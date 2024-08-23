#include "yas_engine.hpp"

#include <SDL_mixer.h>

#include <bit>
#include <fstream>
#include <iostream>
#include <string>

#include "circle.hpp"
#include "collider.hpp"
#include "cosine_points_generator.hpp"
#include "fibonacci_points_generator.hpp"
#include "prime_numbers_points_generator.hpp"
#include "randomizer.hpp"
#include "sine_points_generator.hpp"
#include "yas_graphics_library.hpp"

YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize() {
  engineVersion = "YasEngine 1 | Beauty of Math 1 version: " +
                  std::to_string(MAJOR_REVISION) + "." +
                  std::to_string(MINOR_REVISION) + "." +
                  std::to_string(BUG_FIX_RELEASE) + "." +
                  std::to_string(BUILD_NUMBER);
  std::cout << engineVersion << "\n";
  readSettingsFromFile();

  srand(clock());

  prepareBasicSettings();
  prepareRendering();
  preparePlayer();
  prepareGameWorld();
  prepareSoundAndMusic();
  prepareInterface();

  writer.initialize();

  surfaceWithMathBasedEffects = new SurfaceWithMathBasedEffects(
      0, static_cast<int>(windowDimensions->y * 0.5F),
      static_cast<int>(windowDimensions->x * 0.5F),
      static_cast<int>(windowDimensions->y), kBlack);
}

void YasEngine::clean() {
  for (auto drawableObject : objectsToDraw) {
    delete drawableObject;
  }

  delete surfaceWithMathBasedEffects;
  delete pixelsTable;
  delete windowDimensions;

  delete sinePicture;
  delete cosinePicture;
  delete fibonacciePicture;
  delete primeNumbersPicture;

  delete mousePositionChangeInformation;

  // delete player; // will be deleted in the loop at the beginning of that
  // method

  delete input;

  Mix_FreeChunk(shootSound);
  Mix_FreeChunk(hitSound);
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  Mix_Quit();
  SDL_DestroyTexture(screenTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void YasEngine::YasEngineStart() {
  TimePicker timePicker = TimePicker();
  time = timePicker.getSeconds();
  fpsTime = 0.0F;
  frames = 0;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      handleInput(event);
    }

    newTime = timePicker.getSeconds();
    deltaTime = newTime - time;
    time = newTime;

    ++frames;
    fpsTime = fpsTime + deltaTime;
    if (fpsTime >= 1.0F) {
      fps = frames / fpsTime;
      frames = 0;
      fpsTime = 0.0F;
    }

    update(deltaTime);
    render(deltaTime);
    if (levelChanged) {
      levelChanged = false;
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

  musicVolume = soundSettings["MUSIC_VOLUME"].GetInt();
  shootVolume = soundSettings["SHOOT_VOLUME"].GetInt();
  hitVolume = soundSettings["HIT_VOLUME"].GetInt();
  otherVolume = soundSettings["OTHER_VOLUME"].GetInt();
}

void YasEngine::prepareRendering() {
  pixelsTable = new PixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, kBlack);
  renderer = SDL_CreateRenderer(window, NULL);
  SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_DISABLED,
                                   SDL_SCALEMODE_NEAREST);
  screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX32,
                                    SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH,
                                    WINDOW_HEIGHT);
}

void YasEngine::prepareBasicSettings() {
  checkEndianness();

  SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO);

  windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
  Uint32 windowFlags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_BORDERLESS |
                       SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE |
                       SDL_WINDOW_OPENGL;  // SDL_WINDOW_ALWAYS_ON_TOP
  window =
      SDL_CreateWindow("YasEngine", WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

  SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  SDL_HideCursor();
}

void YasEngine::checkEndianness() {
  if constexpr (std::endian::native == std::endian::big) {
    std::cout << "BIG ENDIAN" << std::endl;
    endianness = 0;
  } else {
    if (std::endian::native == std::endian::little) {
      std::cout << "LITTLE ENDIAN" << std::endl;
      endianness = 1;
    } else {
      std::cout << "MIXED ENDIAN" << std::endl;
      endianness = 2;
    }
  }
}

void YasEngine::drawHudElements(double& deltaTime) {
  drawCrossHair(mouseX, mouseY, *pixelsTable, false);
}

void YasEngine::drawFrame(double& deltaTime) {
  drawHorizontalLine(*pixelsTable,
                     static_cast<int>(mapFrame.top_line_segment.point0.x),
                     static_cast<int>(mapFrame.top_line_segment.point1.x),
                     static_cast<int>(mapFrame.top_line_segment.point0.y), kRed);
  drawHorizontalLine(
      *pixelsTable, static_cast<int>(mapFrame.bottom_line_segment.point0.x),
      static_cast<int>(mapFrame.bottom_line_segment.point1.x),
      static_cast<int>(mapFrame.bottom_line_segment.point0.y), kGreen);

  drawVerticalLine(*pixelsTable,
                   static_cast<int>(mapFrame.left_line_segment.point0.y),
                   static_cast<int>(mapFrame.left_line_segment.point1.y),
      static_cast<int>(mapFrame.left_line_segment.point0.x), kYellow);
  drawVerticalLine(
      *pixelsTable, static_cast<int>(mapFrame.right_line_segment.point0.y),
      static_cast<int>(mapFrame.right_line_segment.point1.y),
      static_cast<int>(mapFrame.right_line_segment.point0.x), kYellow);
}

void YasEngine::handleInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_QUIT) {
    quit = true;
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
        input->up = true;
        break;
      case SDLK_S:
        input->down = true;
        break;
      case SDLK_A:
        input->left = true;
        break;
      case SDLK_D:
        input->right = true;
        break;
      case SDLK_O:
        input->test_o_button = true;
        break;
      case SDLK_RETURN:
        if (gameState == kLevelChangeScreen) {
          gameState = GameState::kGameplay;
        }
        if (gameState == GameState::kYouWon) {
          gameState = GameState::kMainMenuRestart;
          playerWonAndExited = true;
        }
        break;
      case SDLK_TAB:
        if (gameState == kLevelChangeScreen) {
          gameState = GameState::kGameplay;
        }
        if (gameState == GameState::kYouWon) {
          gameState = GameState::kMainMenuRestart;
          playerWonAndExited = true;
        }
        break;
      default:;
    }
  }

  if (event.type == SDL_EVENT_KEY_UP) {
    switch (event.key.key) {
      case SDLK_W:
        input->up = false;
        break;
      case SDLK_S:
        input->down = false;
        break;
      case SDLK_A:
        input->left = false;
        break;
      case SDLK_D:
        input->right = false;
        break;
      case SDLK_O:
        if (input->test_o_button == true) {
          Mix_PlayChannel(-1, otherSound, 0);
          input->test_o_button = false;
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
    switch (gameState) {
      case kGameplay:
        player->is_shooting_ = true;

        break;
      case kMainMenuRestart:
        handleClickedButtons();
        break;
      case kIntro:
        gameState = GameState::kMainMenuRestart;
        break;
      case kOutro:
        quit = true;
        break;
      default:;
    }
  }

  if (event.type == SDL_EVENT_MOUSE_BUTTON_UP &&
      event.button.button == SDL_BUTTON_LEFT) {
    switch (gameState) {
      case kGameplay:
        player->is_shooting_ = false;
        break;
    }
  }
}

void YasEngine::handleMouseMovement() {
  float x;
  float y;
  SDL_GetMouseState(&x, &y);
  mousePositionChangeInformation->mouseMoved = true;
  mousePositionChangeInformation->x = x;
  mousePositionChangeInformation->y = y;
  mouseX = static_cast<float>(mousePositionChangeInformation->x);
  mouseY = static_cast<float>(mousePositionChangeInformation->y);

  windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);
}

void YasEngine::deleteNotAliveObjects() {
  for (int i = 0; i < objectsToDraw.size(); i++) {
    if (objectsToDraw[i]->is_alive_ == false) {
      objectsToDraw.erase(objectsToDraw.begin() + i);
    }
  }
}

void YasEngine::handleSpawningCollectibles() {
  for (int i = 0; i < 8; i++) {
    int randomSpawner = Randomizer::drawNumberClosedInterval(0, 15);
    int firstLevelNodeIndex = spawnersPositions[randomSpawner]->firstLevelNode;
    int secondLevelNodeIndex =
        spawnersPositions[randomSpawner]->secondLevelNode;
    if (Spawner::number_of_spawned_objects_ < MAX_COLLECTIBLES_TO_SPAWN) {
      if (isObjectInSameQuarterAsProtagonist(randomSpawner)) {
        continue;
      }
      spawners->child_nodes_[firstLevelNodeIndex]
          ->child_nodes_[secondLevelNodeIndex]
          ->spawner_->spawnObject(go);
      if (go != nullptr) {
        Spawner::number_of_spawned_objects_++;
        objectsToDraw.push_back(go);
        go = nullptr;
      }
    } else {
      spawners->child_nodes_[firstLevelNodeIndex]
          ->child_nodes_[secondLevelNodeIndex]
          ->spawner_->resetTimes();
    }
  }
}

bool YasEngine::isObjectInSameQuarterAsProtagonist(int randomSpawner) {
  int quarterSize =
      spawners->child_nodes_[spawnersPositions[randomSpawner]->firstLevelNode]
          ->child_nodes_[spawnersPositions[randomSpawner]->secondLevelNode]
          ->size_;
  return (
      (player->getPosition().x <
       (spawners->child_nodes_[spawnersPositions[randomSpawner]->firstLevelNode]
            ->child_nodes_[spawnersPositions[randomSpawner]->secondLevelNode]
            ->position_->x +
        quarterSize / 2)) &&
      (player->getPosition().x >
       (spawners->child_nodes_[spawnersPositions[randomSpawner]->firstLevelNode]
            ->child_nodes_[spawnersPositions[randomSpawner]->secondLevelNode]
            ->position_->x -
        quarterSize / 2)) &&
      (player->getPosition().y <
       (spawners->child_nodes_[spawnersPositions[randomSpawner]->firstLevelNode]
            ->child_nodes_[spawnersPositions[randomSpawner]->secondLevelNode]
            ->position_->y +
        quarterSize / 2)) &&
      (player->getPosition().y >
       (spawners->child_nodes_[spawnersPositions[randomSpawner]->firstLevelNode]
            ->child_nodes_[spawnersPositions[randomSpawner]->secondLevelNode]
            ->position_->y -
        quarterSize / 2)));
}

void YasEngine::handleProjectiles() {
  Projectile* projectile = player->shoot();

  if (projectile != nullptr) {
    Mix_PlayChannel(-1, shootSound, 0);
    objectsToDraw.push_back(projectile);
  }

  if (projectile != nullptr) {
    projectile = nullptr;
  }
}

void YasEngine::handlePlayer() {
  if (mousePositionChangeInformation->mouseMoved || input->up || input->down ||
      input->left || input->right) {
    player->rotateToMousePositionInLocalCoordinateSystem(
        static_cast<float>(mousePositionChangeInformation->x),
        static_cast<float>(mousePositionChangeInformation->y),
        windowDimensions);
  }
}

void YasEngine::preparePlayer() {
  srand(clock());
  int sizeOfkGameplaySpace = static_cast<int>(windowDimensions->x * 0.25F);
  int x = Randomizer::drawNumberClosedInterval(0, sizeOfkGameplaySpace) - 64;
  int y = Randomizer::drawNumberClosedInterval(0, sizeOfkGameplaySpace) - 64;

  player = new Player(static_cast<float>((-sizeOfkGameplaySpace) + x), 0.0F + y);
  player->setColor(kYellow);
  player->setInput(input);
  player->setInput(mousePositionChangeInformation);
  objectsToDraw.push_back(player);
}

void YasEngine::update(double& deltaTime) {
  if (levelChanged) {
    for (int i = 0; i < objectsToDraw.size(); i++) {
      if (objectsToDraw[i]->i_am_ != GameObject::kProtagonist) {
        objectsToDraw[i]->is_alive_ = false;
      }
    }
    Spawner::number_of_spawned_objects_ = 0;
  }

  deleteNotAliveObjects();

  switch (gameState) {
    case kGameplay:
      handleSpawningCollectibles();
      handlePhysics();
      if (levelChanged) {
        gameState = kLevelChangeScreen;
      }
      if (levelChanged && level == -1) {
        gameState = GameState::kYouWon;
      }
      moveObjects();
      handleProjectiles();
      handlePlayer();
      break;
  }

  if (playerWonAndExited) {
    resetAll();
  }
}

void YasEngine::resetAll() {
  deleteNotAliveObjects();
  level = 1;
  previousLevel = 0;
  levelChanged = false;
  sinePointsHarvested = 0;
  cosinePointsHarvested = 0;
  primesPointsHarvested = 0;
  fibbsPointsHarvested = 0;
  playerWonAndExited = false;
}

void YasEngine::render(double& deltaTime) {
  pixelsTable->clearColor(kBlack);
  surfaceWithMathBasedEffects->clearColor(kBlack);

  switch (gameState) {
    case kIntro:
      writer.write((-238) / 2, 200, "BEOUTY.OF.MATH", kLightBlue, *pixelsTable);
      // TODO write title and version and tha game is powekRed by YasEngine
      writer.write((-170) / 2, 100, "POWEkRed.BY", kRed, *pixelsTable);
      writer.write((-170) / 2, 0, "YAS.ENGINE", kYellow, *pixelsTable);
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
      writer.write((-37 * 17) / 2, 350, "GAME.DESIGN.PROGRAMMING.AND.MARKETING",
                   kLightBlue, *pixelsTable);
      writer.write((-14 * 17) / 2, 325, "LUKASZ.SAWICKI", kPurple, *pixelsTable);
      writer.write((-22 * 17) / 2, 275, "SOUND.DESIGN.AND.MUSIC", kLightBlue,
                   *pixelsTable);
      writer.write((-17 * 17) / 2, 250, "JAKUB.TWAROGOWSKI", kPurple,
                   *pixelsTable);
      writer.write((-17 * 17) / 2, 200, "QUALITY.ASSURANCE", kLightBlue,
                   *pixelsTable);
      writer.write((-15 * 17) / 2, 175, "BARTLOMIEJ.KAWA", kPurple,
                   *pixelsTable);
      writer.write((-15 * 17) / 2, 125, "SPECIAL.THANKS:", kGreen, *pixelsTable);
      writer.write((-22 * 17) / 2, 75, "MY.DEAR.SISTER.IZABELA", kYellow,
                   *pixelsTable);
      writer.write((-15 * 17) / 2, 50, "MY.LOVE.MARIOLA", kYellow, *pixelsTable);
      writer.write((-50 * 17) / 2, 0,
                   "MY.FRIENDS.FROM.WARSAW.SCHOOL.OF.COMPUTER.SCIENCE:", kBlue,
                   *pixelsTable);
      writer.write((-36 * 17) / 2, -25, "LUKASZ.KRZYSZTOF.MICHAL.MAREK.TOMASZ",
                   kYellow, *pixelsTable);
      writer.write((-21 * 17) / 2, -75, "MY.FRENDS.FROM.GDS.4:", kBlue,
                   *pixelsTable);
      writer.write((-17 * 17) / 2, -100, "KASIA.AND.BARTOSZ", kYellow,
                   *pixelsTable);
      writer.write((-31 * 17) / 2, -150, "WHOLE.COMMUNITY.OF.KNTG.POLYGON",
                   kPolygon, *pixelsTable);
      writer.write((-31 * 17) / 2, -200, "AND.ALL.MEMBERS.OF.TEAM.XPORTAL",
                   kXportal, *pixelsTable);

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

  SDL_UpdateTexture(screenTexture, NULL, pixelsTable->pixels, WINDOW_WIDTH * 4);
  SDL_RenderTexture(renderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void YasEngine::renderGameObjects(double& deltaTime) {
  for (auto object : objectsToDraw) {
    if (object->is_alive_) {
      // TODO if gamestate == kGameplay

      drawPolygon(object, *pixelsTable);
    }
  }
}

void YasEngine::renderOnViewports(double& deltaTime) {
  if (tests) {
    surfaceWithMathBasedEffects->drawCartesianAxies();
  }

  switch (level) {
    case 1:
      surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(
          primeNumbersPicture->points_set_->points,
          primeNumbersPicture->base_points_fuel_, primesPointsHarvested,
          kLightBlue, false);
      break;

    case 2:
      surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(
          fibonacciePicture->points_set_->points,
          fibonacciePicture->base_points_fuel_, fibbsPointsHarvested, kPurple,
          false);
      break;
    case 3:
      surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(
          sinePicture->points_set_->points, sinePicture->base_points_fuel_,
          sinePointsHarvested, kBlue, true);
      break;
    case 4:
      surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(
          cosinePicture->points_set_->points, cosinePicture->base_points_fuel_,
          cosinePointsHarvested, kRed, true);
      break;
    default:;
  }

  surfaceWithMathBasedEffects->copyPixelsInToPIxelTable(*pixelsTable);
}

void YasEngine::renderLevelChange() {
  switch (previousLevel) {
    case 1:

      writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.1", kLightBlue,
                   *pixelsTable);
      writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                   *pixelsTable);
      writer.write((-221) / 2, 0, "PRIME.NUMBERS", kGreen, *pixelsTable);
      break;
    case 2:
      writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", kLightBlue,
                   *pixelsTable);
      writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                   *pixelsTable);
      writer.write((-289) / 2, 0, "FIBONACCI.NUMBERS", kGreen, *pixelsTable);
      break;
    case 3:
      writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", kLightBlue,
                   *pixelsTable);
      writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                   *pixelsTable);
      writer.write((-221) / 2, 0, "SINE.FUNCTION", kGreen, *pixelsTable);
      break;
    case 4:
      writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", kLightBlue,
                   *pixelsTable);
      writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", kBlue,
                   *pixelsTable);
      writer.write((-255) / 2, 0, "COSINE.FUNCTION", kGreen, *pixelsTable);
      writer.write((-187) / 2, -25, "AND.YOU.WON", kYellow, *pixelsTable);
      break;
    default:;
  }
}

void YasEngine::renderWonScreen() {
  writer.write((-119) / 2, 310, "YOU.WON", kLightBlue, *pixelsTable);
  writer.write((-408) / 2, 210, "MATHEMATICS.IS.BEAUTIFUL", kYellow,
               *pixelsTable);
  writer.write((-578) / 2, 110, "YOU.ARE.NOT.SUPPOSED.TO.BELIEVE.ME", kPurple,
               *pixelsTable);
  writer.write((-357) / 2, 10, "CHECK.IT.FOR.YOURSELF", kPurple, *pixelsTable);
  writer.write((-935) / 2, -10,
               "FIND.AND.LEARN.MORE.ABOUT.WHAT.YOU.HAVE.JUST.DISCOVEkRed",
               kPurple, *pixelsTable);
  writer.write((-221) / 2, -110, "PRIME.NUMBERS", kGreen, *pixelsTable);
  writer.write((-289) / 2, -160, "FIBONACCI.NUMBERS", kYellow, *pixelsTable);
  writer.write((-425) / 2, -210, "SINE.AND.COSINE.FUNCTIONS", kLightBlue,
               *pixelsTable);
}

void YasEngine::handlePhysics() {
  if (objectsToDraw.size() >= 3) {
    for (int i = 0; i < static_cast<int>(objectsToDraw.size() - 2); i++) {
      if (objectsToDraw[i]->i_am_ == GameObject::kCollectible) {
        handleCollectiblesWithWallsCollisions(objectsToDraw[i]);
      }

      if (objectsToDraw[i]->i_am_ == GameObject::kProtagonist) {
        handleProtagonistWithWallsCollisions(objectsToDraw[i]);
      }

      for (int j = i; j < static_cast<int>(objectsToDraw.size()); j++) {
        if (objectsToDraw[i] == objectsToDraw[j] ||
            (objectsToDraw[i]->i_am_ == GameObject::kProjectile &&
             objectsToDraw[j]->i_am_ == GameObject::kProjectile) ||
            (objectsToDraw[i]->i_am_ == GameObject::kProjectile &&
             objectsToDraw[j]->i_am_ == GameObject::kProtagonist) ||
            (objectsToDraw[i]->i_am_ == GameObject::kProtagonist &&
             objectsToDraw[j]->i_am_ == GameObject::kProjectile) ||
            (objectsToDraw[i]->i_am_ == GameObject::kCollectible &&
             objectsToDraw[j]->i_am_ == GameObject::kCollectible)) {
          continue;
        }

        // LEFT Projectile <-> Collectible && Protagonist <-> Collectible)
        if (objectsToDraw[i]->is_alive_ && objectsToDraw[j]->is_alive_) {
          GameObject* protagonist =
              getProtagonist(objectsToDraw[i], objectsToDraw[j]);
          GameObject* gameObj =
              getNotProtagonist(objectsToDraw[i], objectsToDraw[j]);

          if ((protagonist != nullptr) &&
              gameObj->i_am_ == GameObject::kCollectible &&
              !gameObj->collider_.isInCollision &&
              Collider::isCollision(objectsToDraw[i]->collider_,
                                    objectsToDraw[j]->collider_)) {
            // handleBuildingGraph
            handleDisassemblingGraphs(gameObj);

            gameObj->collider_.isInCollision = true;
          }

          // if exited from collision
          if ((protagonist != nullptr) &&
              gameObj->i_am_ == GameObject::kCollectible &&
              gameObj->collider_.isInCollision &&
              !Collider::isCollision(objectsToDraw[i]->collider_,
                                     objectsToDraw[j]->collider_)) {
            gameObj->collider_.isInCollision = false;
          }

          if ((protagonist == nullptr) &&
              Collider::isCollision(objectsToDraw[i]->collider_,
                                    objectsToDraw[j]->collider_)) {
            objectsToDraw[i]->is_alive_ = false;
            objectsToDraw[j]->is_alive_ = false;
            Mix_PlayChannel(-1, hitSound, 0);

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
  if (primesPointsHarvested < 0) {
    primesPointsHarvested = 0;
    return;
  }
  if (fibbsPointsHarvested < 0) {
    fibbsPointsHarvested = 0;
    return;
  }
  if (sinePointsHarvested < 0) {
    sinePointsHarvested = 0;
    return;
  }
  if (cosinePointsHarvested < 0) {
    cosinePointsHarvested = 0;
    return;
  }

  switch (level) {
    case 1:
      primesPointsHarvested -= gameObj->number_of_vertices_;
      break;

    case 2:

      fibbsPointsHarvested -= gameObj->number_of_vertices_;
      break;

    case 3:

      sinePointsHarvested -= gameObj->number_of_vertices_;
      break;

    case 4:

      cosinePointsHarvested -= gameObj->number_of_vertices_;
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
      primesPointsHarvested + gameObj->number_of_vertices_;
  int newValueOfFibbsPointsHarvested =
      fibbsPointsHarvested + gameObj->number_of_vertices_;
  int newSinePointsHarvested =
      sinePointsHarvested + gameObj->number_of_vertices_;
  int newCosinePointsHarvested =
      cosinePointsHarvested + gameObj->number_of_vertices_;

  int test1 = primesPointsHarvested;

  if (level == 1 && newValueOfPrimesPointsHarvested >=
                        primeNumbersPicture->base_points_fuel_) {
    primesPointsHarvested = primeNumbersPicture->base_points_fuel_;
    previousLevel = level;
    level = 2;
    levelChanged = true;
    return;
  }

  if (level == 2 &&
      newValueOfFibbsPointsHarvested >= fibonacciePicture->base_points_fuel_) {
    fibbsPointsHarvested = fibonacciePicture->base_points_fuel_;
    previousLevel = level;
    level = 3;
    levelChanged = true;
    return;
  }

  int some = sinePointsHarvested;

  if (level == 3 && newSinePointsHarvested >= sinePicture->base_points_fuel_) {
    sinePointsHarvested = sinePicture->base_points_fuel_;
    previousLevel = level;
    level = 4;
    levelChanged = true;
    return;
  }

  if (level == 4 &&
      newCosinePointsHarvested >= cosinePicture->base_points_fuel_) {
    cosinePointsHarvested = cosinePicture->base_points_fuel_;
    previousLevel = level;
    level = -1;
    levelChanged = true;
    return;
  }

  switch (level) {
    case 1:

      if (newValueOfPrimesPointsHarvested <=
          primeNumbersPicture->base_points_fuel_) {
        primesPointsHarvested = newValueOfPrimesPointsHarvested;
      }
      break;
    case 2:

      if (newValueOfFibbsPointsHarvested <=
          fibonacciePicture->base_points_fuel_) {
        fibbsPointsHarvested = newValueOfFibbsPointsHarvested;
      }

      break;
    case 3:

      if (newSinePointsHarvested <= sinePicture->base_points_fuel_) {
        sinePointsHarvested = newSinePointsHarvested;
      }

      break;
    case 4:

      if (newCosinePointsHarvested <= cosinePicture->base_points_fuel_) {
        cosinePointsHarvested = newCosinePointsHarvested;
      }

      break;
    default:;
  }
}

void YasEngine::handleCollectiblesWithWallsCollisions(GameObject* object) {
  float leftWall = mapFrame.left_line_segment.point0.x;
  float rightWall = mapFrame.right_line_segment.point0.x;
  float topWall = mapFrame.top_line_segment.point0.y;
  float bottomWall = mapFrame.bottom_line_segment.point0.y;

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
  float leftWall = mapFrame.left_line_segment.point0.x;
  float rightWall = mapFrame.right_line_segment.point0.x;
  float topWall = mapFrame.top_line_segment.point0.y;
  float bottomWall = mapFrame.bottom_line_segment.point0.y;

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
      normal.x = 1;
      normal.y = 0;
      break;
    case kRight:
      normal.x = -1;
      normal.y = 0;
      break;
    case kTop:
      normal.x = 0;
      normal.y = -1;
      break;
    case kBottom:
      normal.x = 0;
      normal.y = 1;
      break;
    default:;
      break;
  }

  float dotProduct = Vector2D<float>::dotProduct(gameObject->velocity_, normal);
  Vector2D<float>::multiplyByScalar(&normal, dotProduct * 2.0f);
  Vector2D<float>::substract(&gameObject->velocity_, normal);

  // TO PREVENT COLLECTIBLE STUCK IN THE WALL
  // objectsToDraw[i]->setX(rightWall - objectsToDraw[i]->collider.radius - 1);
}

void YasEngine::moveObjectToMapBoundries(GameObject* gameObject, Wall wall,
                                         int shift) {
  switch (wall) {
    case kLeft:
      gameObject->setX(mapFrame.left_line_segment.point0.x +
                       gameObject->collider_.radius + shift);
      break;
    case kRight:
      gameObject->setX(mapFrame.right_line_segment.point0.x -
                       gameObject->collider_.radius - shift);
      break;
    case kTop:
      gameObject->setY(mapFrame.top_line_segment.point0.y -
                       gameObject->collider_.radius - shift);
      break;
    case kBottom:
      gameObject->setY(mapFrame.bottom_line_segment.point0.y +
                       gameObject->collider_.radius + shift);
      break;
    default:;
      break;
  }
}

void YasEngine::moveObjects() {
  for (auto object : objectsToDraw) {
    if (object->is_alive_) {
      object->Move(static_cast<float>(deltaTime));
      object->regeneratePolygon();
    }
  }
}

void YasEngine::prepareSoundAndMusic() {
  audioSpecs.freq = 44100;
  audioSpecs.format = MIX_DEFAULT_FORMAT;
  audioSpecs.channels = 2;

  if (Mix_OpenAudio(0, &audioSpecs) < 0) {
    std::cout << "Error cannot open audio device" << std::endl;
  }

  Mix_Init(MIX_DEFAULT_FORMAT);

  music = Mix_LoadMUS("music.wav");
  if (music == NULL) {
    std::cout << "Error while loading music. Cannot load music." << std::endl;
    std::cout << "SDL message: " << SDL_GetError() << std::endl
              << " | Mix library error: " << Mix_GetError() << std::endl;
    quit = true;
  }

  Mix_VolumeMusic(musicVolume);
  // Mix_VolumeMusic

  shootSound = Mix_LoadWAV("shoot.wav");
  Mix_VolumeChunk(shootSound, shootVolume);

  hitSound = Mix_LoadWAV("hit.wav");
  Mix_VolumeChunk(hitSound, hitVolume);

  otherSound = Mix_LoadWAV("other.wav");
  Mix_VolumeChunk(otherSound, otherVolume);

  if (shootSound == NULL || hitSound == NULL || otherSound == NULL) {
    std::cout << "Error while loading sounds. Cannot load sounds." << std::endl;
    std::cout << "SDL message: " << SDL_GetError() << std::endl
              << " | Mix library error: " << Mix_GetError() << std::endl;
    quit = true;
  }
  Mix_PlayMusic(music, 999);
}

void YasEngine::prepareGameWorld() {
  // srand(clock());

  int mainNodeX = -(windowDimensions->x / 4);
  int mainNodeY = 0;

  std::cout << "Main node X: " << mainNodeX << "\n";
  std::cout << "Main node Y: " << mainNodeY << "\n";

  spawners = new Node(new Vector2D<int>(-(windowDimensions->x / 4), 0),
                      windowDimensions->x / 2, nullptr);

  // adding nodes(first level) to head node
  Node::addNodes(*spawners);
  for (int i = 0; i < 4; i++) {
    // adding nodes(second level) to nodes
    Node::addNodes(*spawners->child_nodes_[i]);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      spawnersPositions.push_back(new NodeNumbersOnTwoProceedingLevels(i, j));
    }
  }

  int drawnNumbers = 0;  // PL - wylosowane a nie narysowane w tym kontekscie
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

  // calculate position_ of player on tree 1 - level of nodes and number of node
  // and 2 level of node and number
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (player->getPosition().x >=
              (spawners->child_nodes_[i]->child_nodes_[j]->position_->x -
               spawners->child_nodes_[i]->child_nodes_[j]->size_ * 0.5) &&
          player->getPosition().x <
              (spawners->child_nodes_[i]->child_nodes_[j]->position_->x +
               spawners->child_nodes_[i]->child_nodes_[j]->size_ * 0.5) &&
          player->getPosition().y <=
              (spawners->child_nodes_[i]->child_nodes_[j]->position_->y +
               spawners->child_nodes_[i]->child_nodes_[j]->size_ * 0.5) &&
          player->getPosition().y >
              (spawners->child_nodes_[i]->child_nodes_[j]->position_->y -
               spawners->child_nodes_[i]->child_nodes_[j]->size_ * 0.5)) {
        playerPosition.firstLevelNode = i;
        playerPosition.secondLevelNode = j;
        goto afterFor;
      }
    }
  }
afterFor:

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      spawners->child_nodes_[i]->child_nodes_[j]->spawner_ =
          new Spawner(spawners->child_nodes_[i]->child_nodes_[j]->position_->x,
                      spawners->child_nodes_[i]->child_nodes_[j]->position_->y);
    }
  }

  numberOfGivenColors.insert({"kRed", 0});
  numberOfGivenColors.insert({"GREEN", 0});
  numberOfGivenColors.insert({"kBlue", 0});
  numberOfGivenColors.insert({"YELLOW", 0});
  prepareDataForDrawingGraphs();
}

void YasEngine::setFrameAroundGameplaySpace() {
  const int VERTHICAL_SHIFT = 10;
  const int HORIZONTAL_SHIFT = 10;

  // HORIZONTAL LINE SEGMENTS

  // Top              ---->
  // Left point
  mapFrame.top_line_segment.point0.x =
      static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.top_line_segment.point0.y =
      static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);
  // Right point
  mapFrame.top_line_segment.point1.x =
      static_cast<float>(-1 - HORIZONTAL_SHIFT);
  mapFrame.top_line_segment.point1.y =
      static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);

  // Bottom
  // Left point
  mapFrame.bottom_line_segment.point0.x =
      static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.bottom_line_segment.point0.y =
      static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);

  // Right point
  mapFrame.bottom_line_segment.point1.x = static_cast<float>(-HORIZONTAL_SHIFT);
  mapFrame.bottom_line_segment.point1.y =
      static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);

  // VERTICAL LINE SEGMENTS
  // Left
  // Top point
  mapFrame.left_line_segment.point0.x =
      static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.left_line_segment.point0.y =
      static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);
  // Bottom point
  mapFrame.left_line_segment.point1.x =
      static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.left_line_segment.point1.y =
      static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);

  // Right
  // Top point
  mapFrame.right_line_segment.point0.x =
      static_cast<float>(-1 - HORIZONTAL_SHIFT);
  mapFrame.right_line_segment.point0.y =
      static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);
  // Bottom point
  mapFrame.right_line_segment.point1.x =
      static_cast<float>(-1 - HORIZONTAL_SHIFT);
  mapFrame.right_line_segment.point1.y =
      static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);
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
  sinePointsHarvested = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>>
  // pairNumbersMap;

  std::map<int, std::map<float, float>> numbekRedSines;

  pairNumbersMap.insert(
      std::pair<std::string, std::map<int, std::map<float, float>*>*>(
          "Sines", new std::map<int, std::map<float, float>*>));

  // for (int i = 0; i < sinuses->size_(); i++)
  // {
  int i = 0;
  for (std::pair<float, float> pair : *sines) {
    std::map<float, float>* m = new std::map<float, float>();
    m->insert(pair);
    pairNumbersMap.at("Sines")->insert(
        std::pair<int, std::map<float, float>*>(i, m));
  }

  // }

  sinePicture = new MathPicture(sines, new SinePointsGenerator());
}

void YasEngine::prepareCosineDrawing() {
  std::map<float, float>* cosines =
      generateCosineNumbers(40);  // generatePrimeNumbersLessThanN(1000);
  cosinePointsHarvested = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>>
  // pairNumbersMap;

  std::map<int, std::map<float, float>> numbekRedSines;

  pairNumbersMap.insert(
      std::pair<std::string, std::map<int, std::map<float, float>*>*>(
          "Cosines", new std::map<int, std::map<float, float>*>));

  // for (int i = 0; i < sinuses->size_(); i++)
  // {
  int i = 0;
  for (std::pair<float, float> pair : *cosines) {
    std::map<float, float>* m = new std::map<float, float>();
    m->insert(pair);
    pairNumbersMap.at("Cosines")->insert(
        std::pair<int, std::map<float, float>*>(i, m));
  }

  // }

  cosinePicture = new MathPicture(cosines, new CosinePointsGenerator());
}

void YasEngine::prepareFibonacciDrawing() {
  std::vector<int> fibbs = generateNfibonacciNumbers(40);
  fibbsPointsHarvested = 0;

  numbersMap.insert(std::pair<std::string, std::map<int, float>*>(
      "Fibbs", new std::map<int, float>));

  for (int i = 0; i < fibbs.size(); i++) {
    numbersMap.at("Fibbs")->insert(std::pair<int, int>(i, fibbs.at(i)));
  }

  fibonacciePicture =
      new MathPicture(numbersMap.at("Fibbs"), new FibonacciPointsGenerator());
}

void YasEngine::preparePrimesDrawing() {
  std::vector<int> primes = generatePrimeNumbersLessThanN(1000);
  primesPointsHarvested = 0;

  numbersMap.insert(std::pair<std::string, std::map<int, float>*>(
      "Primes", new std::map<int, float>));

  for (int i = 0; i < primes.size(); i++) {
    numbersMap.at("Primes")->insert(std::pair<int, int>(i, primes.at(i)));
  }

  primeNumbersPicture = new MathPicture(numbersMap.at("Primes"),
                                        new PrimeNumbersPointsGenerator());

  std::cout << "prepakRedPrimesDrawing" << "\n";
}

void YasEngine::prepareInterface() {
  // Button 1
  buttons.push_back(new Button(Button::kRestartStart, "START", kRed));
  buttons.at(0)->setPosition(0, 50);
  dynamic_cast<Button*>(buttons.at(0))->horizontal_margin_ = 10;
  dynamic_cast<Button*>(buttons.at(0))->vertical_margin_ = 5;
  dynamic_cast<Button*>(buttons.at(0))->button_width_ =
      writer.kfont_width *
          static_cast<int>(dynamic_cast<Button*>(buttons.at(0))->text_.size()) +
      2 * dynamic_cast<Button*>(buttons.at(0))->horizontal_margin_;
  dynamic_cast<Button*>(buttons.at(0))->button_height_ =
      writer.kfont_height +
      2 * dynamic_cast<Button*>(buttons.at(0))->vertical_margin_;
  buttons.at(0)->local_vertices_ = new Vector2D<float>[4];
  buttons.at(0)->world_vertices_ = new Vector2D<float>[4];
  buttons.at(0)->local_vertices_[0].x =
      0 - dynamic_cast<Button*>(buttons.at(0))->button_width_ * 0.5F;
  buttons.at(0)->local_vertices_[0].y =
      0 + dynamic_cast<Button*>(buttons.at(0))->button_height_ * 0.5F;
  buttons.at(0)->local_vertices_[1].x =
      0 + dynamic_cast<Button*>(buttons.at(0))->button_width_ * 0.5F;
  buttons.at(0)->local_vertices_[1].y =
      0 + dynamic_cast<Button*>(buttons.at(0))->button_height_ * 0.5F;
  buttons.at(0)->local_vertices_[2].x =
      0 + dynamic_cast<Button*>(buttons.at(0))->button_width_ * 0.5F;
  buttons.at(0)->local_vertices_[2].y =
      0 - dynamic_cast<Button*>(buttons.at(0))->button_height_ * 0.5F;
  buttons.at(0)->local_vertices_[3].x =
      0 - dynamic_cast<Button*>(buttons.at(0))->button_width_ * 0.5F;
  buttons.at(0)->local_vertices_[3].y =
      0 - dynamic_cast<Button*>(buttons.at(0))->button_height_ * 0.5F;
  buttons.at(0)->generate();

  // Button 2
  buttons.push_back(new Button(Button::kQuit, "QUIT", kYellow));
  buttons.at(1)->setPosition(0, -50);
  dynamic_cast<Button*>(buttons.at(1))->horizontal_margin_ = 10;
  dynamic_cast<Button*>(buttons.at(1))->vertical_margin_ = 5;
  dynamic_cast<Button*>(buttons.at(1))->button_width_ =
      writer.kfont_width *
          static_cast<int>(dynamic_cast<Button*>(buttons.at(1))->text_.size()) +
      2 * dynamic_cast<Button*>(buttons.at(1))->horizontal_margin_;
  dynamic_cast<Button*>(buttons.at(1))->button_height_ =
      writer.kfont_height +
      2 * dynamic_cast<Button*>(buttons.at(1))->vertical_margin_;
  buttons.at(1)->local_vertices_ = new Vector2D<float>[4];
  buttons.at(1)->world_vertices_ = new Vector2D<float>[4];
  buttons.at(1)->local_vertices_[0].x =
      0 - dynamic_cast<Button*>(buttons.at(1))->button_width_ * 0.5F;
  buttons.at(1)->local_vertices_[0].y =
      0 + dynamic_cast<Button*>(buttons.at(1))->button_height_ * 0.5F;
  buttons.at(1)->local_vertices_[1].x =
      0 + dynamic_cast<Button*>(buttons.at(1))->button_width_ * 0.5F;
  buttons.at(1)->local_vertices_[1].y =
      0 + dynamic_cast<Button*>(buttons.at(1))->button_height_ * 0.5F;
  buttons.at(1)->local_vertices_[2].x =
      0 + dynamic_cast<Button*>(buttons.at(1))->button_width_ * 0.5F;
  buttons.at(1)->local_vertices_[2].y =
      0 - dynamic_cast<Button*>(buttons.at(1))->button_height_ * 0.5F;
  buttons.at(1)->local_vertices_[3].x =
      0 - dynamic_cast<Button*>(buttons.at(1))->button_width_ * 0.5F;
  buttons.at(1)->local_vertices_[3].y =
      0 - dynamic_cast<Button*>(buttons.at(1))->button_height_ * 0.5F;
  buttons.at(1)->generate();

  setFrameAroundGameplaySpace();
}

void YasEngine::drawButtons() {
  for (unsigned int i = 0; i < buttons.size(); i++) {
    drawPolygon(buttons.at(i), *pixelsTable);
    writer.write(
        static_cast<int>(buttons.at(i)->getPosition().x -
            dynamic_cast<Button*>(buttons.at(i))->button_text_width_ *
                             0.5F +
                         ScreenWriter::kfont_width * 0.5F),
        static_cast<int>(buttons.at(i)->getPosition().y),
        dynamic_cast<Button*>(buttons.at(i))->text_,
        dynamic_cast<Button*>(buttons.at(i))->color_, *pixelsTable);
  }
}

Button::ButtonId YasEngine::checkWhichButtonClicked() {
  float x = static_cast<float>(mousePositionChangeInformation->x);
  float y = static_cast<float>(mousePositionChangeInformation->y);
  windowPositionToCartesianPosition(x, y, windowDimensions);
  for (unsigned int i = 0; i < buttons.size(); i++) {
    if (
        // mouse cursor under top Y
        y <= (buttons.at(i)->getPosition().y +
              dynamic_cast<Button*>(buttons.at(i))->button_height_ * 0.5F) &&
        // mouser cursor above bottom Y
        y >= (buttons.at(i)->getPosition().y -
              dynamic_cast<Button*>(buttons.at(i))->button_height_ * 0.5F) &&
        // cursor to the right of left X
        x >= (buttons.at(i)->getPosition().x -
              dynamic_cast<Button*>(buttons.at(i))->button_width_ * 0.5F) &&
        // cursor to the left of X
        x <= (buttons.at(i)->getPosition().x +
              dynamic_cast<Button*>(buttons.at(i))->button_width_ * 0.5F)) {
      return dynamic_cast<Button*>(buttons.at(i))->button_id_;
    }
  }
  return Button::kNone;
}

void YasEngine::handleClickedButtons() {
  switch (checkWhichButtonClicked()) {
    case Button::kRestartStart:
      gameState = GameState::kGameplay;
      break;
    case Button::kQuit:
      gameState = GameState::kOutro;
      break;
    default:;
  }
}

void YasEngine::handleGameStateWhenESCbuttonPushed() {
  switch (gameState) {
    case kIntro:
      gameState = GameState::kMainMenuRestart;
      break;
    case kMainMenuRestart:
      gameState = GameState::kOutro;
      break;
    case kGameplay:
      gameState = GameState::kMainMenuRestart;
      break;
    case kOutro:
      quit = true;
      break;
    case kLevelChangeScreen:
      gameState = GameState::kGameplay;
      break;
    case kYouWon:
      gameState = GameState::kMainMenuRestart;
      playerWonAndExited = true;
      break;
    default:;
  }
}

void YasEngine::handleGameStateWhenSPACEbuttonPushed() {
  switch (gameState) {
    case kIntro:
      gameState = GameState::kMainMenuRestart;
      break;
    case kOutro:
      quit = true;
      break;
    case kLevelChangeScreen:
      gameState = GameState::kGameplay;
      break;
    case kGameplay:
      levelChanged = false;
      // break;
      break;
    case kYouWon:
      gameState = GameState::kMainMenuRestart;
      playerWonAndExited = true;
      break;
    default:;
  }
}
