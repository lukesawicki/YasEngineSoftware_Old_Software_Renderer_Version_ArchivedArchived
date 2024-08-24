#include "yas_engine.hpp"

#include <SDL_mixer.h>

#include <bit>
#include <fstream>
#include <iostream>
#include <string>

#include "collider.hpp"
#include "cosine_points_generator.hpp"
#include "fibonacci_points_generator.hpp"
#include "prime_numbers_points_generator.hpp"
#include "randomizer.hpp"
#include "sine_points_generator.hpp"
#include "yas_graphics_library.hpp"

YasEngine* YasEngine::instance_ = nullptr;

void YasEngine::initialize() {
  engine_version_ = "YasEngine 1 | Beauty of Math 1 version: " +
                    std::to_string(MAJOR_REVISION) + "." +
                    std::to_string(MINOR_REVISION) + "." +
                    std::to_string(BUG_FIX_RELEASE) + "." +
                    std::to_string(BUILD_NUMBER);
  std::cout << engine_version_ << "\n";
  readSettingsFromFile();

  srand(clock());

  prepareBasicSettings();
  prepareRendering();
  preparePlayer();
  prepareGameWorld();
  prepareSoundAndMusic();
  prepareInterface();

  writer_.initialize();

  mathematics_graphs_surface_ = new MathematicsGraphsSurface(
      0, static_cast<int>(window_dimensions_->y_ * 0.5F),
      static_cast<int>(window_dimensions_->x_ * 0.5F),
      static_cast<int>(window_dimensions_->y_), kBlack);
}

void YasEngine::clean() {
  for (auto drawableObject : objects_to_draw_) {
    delete drawableObject;
  }

  delete mathematics_graphs_surface_;
  delete pixels_table_;
  delete window_dimensions_;

  delete sine_picture_;
  delete cosine_picture_;
  delete fibonaccie_picture_;
  delete prime_numbers_picture_;

  delete mouse_position_change_information_;

  // delete player_; // will be deleted in the loop at the beginning of that
  // method

  delete input_;

  Mix_FreeChunk(shoot_sound_);
  Mix_FreeChunk(hit_sound_);
  Mix_FreeMusic(music_);
  Mix_CloseAudio();
  Mix_Quit();
  SDL_DestroyTexture(screen_texture_);
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void YasEngine::YasEngineStart() {
  TimePicker timePicker = TimePicker();
  time_ = timePicker.getSeconds();
  fps_time_ = 0.0F;
  frames_ = 0;

  while (!quit_) {
    while (SDL_PollEvent(&event_)) {
      handleInput(event_);
    }

    new_time_ = timePicker.getSeconds();
    delta_time_ = new_time_ - time_;
    time_ = new_time_;

    ++frames_;
    fps_time_ = fps_time_ + delta_time_;
    if (fps_time_ >= 1.0F) {
      fps_ = frames_ / fps_time_;
      frames_ = 0;
      fps_time_ = 0.0F;
    }

    update(delta_time_);
    render(delta_time_);
    if (level_changed_) {
      level_changed_ = false;
    }
  }

  clean();
}

void YasEngine::readSettingsFromFile() {
  std::ifstream settingsFile("settings.json");
  if (!settingsFile.is_open()) {
    std::cerr << "Error opening JSON file" << std::endl;
    exit(1);
  }

  std::string settingsString((std::istreambuf_iterator<char>(settingsFile)),
                             std::istreambuf_iterator<char>());
  settingsFile.close();

  settings.Parse(settingsString.c_str());

  if (settings.HasParseError()) {
    std::cerr << "Error parsing JSON" << std::endl;
    exit(1);
  }

  const rapidjson::Value& soundSettings = settings["SOUND_MUSIC"];

  music_volume_ = soundSettings["MUSIC_VOLUME"].GetInt();
  shoot_volume_ = soundSettings["SHOOT_VOLUME"].GetInt();
  hit_volume_ = soundSettings["HIT_VOLUME"].GetInt();
  other_volume_ = soundSettings["OTHER_VOLUME"].GetInt();
}

void YasEngine::prepareRendering() {
  pixels_table_ = new PixelsTable(window_width_, window_height_, kBlack);
  renderer_ = SDL_CreateRenderer(window_, NULL);
  SDL_SetRenderLogicalPresentation(renderer_, window_width_, window_height_,
                                   SDL_LOGICAL_PRESENTATION_DISABLED,
                                   SDL_SCALEMODE_NEAREST);
  screen_texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBX32,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      window_width_, window_height_);
}

void YasEngine::prepareBasicSettings() {
  checkEndianness();

  SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO);

  window_dimensions_ = new Vector2D<int>(window_width_, window_height_);
  Uint32 windowFlags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_BORDERLESS |
                       SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE |
                       SDL_WINDOW_OPENGL;  // SDL_WINDOW_ALWAYS_ON_TOP
  window_ =
      SDL_CreateWindow("YasEngine", window_width_, window_height_, windowFlags);

  SDL_SetWindowMinimumSize(window_, window_width_, window_height_);
  SDL_HideCursor();
}

void YasEngine::checkEndianness() {
  if constexpr (std::endian::native == std::endian::big) {
    std::cout << "BIG ENDIAN" << std::endl;
    endianness_ = 0;
  } else {
    if (std::endian::native == std::endian::little) {
      std::cout << "LITTLE ENDIAN" << std::endl;
      endianness_ = 1;
    } else {
      std::cout << "MIXED ENDIAN" << std::endl;
      endianness_ = 2;
    }
  }
}

void YasEngine::drawHudElements(double& deltaTime) {
  drawCrossHair(mouse_x_, mouse_y_, *pixels_table_, false);
}

void YasEngine::drawFrame(double& deltaTime) {
  drawHorizontalLine(
      *pixels_table_, static_cast<int>(map_frame_.top_line_segment.point_0.x_),
      static_cast<int>(map_frame_.top_line_segment.point_1.x_),
      static_cast<int>(map_frame_.top_line_segment.point_0.y_), kRed);
  drawHorizontalLine(
      *pixels_table_,
      static_cast<int>(map_frame_.bottom_line_segment.point_0.x_),
      static_cast<int>(map_frame_.bottom_line_segment.point_1.x_),
      static_cast<int>(map_frame_.bottom_line_segment.point_0.y_), kGreen);

  drawVerticalLine(
      *pixels_table_, static_cast<int>(map_frame_.left_line_segment.point_0.y_),
      static_cast<int>(map_frame_.left_line_segment.point_1.y_),
      static_cast<int>(map_frame_.left_line_segment.point_0.x_), kYellow);
  drawVerticalLine(*pixels_table_,
                   static_cast<int>(map_frame_.right_line_segment.point_0.y_),
                   static_cast<int>(map_frame_.right_line_segment.point_1.y_),
                   static_cast<int>(map_frame_.right_line_segment.point_0.x_),
                   kYellow);
}

void YasEngine::handleInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_QUIT) {
    quit_ = true;
  } else {
    handleKeyboardInput(event);
    handleMouseInput(event);
  }
}

void YasEngine::handleKeyboardInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.key) {
      case SDLK_ESCAPE:
        handleGameStateWhenESCbuttonPushed();
        break;
      case SDLK_SPACE:
        handleGameStateWhenSPACEbuttonPushed();
        break;
      case SDLK_W:
        input_->up = true;
        break;
      case SDLK_S:
        input_->down = true;
        break;
      case SDLK_A:
        input_->left = true;
        break;
      case SDLK_D:
        input_->right = true;
        break;
      case SDLK_O:
        input_->test_o_button = true;
        break;
      case SDLK_RETURN:
        if (game_state_ == kLevelChangeScreen) {
          game_state_ = GameState::kGameplay;
        }
        if (game_state_ == GameState::kYouWon) {
          game_state_ = GameState::kMainMenuRestart;
          player_won_and_exited_ = true;
        }
        break;
      case SDLK_TAB:
        if (game_state_ == kLevelChangeScreen) {
          game_state_ = GameState::kGameplay;
        }
        if (game_state_ == GameState::kYouWon) {
          game_state_ = GameState::kMainMenuRestart;
          player_won_and_exited_ = true;
        }
        break;
      default:;
    }
  }

  if (event.type == SDL_EVENT_KEY_UP) {
    switch (event.key.key) {
      case SDLK_W:
        input_->up = false;
        break;
      case SDLK_S:
        input_->down = false;
        break;
      case SDLK_A:
        input_->left = false;
        break;
      case SDLK_D:
        input_->right = false;
        break;
      case SDLK_O:
        if (input_->test_o_button == true) {
          Mix_PlayChannel(-1, other_sound_, 0);
          input_->test_o_button = false;
        }
        break;
      default:;
    }
  }
}

void YasEngine::handleMouseInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    handleMouseMovement();
  }
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    switch (game_state_) {
      case kGameplay:
        player_->is_shooting_ = true;

        break;
      case kMainMenuRestart:
        handleClickedButtons();
        break;
      case kIntro:
        game_state_ = GameState::kMainMenuRestart;
        break;
      case kOutro:
        quit_ = true;
        break;
      default:;
    }
  }

  if (event.type == SDL_EVENT_MOUSE_BUTTON_UP &&
      event.button.button == SDL_BUTTON_LEFT) {
    switch (game_state_) {
      case kGameplay:
        player_->is_shooting_ = false;
        break;
    }
  }
}

void YasEngine::handleMouseMovement() {
  float x;
  float y;
  SDL_GetMouseState(&x, &y);
  mouse_position_change_information_->mouseMoved = true;
  mouse_position_change_information_->x = x;
  mouse_position_change_information_->y = y;
  mouse_x_ = static_cast<float>(mouse_position_change_information_->x);
  mouse_y_ = static_cast<float>(mouse_position_change_information_->y);

  windowPositionToCartesianPosition(mouse_x_, mouse_y_, window_dimensions_);
}

void YasEngine::deleteNotAliveObjects() {
  for (int i = 0; i < objects_to_draw_.size(); i++) {
    if (objects_to_draw_[i]->is_alive_ == false) {
      objects_to_draw_.erase(objects_to_draw_.begin() + i);
    }
  }
}

void YasEngine::handleSpawningCollectibles() {
  for (int i = 0; i < 8; i++) {
    int randomSpawner = Randomizer::drawNumberClosedInterval(0, 15);
    int firstLevelNodeIndex =
        spawners_positions_[randomSpawner]->first_level_node;
    int secondLevelNodeIndex =
        spawners_positions_[randomSpawner]->second_level_node;
    if (Spawner::number_of_spawned_objects_ < kmax_collectibles_to_spawn_) {
      if (isObjectInSameQuarterAsProtagonist(randomSpawner)) {
        continue;
      }
      spawners_->child_nodes_[firstLevelNodeIndex]
          ->child_nodes_[secondLevelNodeIndex]
          ->spawner_->spawnObject(game_object_);
      if (game_object_ != nullptr) {
        Spawner::number_of_spawned_objects_++;
        objects_to_draw_.push_back(game_object_);
        game_object_ = nullptr;
      }
    } else {
      spawners_->child_nodes_[firstLevelNodeIndex]
          ->child_nodes_[secondLevelNodeIndex]
          ->spawner_->resetTimes();
    }
  }
}

bool YasEngine::isObjectInSameQuarterAsProtagonist(int randomSpawner) {
  int quarterSize =
      spawners_
          ->child_nodes_[spawners_positions_[randomSpawner]->first_level_node]
          ->child_nodes_[spawners_positions_[randomSpawner]->second_level_node]
          ->size_;
  return (
      (player_->getPosition().x_ <
       (spawners_
            ->child_nodes_[spawners_positions_[randomSpawner]->first_level_node]
            ->child_nodes_[spawners_positions_[randomSpawner]
                               ->second_level_node]
            ->position_->x_ +
        quarterSize / 2)) &&
      (player_->getPosition().x_ >
       (spawners_
            ->child_nodes_[spawners_positions_[randomSpawner]->first_level_node]
            ->child_nodes_[spawners_positions_[randomSpawner]
                               ->second_level_node]
            ->position_->x_ -
        quarterSize / 2)) &&
      (player_->getPosition().y_ <
       (spawners_
            ->child_nodes_[spawners_positions_[randomSpawner]->first_level_node]
            ->child_nodes_[spawners_positions_[randomSpawner]
                               ->second_level_node]
            ->position_->y_ +
        quarterSize / 2)) &&
      (player_->getPosition().y_ >
       (spawners_
            ->child_nodes_[spawners_positions_[randomSpawner]->first_level_node]
            ->child_nodes_[spawners_positions_[randomSpawner]
                               ->second_level_node]
            ->position_->y_ -
        quarterSize / 2)));
}

void YasEngine::handleProjectiles() {
  Projectile* projectile = player_->shoot();

  if (projectile != nullptr) {
    Mix_PlayChannel(-1, shoot_sound_, 0);
    objects_to_draw_.push_back(projectile);
  }

  if (projectile != nullptr) {
    projectile = nullptr;
  }
}

void YasEngine::handlePlayer() {
  if (mouse_position_change_information_->mouseMoved || input_->up ||
      input_->down || input_->left || input_->right) {
    player_->rotateToMousePositionInLocalCoordinateSystem(
        static_cast<float>(mouse_position_change_information_->x),
        static_cast<float>(mouse_position_change_information_->y),
        window_dimensions_);
  }
}

void YasEngine::preparePlayer() {
  srand(clock());
  int sizeOfkGameplaySpace = static_cast<int>(window_dimensions_->x_ * 0.25F);
  int x = Randomizer::drawNumberClosedInterval(0, sizeOfkGameplaySpace) - 64;
  int y = Randomizer::drawNumberClosedInterval(0, sizeOfkGameplaySpace) - 64;

  player_ =
      new Player(static_cast<float>((-sizeOfkGameplaySpace) + x), 0.0F + y);
  player_->set_color(kYellow);
  player_->setInput(input_);
  player_->setInput(mouse_position_change_information_);
  objects_to_draw_.push_back(player_);
}

void YasEngine::update(double& deltaTime) {
  if (level_changed_) {
    for (int i = 0; i < objects_to_draw_.size(); i++) {
      if (objects_to_draw_[i]->i_am_ != GameObject::kProtagonist) {
        objects_to_draw_[i]->is_alive_ = false;
      }
    }
    Spawner::number_of_spawned_objects_ = 0;
  }

  deleteNotAliveObjects();

  switch (game_state_) {
    case kGameplay:
      handleSpawningCollectibles();
      handlePhysics();
      if (level_changed_) {
        game_state_ = kLevelChangeScreen;
      }
      if (level_changed_ && level_ == -1) {
        game_state_ = GameState::kYouWon;
      }
      moveObjects();
      handleProjectiles();
      handlePlayer();
      break;
  }

  if (player_won_and_exited_) {
    resetAll();
  }
}

void YasEngine::resetAll() {
  deleteNotAliveObjects();
  level_ = 1;
  previous_level_ = 0;
  level_changed_ = false;
  sine_points_harvested_ = 0;
  cosine_points_harvested_ = 0;
  primes_points_harvested_ = 0;
  fibonacci_points_harvested_ = 0;
  player_won_and_exited_ = false;
}

void YasEngine::render(double& deltaTime) {
  pixels_table_->clearColor(kBlack);
  mathematics_graphs_surface_->clearColor(kBlack);

  switch (game_state_) {
    case kIntro:
      writer_.write((-238) / 2, 200, "BEAUTY.OF.MATH", kLightBlue,
                    *pixels_table_);
      // TODO write title and version and tha game is powered by YasEngine
      writer_.write((-170) / 2, 100, "POWERED.BY", kRed, *pixels_table_);
      writer_.write((-170) / 2, 0, "YAS.ENGINE", kYellow, *pixels_table_);
      break;
    case kMainMenuRestart:
      drawButtons();
      break;
    case kGameplay:
      renderGameObjects(deltaTime);
      renderOnViewports(deltaTime);
      drawFrame(deltaTime);
      break;
    case kOutro:
      writer_.write((-37 * 17) / 2, 350,
                    "GAME.DESIGN.PROGRAMMING.AND.MARKETING", kLightBlue,
                    *pixels_table_);
      writer_.write((-14 * 17) / 2, 325, "LUKASZ.SAWICKI", kPurple,
                    *pixels_table_);
      writer_.write((-22 * 17) / 2, 275, "SOUND.DESIGN.AND.MUSIC", kLightBlue,
                    *pixels_table_);
      writer_.write((-17 * 17) / 2, 250, "JAKUB.TWAROGOWSKI", kPurple,
                    *pixels_table_);
      writer_.write((-17 * 17) / 2, 200, "QUALITY.ASSURANCE", kLightBlue,
                    *pixels_table_);
      writer_.write((-15 * 17) / 2, 175, "BARTLOMIEJ.KAWA", kPurple,
                    *pixels_table_);
      writer_.write((-15 * 17) / 2, 125, "SPECIAL.THANKS:", kGreen,
                    *pixels_table_);
      writer_.write((-22 * 17) / 2, 75, "MY.DEAR.SISTER.IZABELA", kYellow,
                    *pixels_table_);
      writer_.write((-15 * 17) / 2, 50, "MY.LOVE.MARIOLA", kYellow,
                    *pixels_table_);
      writer_.write((-50 * 17) / 2, 0,
                    "MY.FRIENDS.FROM.WARSAW.SCHOOL.OF.COMPUTER.SCIENCE:", kBlue,
                    *pixels_table_);
      writer_.write((-36 * 17) / 2, -25, "LUKASZ.KRZYSZTOF.MICHAL.MAREK.TOMASZ",
                    kYellow, *pixels_table_);
      writer_.write((-21 * 17) / 2, -75, "MY.FRENDS.FROM.GDS.4:", kBlue,
                    *pixels_table_);
      writer_.write((-17 * 17) / 2, -100, "KASIA.AND.BARTOSZ", kYellow,
                    *pixels_table_);
      writer_.write((-31 * 17) / 2, -150, "WHOLE.COMMUNITY.OF.KNTG.POLYGON",
                    kPolygon, *pixels_table_);
      writer_.write((-31 * 17) / 2, -200, "AND.ALL.MEMBERS.OF.TEAM.XPORTAL",
                    kXportal, *pixels_table_);

      break;
    case kLevelChangeScreen:
      renderLevelChange();
      break;
    case kYouWon:
      renderWonScreen();
      break;
    default:;
  }

  drawHudElements(deltaTime);

  SDL_UpdateTexture(screen_texture_, NULL, pixels_table_->pixels_,
                    window_width_ * 4);
  SDL_RenderTexture(renderer_, screen_texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}

void YasEngine::renderGameObjects(double& deltaTime) {
  for (auto object : objects_to_draw_) {
    if (object->is_alive_) {
      // TODO if gamestate == kGameplay

      drawPolygon(object, *pixels_table_);
    }
  }
}

void YasEngine::renderOnViewports(double& deltaTime) {
  if (tests_) {
    mathematics_graphs_surface_->drawCartesianAxies();
  }

  switch (level_) {
    case 1:
      mathematics_graphs_surface_->drawNumbersAsGroupOfLines(
          prime_numbers_picture_->points_set_->points_,
          prime_numbers_picture_->base_points_fuel_, primes_points_harvested_,
          kLightBlue, false);
      break;

    case 2:
      mathematics_graphs_surface_->drawNumbersAsGroupOfLines(
          fibonaccie_picture_->points_set_->points_,
          fibonaccie_picture_->base_points_fuel_, fibonacci_points_harvested_,
          kPurple, false);
      break;
    case 3:
      mathematics_graphs_surface_->drawNumbersAsGroupOfLines(
          sine_picture_->points_set_->points_, sine_picture_->base_points_fuel_,
          sine_points_harvested_, kBlue, true);
      break;
    case 4:
      mathematics_graphs_surface_->drawNumbersAsGroupOfLines(
          cosine_picture_->points_set_->points_,
          cosine_picture_->base_points_fuel_, cosine_points_harvested_, kRed,
          true);
      break;
    default:;
  }

  mathematics_graphs_surface_->copyPixelsInToPIxelTable(*pixels_table_);
}

void YasEngine::renderLevelChange() {
  switch (previous_level_) {
    case 1:

      writer_.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.1", kLightBlue,
                    *pixels_table_);
      writer_.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                    *pixels_table_);
      writer_.write((-221) / 2, 0, "PRIME.NUMBERS", kGreen, *pixels_table_);
      break;
    case 2:
      writer_.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", kLightBlue,
                    *pixels_table_);
      writer_.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                    *pixels_table_);
      writer_.write((-289) / 2, 0, "FIBONACCI.NUMBERS", kGreen, *pixels_table_);
      break;
    case 3:
      writer_.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", kLightBlue,
                    *pixels_table_);
      writer_.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                    *pixels_table_);
      writer_.write((-221) / 2, 0, "SINE.FUNCTION", kGreen, *pixels_table_);
      break;
    case 4:
      writer_.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", kLightBlue,
                    *pixels_table_);
      writer_.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                    *pixels_table_);
      writer_.write((-255) / 2, 0, "COSINE.FUNCTION", kGreen, *pixels_table_);
      writer_.write((-187) / 2, -25, "AND.YOU.WON", kYellow, *pixels_table_);
      break;
    default:;
  }
}

void YasEngine::renderWonScreen() {
  writer_.write((-119) / 2, 310, "YOU.WON", kLightBlue, *pixels_table_);
  writer_.write((-408) / 2, 210, "MATHEMATICS.IS.BEAUTIFUL", kYellow,
                *pixels_table_);
  writer_.write((-578) / 2, 110, "YOU.ARE.NOT.SUPPOSED.TO.BELIEVE.ME", kPurple,
                *pixels_table_);
  writer_.write((-357) / 2, 10, "CHECK.IT.FOR.YOURSELF", kPurple,
                *pixels_table_);
  writer_.write((-935) / 2, -10,
                "FIND.AND.LEARN.MORE.ABOUT.WHAT.YOU.HAVE.JUST.DISCOVEkRed",
                kPurple, *pixels_table_);
  writer_.write((-221) / 2, -110, "PRIME.NUMBERS", kGreen, *pixels_table_);
  writer_.write((-289) / 2, -160, "FIBONACCI.NUMBERS", kYellow, *pixels_table_);
  writer_.write((-425) / 2, -210, "SINE.AND.COSINE.FUNCTIONS", kLightBlue,
                *pixels_table_);
}

void YasEngine::handlePhysics() {
  if (objects_to_draw_.size() >= 3) {
    for (int i = 0; i < static_cast<int>(objects_to_draw_.size() - 2); i++) {
      if (objects_to_draw_[i]->i_am_ == GameObject::kCollectible) {
        handleCollectiblesWithWallsCollisions(objects_to_draw_[i]);
      }

      if (objects_to_draw_[i]->i_am_ == GameObject::kProtagonist) {
        handleProtagonistWithWallsCollisions(objects_to_draw_[i]);
      }

      for (int j = i; j < static_cast<int>(objects_to_draw_.size()); j++) {
        if (objects_to_draw_[i] == objects_to_draw_[j] ||
            (objects_to_draw_[i]->i_am_ == GameObject::kProjectile &&
             objects_to_draw_[j]->i_am_ == GameObject::kProjectile) ||
            (objects_to_draw_[i]->i_am_ == GameObject::kProjectile &&
             objects_to_draw_[j]->i_am_ == GameObject::kProtagonist) ||
            (objects_to_draw_[i]->i_am_ == GameObject::kProtagonist &&
             objects_to_draw_[j]->i_am_ == GameObject::kProjectile) ||
            (objects_to_draw_[i]->i_am_ == GameObject::kCollectible &&
             objects_to_draw_[j]->i_am_ == GameObject::kCollectible)) {
          continue;
        }

        // LEFT Projectile <-> Collectible && Protagonist <-> Collectible)
        if (objects_to_draw_[i]->is_alive_ && objects_to_draw_[j]->is_alive_) {
          GameObject* protagonist =
              getProtagonist(objects_to_draw_[i], objects_to_draw_[j]);
          GameObject* gameObj =
              getNotProtagonist(objects_to_draw_[i], objects_to_draw_[j]);

          if ((protagonist != nullptr) &&
              gameObj->i_am_ == GameObject::kCollectible &&
              !gameObj->collider_.is_in_collision_ &&
              Collider::isCollision(objects_to_draw_[i]->collider_,
                                    objects_to_draw_[j]->collider_)) {
            // handleBuildingGraph
            handleDisassemblingGraphs(gameObj);

            gameObj->collider_.is_in_collision_ = true;
          }

          // if exited from collision
          if ((protagonist != nullptr) &&
              gameObj->i_am_ == GameObject::kCollectible &&
              gameObj->collider_.is_in_collision_ &&
              !Collider::isCollision(objects_to_draw_[i]->collider_,
                                     objects_to_draw_[j]->collider_)) {
            gameObj->collider_.is_in_collision_ = false;
          }

          if ((protagonist == nullptr) &&
              Collider::isCollision(objects_to_draw_[i]->collider_,
                                    objects_to_draw_[j]->collider_)) {
            objects_to_draw_[i]->is_alive_ = false;
            objects_to_draw_[j]->is_alive_ = false;
            Mix_PlayChannel(-1, hit_sound_, 0);

            if (gameObj->i_am_ == GameObject::kCollectible) {
              handleDestroingCollectibles(gameObj);
              handlingAssemblingGraphs(gameObj);
            }
          }
        }
      }
    }
  }
}  // END OF handlePhysics()

void YasEngine::handleDisassemblingGraphs(GameObject* gameObj) {
  if (primes_points_harvested_ < 0) {
    primes_points_harvested_ = 0;
    return;
  }
  if (fibonacci_points_harvested_ < 0) {
    fibonacci_points_harvested_ = 0;
    return;
  }
  if (sine_points_harvested_ < 0) {
    sine_points_harvested_ = 0;
    return;
  }
  if (cosine_points_harvested_ < 0) {
    cosine_points_harvested_ = 0;
    return;
  }

  switch (level_) {
    case 1:
      primes_points_harvested_ -= gameObj->number_of_vertices_;
      break;

    case 2:

      fibonacci_points_harvested_ -= gameObj->number_of_vertices_;
      break;

    case 3:

      sine_points_harvested_ -= gameObj->number_of_vertices_;
      break;

    case 4:

      cosine_points_harvested_ -= gameObj->number_of_vertices_;
      break;

    default:;
  }
}

void YasEngine::handleDestroingCollectibles(GameObject* gameObj) {
  if (Spawner::number_of_spawned_objects_ > 0) {
    --Spawner::number_of_spawned_objects_;
  } else {
    Spawner::number_of_spawned_objects_ = 0;
  }
}

void YasEngine::handlingAssemblingGraphs(GameObject* gameObj) {
  int newValueOfPrimesPointsHarvested =
      primes_points_harvested_ + gameObj->number_of_vertices_;
  int newValueOfFibbsPointsHarvested =
      fibonacci_points_harvested_ + gameObj->number_of_vertices_;
  int newSinePointsHarvested =
      sine_points_harvested_ + gameObj->number_of_vertices_;
  int newCosinePointsHarvested =
      cosine_points_harvested_ + gameObj->number_of_vertices_;

  int test1 = primes_points_harvested_;

  if (level_ == 1 && newValueOfPrimesPointsHarvested >=
                         prime_numbers_picture_->base_points_fuel_) {
    primes_points_harvested_ = prime_numbers_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = 2;
    level_changed_ = true;
    return;
  }

  if (level_ == 2 && newValueOfFibbsPointsHarvested >=
                         fibonaccie_picture_->base_points_fuel_) {
    fibonacci_points_harvested_ = fibonaccie_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = 3;
    level_changed_ = true;
    return;
  }

  int some = sine_points_harvested_;

  if (level_ == 3 &&
      newSinePointsHarvested >= sine_picture_->base_points_fuel_) {
    sine_points_harvested_ = sine_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = 4;
    level_changed_ = true;
    return;
  }

  if (level_ == 4 &&
      newCosinePointsHarvested >= cosine_picture_->base_points_fuel_) {
    cosine_points_harvested_ = cosine_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = -1;
    level_changed_ = true;
    return;
  }

  switch (level_) {
    case 1:

      if (newValueOfPrimesPointsHarvested <=
          prime_numbers_picture_->base_points_fuel_) {
        primes_points_harvested_ = newValueOfPrimesPointsHarvested;
      }
      break;
    case 2:

      if (newValueOfFibbsPointsHarvested <=
          fibonaccie_picture_->base_points_fuel_) {
        fibonacci_points_harvested_ = newValueOfFibbsPointsHarvested;
      }

      break;
    case 3:

      if (newSinePointsHarvested <= sine_picture_->base_points_fuel_) {
        sine_points_harvested_ = newSinePointsHarvested;
      }

      break;
    case 4:

      if (newCosinePointsHarvested <= cosine_picture_->base_points_fuel_) {
        cosine_points_harvested_ = newCosinePointsHarvested;
      }

      break;
    default:;
  }
}

void YasEngine::handleCollectiblesWithWallsCollisions(GameObject* object) {
  float leftWall = map_frame_.left_line_segment.point_0.x_;
  float rightWall = map_frame_.right_line_segment.point_0.x_;
  float topWall = map_frame_.top_line_segment.point_0.y_;
  float bottomWall = map_frame_.bottom_line_segment.point_0.y_;

  if (object->i_am_ == GameObject::kCollectible) {
    if (object->getColliderLeftSide() < static_cast<int>(leftWall)) {
      bounceCollectibles(object, kLeft);
    }

    if (object->getColliderRightSide() > static_cast<int>(rightWall)) {
      bounceCollectibles(object, kRight);
    }

    if (object->getColliderTopSide() < static_cast<int>(topWall)) {
      bounceCollectibles(object, kTop);
    }

    if (object->getColliderBottomSide() > static_cast<int>(bottomWall)) {
      bounceCollectibles(object, kBottom);
    }
  }
}

bool YasEngine::isObjectProtagonist(GameObject* object) {
  return object->i_am_ == GameObject::kProtagonist;
}

GameObject* YasEngine::getProtagonist(GameObject* object0,
                                      GameObject* object1) {
  if (isObjectProtagonist(object0)) {
    return object0;
  }
  if (isObjectProtagonist(object1)) {
    return object1;
  }
  return nullptr;
}

GameObject* YasEngine::getNotProtagonist(GameObject* object0,
                                         GameObject* object1) {
  if (!isObjectProtagonist(object0)) {
    return object0;
  }
  if (!isObjectProtagonist(object1)) {
    return object1;
  }
  return nullptr;
}

void YasEngine::handleProtagonistWithWallsCollisions(GameObject* object) {
  float leftWall = map_frame_.left_line_segment.point_0.x_;
  float rightWall = map_frame_.right_line_segment.point_0.x_;
  float topWall = map_frame_.top_line_segment.point_0.y_;
  float bottomWall = map_frame_.bottom_line_segment.point_0.y_;

  if (object->getColliderLeftSide() < static_cast<int>(leftWall)) {
    moveObjectToMapBoundries(object, kLeft);
    // bounceCollectibles(object, LEFT);
  }

  if (object->getColliderRightSide() > static_cast<int>(rightWall)) {
    moveObjectToMapBoundries(object, kRight);
    // bounceCollectibles(object, RIGHT);
  }

  if (object->getColliderTopSide() > static_cast<int>(topWall)) {
    moveObjectToMapBoundries(object, kTop);
    // bounceCollectibles(object, TOP);
  }

  if (object->getColliderBottomSide() < static_cast<int>(bottomWall)) {
    moveObjectToMapBoundries(object, kBottom);
    // bounceCollectibles(object, BOTTOM);
  }
}

void YasEngine::bounceCollectibles(GameObject* gameObject, Wall wall) {
  Vector2D<float> normal;
  switch (wall) {
    case kLeft:
      normal.x_ = 1;
      normal.y_ = 0;
      break;
    case kRight:
      normal.x_ = -1;
      normal.y_ = 0;
      break;
    case kTop:
      normal.x_ = 0;
      normal.y_ = -1;
      break;
    case kBottom:
      normal.x_ = 0;
      normal.y_ = 1;
      break;
    default:;
      break;
  }

  float dotProduct = Vector2D<float>::dotProduct(gameObject->velocity_, normal);
  Vector2D<float>::multiplyByScalar(&normal, dotProduct * 2.0f);
  Vector2D<float>::substract(&gameObject->velocity_, normal);

  // TO PREVENT COLLECTIBLE STUCK IN THE WALL
  // objects_to_draw_[i]->setX(rightWall - objects_to_draw_[i]->collider.radius_
  // - 1);
}

void YasEngine::moveObjectToMapBoundries(GameObject* gameObject, Wall wall,
                                         int shift) {
  switch (wall) {
    case kLeft:
      gameObject->setX(map_frame_.left_line_segment.point_0.x_ +
                       gameObject->collider_.radius_ + shift);
      break;
    case kRight:
      gameObject->setX(map_frame_.right_line_segment.point_0.x_ -
                       gameObject->collider_.radius_ - shift);
      break;
    case kTop:
      gameObject->setY(map_frame_.top_line_segment.point_0.y_ -
                       gameObject->collider_.radius_ - shift);
      break;
    case kBottom:
      gameObject->setY(map_frame_.bottom_line_segment.point_0.y_ +
                       gameObject->collider_.radius_ + shift);
      break;
    default:;
      break;
  }
}

void YasEngine::moveObjects() {
  for (auto object : objects_to_draw_) {
    if (object->is_alive_) {
      object->Move(static_cast<float>(delta_time_));
      object->RegeneratePolygon();
    }
  }
}

void YasEngine::prepareSoundAndMusic() {
  audio_specs_.freq = 44100;
  audio_specs_.format = MIX_DEFAULT_FORMAT;
  audio_specs_.channels = 2;

  if (Mix_OpenAudio(0, &audio_specs_) < 0) {
    std::cout << "Error cannot open audio device" << std::endl;
  }

  Mix_Init(MIX_DEFAULT_FORMAT);

  music_ = Mix_LoadMUS("music.wav");
  if (music_ == NULL) {
    std::cout << "Error while loading music_. Cannot load music." << std::endl;
    std::cout << "SDL message: " << SDL_GetError() << std::endl
              << " | Mix library error: " << Mix_GetError() << std::endl;
    quit_ = true;
  }

  Mix_VolumeMusic(music_volume_);
  // Mix_VolumeMusic

  shoot_sound_ = Mix_LoadWAV("shoot.wav");
  Mix_VolumeChunk(shoot_sound_, shoot_volume_);

  hit_sound_ = Mix_LoadWAV("hit.wav");
  Mix_VolumeChunk(hit_sound_, hit_volume_);

  other_sound_ = Mix_LoadWAV("other.wav");
  Mix_VolumeChunk(other_sound_, other_volume_);

  if (shoot_sound_ == NULL || hit_sound_ == NULL || other_sound_ == NULL) {
    std::cout << "Error while loading sounds. Cannot load sounds." << std::endl;
    std::cout << "SDL message: " << SDL_GetError() << std::endl
              << " | Mix library error: " << Mix_GetError() << std::endl;
    quit_ = true;
  }
  Mix_PlayMusic(music_, 999);
}

void YasEngine::prepareGameWorld() {
  // srand(clock());

  int mainNodeX = -(window_dimensions_->x_ / 4);
  int mainNodeY = 0;

  std::cout << "Main node X: " << mainNodeX << "\n";
  std::cout << "Main node Y: " << mainNodeY << "\n";

  spawners_ = new Node(new Vector2D<int>(-(window_dimensions_->x_ / 4), 0),
                       window_dimensions_->x_ / 2, nullptr);

  // adding nodes(first level_) to head node
  Node::addNodes(*spawners_);
  for (int i = 0; i < 4; i++) {
    // adding nodes(second level_) to nodes
    Node::addNodes(*spawners_->child_nodes_[i]);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      spawners_positions_.push_back(new NodeNumbersOnTwoProceedingLevels(i, j));
    }
  }

  int drawnNumbers = 0;  // PL - wylosowane a nie narysowane w_ tym kontekscie
  int iteration = 0;
  bool drawn = false;  // PL - bylo wylosowane
  NodeNumbersOnTwoProceedingLevels playerPosition;

  //                   H
  //    0         1         2          3
  // 0 1 2 3   0 1 2 3___0 1 2 3   0 1 2 3

  //    |````` `````|
  //    |           |
  //    |     H     |
  //    |           |
  //    |           |
  //    |___________|
  //    |`````|`````|
  //    |  0  |  1  |
  //    |_____|_____|
  //    |     |     |
  //    |  2  |  3  |
  //    |_____|_____|
  //     ___________
  //    | 0|1 | 0|1 |
  //    |--|--|--|--|
  //    | 2|3 | 2|3 |
  //    -------------
  //    | 0|1 | 0|1 |
  //    |--|--|--|--|
  //    | 2|3 | 2|3 |
  //     ```````````
  // TO READ -----------> Latice

  // calculate position_ of player_ on tree 1 - level_ of nodes and number of
  // node and 2 level_ of node and number
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (player_->getPosition().x_ >=
              (spawners_->child_nodes_[i]->child_nodes_[j]->position_->x_ -
               spawners_->child_nodes_[i]->child_nodes_[j]->size_ * 0.5) &&
          player_->getPosition().x_ <
              (spawners_->child_nodes_[i]->child_nodes_[j]->position_->x_ +
               spawners_->child_nodes_[i]->child_nodes_[j]->size_ * 0.5) &&
          player_->getPosition().y_ <=
              (spawners_->child_nodes_[i]->child_nodes_[j]->position_->y_ +
               spawners_->child_nodes_[i]->child_nodes_[j]->size_ * 0.5) &&
          player_->getPosition().y_ >
              (spawners_->child_nodes_[i]->child_nodes_[j]->position_->y_ -
               spawners_->child_nodes_[i]->child_nodes_[j]->size_ * 0.5)) {
        playerPosition.first_level_node = i;
        playerPosition.second_level_node = j;
        goto afterFor;
      }
    }
  }
afterFor:

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      spawners_->child_nodes_[i]->child_nodes_[j]->spawner_ = new Spawner(
          spawners_->child_nodes_[i]->child_nodes_[j]->position_->x_,
          spawners_->child_nodes_[i]->child_nodes_[j]->position_->y_);
    }
  }

  number_of_given_colors_.insert({"kRed", 0});
  number_of_given_colors_.insert({"GREEN", 0});
  number_of_given_colors_.insert({"kBlue", 0});
  number_of_given_colors_.insert({"YELLOW", 0});
  prepareDataForDrawingGraphs();
}

void YasEngine::setFrameAroundGameplaySpace() {
  const int VERTHICAL_SHIFT = 10;
  const int HORIZONTAL_SHIFT = 10;

  // HORIZONTAL LINE SEGMENTS

  // Top              ---->
  // Left point
  map_frame_.top_line_segment.point_0.x_ =
      static_cast<float>((-(window_dimensions_->x_ / 2)) + HORIZONTAL_SHIFT);
  map_frame_.top_line_segment.point_0.y_ =
      static_cast<float>((window_dimensions_->y_ / 2) - VERTHICAL_SHIFT);
  // Right point
  map_frame_.top_line_segment.point_1.x_ =
      static_cast<float>(-1 - HORIZONTAL_SHIFT);
  map_frame_.top_line_segment.point_1.y_ =
      static_cast<float>((window_dimensions_->y_ / 2) - VERTHICAL_SHIFT);

  // Bottom
  // Left point
  map_frame_.bottom_line_segment.point_0.x_ =
      static_cast<float>((-(window_dimensions_->x_ / 2)) + HORIZONTAL_SHIFT);
  map_frame_.bottom_line_segment.point_0.y_ =
      static_cast<float>((-(window_dimensions_->y_ / 2)) + VERTHICAL_SHIFT);

  // Right point
  map_frame_.bottom_line_segment.point_1.x_ =
      static_cast<float>(-HORIZONTAL_SHIFT);
  map_frame_.bottom_line_segment.point_1.y_ =
      static_cast<float>((-(window_dimensions_->y_ / 2)) + VERTHICAL_SHIFT);

  // VERTICAL LINE SEGMENTS
  // Left
  // Top point
  map_frame_.left_line_segment.point_0.x_ =
      static_cast<float>((-(window_dimensions_->x_ / 2)) + HORIZONTAL_SHIFT);
  map_frame_.left_line_segment.point_0.y_ =
      static_cast<float>((window_dimensions_->y_ / 2) - VERTHICAL_SHIFT);
  // Bottom point
  map_frame_.left_line_segment.point_1.x_ =
      static_cast<float>((-(window_dimensions_->x_ / 2)) + HORIZONTAL_SHIFT);
  map_frame_.left_line_segment.point_1.y_ =
      static_cast<float>((-(window_dimensions_->y_ / 2)) + VERTHICAL_SHIFT);

  // Right
  // Top point
  map_frame_.right_line_segment.point_0.x_ =
      static_cast<float>(-1 - HORIZONTAL_SHIFT);
  map_frame_.right_line_segment.point_0.y_ =
      static_cast<float>((window_dimensions_->y_ / 2) - VERTHICAL_SHIFT);
  // Bottom point
  map_frame_.right_line_segment.point_1.x_ =
      static_cast<float>(-1 - HORIZONTAL_SHIFT);
  map_frame_.right_line_segment.point_1.y_ =
      static_cast<float>((-(window_dimensions_->y_ / 2)) + VERTHICAL_SHIFT);
}

void YasEngine::prepareDataForDrawingGraphs() {
  preparePrimesDrawing();
  prepareFibonacciDrawing();
  prepareSineDrawing();
  prepareCosineDrawing();
}

void YasEngine::prepareSineDrawing() {
  std::map<float, float>* sines =
      generateSineNumbers(40);  // generatePrimeNumbersLessThanN(1000);
  sine_points_harvested_ = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>>
  // pair_numbers_map_;

  std::map<int, std::map<float, float>> numbekRedSines;

  pair_numbers_map_.insert(
      std::pair<std::string, std::map<int, std::map<float, float>*>*>(
          "Sines", new std::map<int, std::map<float, float>*>));

  // for (int i = 0; i < sinuses->size_(); i++)
  // {
  int i = 0;
  for (std::pair<float, float> pair : *sines) {
    std::map<float, float>* m = new std::map<float, float>();
    m->insert(pair);
    pair_numbers_map_.at("Sines")->insert(
        std::pair<int, std::map<float, float>*>(i, m));
  }

  // }

  sine_picture_ = new MathPicture(sines, new SinePointsGenerator());
}

void YasEngine::prepareCosineDrawing() {
  std::map<float, float>* cosines =
      generateCosineNumbers(40);  // generatePrimeNumbersLessThanN(1000);
  cosine_points_harvested_ = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>>
  // pair_numbers_map_;

  std::map<int, std::map<float, float>> numbekRedSines;

  pair_numbers_map_.insert(
      std::pair<std::string, std::map<int, std::map<float, float>*>*>(
          "Cosines", new std::map<int, std::map<float, float>*>));

  // for (int i = 0; i < sinuses->size_(); i++)
  // {
  int i = 0;
  for (std::pair<float, float> pair : *cosines) {
    std::map<float, float>* m = new std::map<float, float>();
    m->insert(pair);
    pair_numbers_map_.at("Cosines")->insert(
        std::pair<int, std::map<float, float>*>(i, m));
  }

  // }

  cosine_picture_ = new MathPicture(cosines, new CosinePointsGenerator());
}

void YasEngine::prepareFibonacciDrawing() {
  std::vector<int> fibbs = generateNfibonacciNumbers(40);
  fibonacci_points_harvested_ = 0;

  numbers_map_.insert(std::pair<std::string, std::map<int, float>*>(
      "Fibbs", new std::map<int, float>));

  for (int i = 0; i < fibbs.size(); i++) {
    numbers_map_.at("Fibbs")->insert(std::pair<int, int>(i, fibbs.at(i)));
  }

  fibonaccie_picture_ =
      new MathPicture(numbers_map_.at("Fibbs"), new FibonacciPointsGenerator());
}

void YasEngine::preparePrimesDrawing() {
  std::vector<int> primes = generatePrimeNumbersLessThanN(1000);
  primes_points_harvested_ = 0;

  numbers_map_.insert(std::pair<std::string, std::map<int, float>*>(
      "Primes", new std::map<int, float>));

  for (int i = 0; i < primes.size(); i++) {
    numbers_map_.at("Primes")->insert(std::pair<int, int>(i, primes.at(i)));
  }

  prime_numbers_picture_ = new MathPicture(numbers_map_.at("Primes"),
                                           new PrimeNumbersPointsGenerator());

  std::cout << "prepakRedPrimesDrawing" << "\n";
}

void YasEngine::prepareInterface() {
  // Button 1
  buttons_.push_back(new Button(Button::kRestartStart, "START", kRed));
  buttons_.at(0)->setPosition(0, 50);
  dynamic_cast<Button*>(buttons_.at(0))->horizontal_margin_ = 10;
  dynamic_cast<Button*>(buttons_.at(0))->vertical_margin_ = 5;
  dynamic_cast<Button*>(buttons_.at(0))->button_width_ =
      writer_.kfont_width *
          static_cast<int>(
              dynamic_cast<Button*>(buttons_.at(0))->text_.size()) +
      2 * dynamic_cast<Button*>(buttons_.at(0))->horizontal_margin_;
  dynamic_cast<Button*>(buttons_.at(0))->button_height_ =
      writer_.kfont_height +
      2 * dynamic_cast<Button*>(buttons_.at(0))->vertical_margin_;
  buttons_.at(0)->local_vertices_ = new Vector2D<float>[4];
  buttons_.at(0)->world_vertices_ = new Vector2D<float>[4];
  buttons_.at(0)->local_vertices_[0].x_ =
      0 - dynamic_cast<Button*>(buttons_.at(0))->button_width_ * 0.5F;
  buttons_.at(0)->local_vertices_[0].y_ =
      0 + dynamic_cast<Button*>(buttons_.at(0))->button_height_ * 0.5F;
  buttons_.at(0)->local_vertices_[1].x_ =
      0 + dynamic_cast<Button*>(buttons_.at(0))->button_width_ * 0.5F;
  buttons_.at(0)->local_vertices_[1].y_ =
      0 + dynamic_cast<Button*>(buttons_.at(0))->button_height_ * 0.5F;
  buttons_.at(0)->local_vertices_[2].x_ =
      0 + dynamic_cast<Button*>(buttons_.at(0))->button_width_ * 0.5F;
  buttons_.at(0)->local_vertices_[2].y_ =
      0 - dynamic_cast<Button*>(buttons_.at(0))->button_height_ * 0.5F;
  buttons_.at(0)->local_vertices_[3].x_ =
      0 - dynamic_cast<Button*>(buttons_.at(0))->button_width_ * 0.5F;
  buttons_.at(0)->local_vertices_[3].y_ =
      0 - dynamic_cast<Button*>(buttons_.at(0))->button_height_ * 0.5F;
  buttons_.at(0)->Generate();

  // Button 2
  buttons_.push_back(new Button(Button::kQuit, "QUIT", kYellow));
  buttons_.at(1)->setPosition(0, -50);
  dynamic_cast<Button*>(buttons_.at(1))->horizontal_margin_ = 10;
  dynamic_cast<Button*>(buttons_.at(1))->vertical_margin_ = 5;
  dynamic_cast<Button*>(buttons_.at(1))->button_width_ =
      writer_.kfont_width *
          static_cast<int>(
              dynamic_cast<Button*>(buttons_.at(1))->text_.size()) +
      2 * dynamic_cast<Button*>(buttons_.at(1))->horizontal_margin_;
  dynamic_cast<Button*>(buttons_.at(1))->button_height_ =
      writer_.kfont_height +
      2 * dynamic_cast<Button*>(buttons_.at(1))->vertical_margin_;
  buttons_.at(1)->local_vertices_ = new Vector2D<float>[4];
  buttons_.at(1)->world_vertices_ = new Vector2D<float>[4];
  buttons_.at(1)->local_vertices_[0].x_ =
      0 - dynamic_cast<Button*>(buttons_.at(1))->button_width_ * 0.5F;
  buttons_.at(1)->local_vertices_[0].y_ =
      0 + dynamic_cast<Button*>(buttons_.at(1))->button_height_ * 0.5F;
  buttons_.at(1)->local_vertices_[1].x_ =
      0 + dynamic_cast<Button*>(buttons_.at(1))->button_width_ * 0.5F;
  buttons_.at(1)->local_vertices_[1].y_ =
      0 + dynamic_cast<Button*>(buttons_.at(1))->button_height_ * 0.5F;
  buttons_.at(1)->local_vertices_[2].x_ =
      0 + dynamic_cast<Button*>(buttons_.at(1))->button_width_ * 0.5F;
  buttons_.at(1)->local_vertices_[2].y_ =
      0 - dynamic_cast<Button*>(buttons_.at(1))->button_height_ * 0.5F;
  buttons_.at(1)->local_vertices_[3].x_ =
      0 - dynamic_cast<Button*>(buttons_.at(1))->button_width_ * 0.5F;
  buttons_.at(1)->local_vertices_[3].y_ =
      0 - dynamic_cast<Button*>(buttons_.at(1))->button_height_ * 0.5F;
  buttons_.at(1)->Generate();

  setFrameAroundGameplaySpace();
}

void YasEngine::drawButtons() {
  for (unsigned int i = 0; i < buttons_.size(); i++) {
    drawPolygon(buttons_.at(i), *pixels_table_);
    writer_.write(
        static_cast<int>(
            buttons_.at(i)->getPosition().x_ -
            dynamic_cast<Button*>(buttons_.at(i))->button_text_width_ * 0.5F +
            ScreenWriter::kfont_width * 0.5F),
        static_cast<int>(buttons_.at(i)->getPosition().y_),
        dynamic_cast<Button*>(buttons_.at(i))->text_,
        dynamic_cast<Button*>(buttons_.at(i))->color_, *pixels_table_);
  }
}

Button::ButtonId YasEngine::checkWhichButtonClicked() {
  float x = static_cast<float>(mouse_position_change_information_->x);
  float y = static_cast<float>(mouse_position_change_information_->y);
  windowPositionToCartesianPosition(x, y, window_dimensions_);
  for (unsigned int i = 0; i < buttons_.size(); i++) {
    if (
        // mouse cursor under top Y
        y <= (buttons_.at(i)->getPosition().y_ +
              dynamic_cast<Button*>(buttons_.at(i))->button_height_ * 0.5F) &&
        // mouser cursor above bottom Y
        y >= (buttons_.at(i)->getPosition().y_ -
              dynamic_cast<Button*>(buttons_.at(i))->button_height_ * 0.5F) &&
        // cursor to the right of left X
        x >= (buttons_.at(i)->getPosition().x_ -
              dynamic_cast<Button*>(buttons_.at(i))->button_width_ * 0.5F) &&
        // cursor to the left of X
        x <= (buttons_.at(i)->getPosition().x_ +
              dynamic_cast<Button*>(buttons_.at(i))->button_width_ * 0.5F)) {
      return dynamic_cast<Button*>(buttons_.at(i))->button_id_;
    }
  }
  return Button::kNone;
}

void YasEngine::handleClickedButtons() {
  switch (checkWhichButtonClicked()) {
    case Button::kRestartStart:
      game_state_ = GameState::kGameplay;
      break;
    case Button::kQuit:
      game_state_ = GameState::kOutro;
      break;
    default:;
  }
}

void YasEngine::handleGameStateWhenESCbuttonPushed() {
  switch (game_state_) {
    case kIntro:
      game_state_ = GameState::kMainMenuRestart;
      break;
    case kMainMenuRestart:
      game_state_ = GameState::kOutro;
      break;
    case kGameplay:
      game_state_ = GameState::kMainMenuRestart;
      break;
    case kOutro:
      quit_ = true;
      break;
    case kLevelChangeScreen:
      game_state_ = GameState::kGameplay;
      break;
    case kYouWon:
      game_state_ = GameState::kMainMenuRestart;
      player_won_and_exited_ = true;
      break;
    default:;
  }
}

void YasEngine::handleGameStateWhenSPACEbuttonPushed() {
  switch (game_state_) {
    case kIntro:
      game_state_ = GameState::kMainMenuRestart;
      break;
    case kOutro:
      quit_ = true;
      break;
    case kLevelChangeScreen:
      game_state_ = GameState::kGameplay;
      break;
    case kGameplay:
      level_changed_ = false;
      // break;
      break;
    case kYouWon:
      game_state_ = GameState::kMainMenuRestart;
      player_won_and_exited_ = true;
      break;
    default:;
  }
}
