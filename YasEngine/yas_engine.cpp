#include "yas_engine.hpp"

#include <SDL_mixer.h>

#include <bit>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "collider.hpp"
#include "cosine_points_generator.hpp"
#include "fibonacci_points_generator.hpp"
#include "prime_numbers_points_generator.hpp"
#include "randomizer.hpp"
#include "sine_points_generator.hpp"
#include "triangle_3d.hpp"
#include "yas_graphics_library.hpp"

YasEngine* YasEngine::instance_ = nullptr;

void YasEngine::initialize() {
  engine_version_ = "YasEngine 1 | Beauty of Math 1 version: " +
    std::to_string(MAJOR_REVISION) + "." +
    std::to_string(MINOR_REVISION) + "." +
    std::to_string(BUG_FIX_RELEASE) + "." +
    std::to_string(BUILD_NUMBER);
  std::cout << engine_version_ << "\n";
  ReadSettingsFromFile();

  srand(clock());

  PrepareBasicSettings();
  PrepareRendering();
  PreparePlayer();
  PrepareGameWorld();
  PrepareSoundAndMusic();
  PrepareInterface();
  writer_ = new ScreenWriter(window_dimensions_);
  writer_->Initialize();

}

void YasEngine::clean() {
  for (auto drawable_object : objects_to_draw_) {
    delete drawable_object;
  }

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

    // for (int i = 0; i < local_box_.size(); i++) {
    //   delete local_box_[i];
    // }
    //
    //   for (int i = 0; i < world_box_.size(); i++) {
    //   delete world_box_[i];
    // }
    //
    /////delete[] testLines;

    // std::vector<Vector4D<float>*> local_box_;
    // std::vector<Vector4D<float>*> world_box_;
    // Vector2D<float>* box_2d_;
    //
    // Vector2D<float>* testLines;

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
  time_ = timePicker.GetSeconds();
  fps_time_ = 0.0F;
  frames_ = 0;

  while (!quit_) {
    while (SDL_PollEvent(&event_)) {
      HandleInput(event_);
    }

    new_time_ = timePicker.GetSeconds();
    delta_time_ = new_time_ - time_;
    time_ = new_time_;

    ++frames_;
    fps_time_ = fps_time_ + delta_time_;
    if (fps_time_ >= 1.0F) {
      fps_ = frames_ / fps_time_;
      frames_ = 0;
      fps_time_ = 0.0F;
    }

    Update(delta_time_);
    Render(delta_time_);
    if (level_changed_) {
      level_changed_ = false;
    }
  }

  clean();
}

void YasEngine::ReadSettingsFromFile() {
  std::ifstream settings_file("settings.json");
  if (!settings_file.is_open()) {
    std::cerr << "Error opening JSON file" << std::endl;
    exit(1);
  }

  std::string settings_string((std::istreambuf_iterator<char>(settings_file)),
                              std::istreambuf_iterator<char>());
  settings_file.close();

  settings.Parse(settings_string.c_str());

  if (settings.HasParseError()) {
    std::cerr << "Error parsing JSON" << std::endl;
    exit(1);
  }

  const rapidjson::Value& sound_settings = settings["SOUND_MUSIC"];

  music_volume_ = sound_settings["MUSIC_VOLUME"].GetInt();
  shoot_volume_ = sound_settings["SHOOT_VOLUME"].GetInt();
  hit_volume_ = sound_settings["HIT_VOLUME"].GetInt();
  other_volume_ = sound_settings["OTHER_VOLUME"].GetInt();
}

void YasEngine::PrepareRendering() {
  pixels_table_ = new PixelsTable(window_width_, window_height_, kBlack);
  renderer_ = SDL_CreateRenderer(window_, NULL);
  SDL_SetRenderLogicalPresentation(renderer_, window_width_, window_height_,
                                   SDL_LOGICAL_PRESENTATION_DISABLED,
                                   SDL_SCALEMODE_NEAREST);
  screen_texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBX32,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      window_width_, window_height_);
}

void YasEngine::PrepareBasicSettings() {
  CheckEndianness();

  SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO);

      // Get the number of displays available
  SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(display_id);

  window_width_ = display_mode->w * 0.75;
  window_height_ = display_mode->h * 0.75;

  window_dimensions_ = new Vector2D<int>(window_width_, window_height_);
  Uint32 windowFlags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_BORDERLESS |
    SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE |
    SDL_WINDOW_OPENGL; // SDL_WINDOW_ALWAYS_ON_TOP
  window_ =
    SDL_CreateWindow("YasEngine", window_width_, window_height_, windowFlags);

  SDL_SetWindowMinimumSize(window_, window_width_, window_height_);
  SDL_HideCursor();
}

void YasEngine::CheckEndianness() {
  if constexpr (std::endian::native == std::endian::big) {
    std::cout << "BIG ENDIAN" << std::endl;
    endianness_ = 0;
  }
  else {
    if (std::endian::native == std::endian::little) {
      std::cout << "LITTLE ENDIAN" << std::endl;
      endianness_ = 1;
    }
    else {
      std::cout << "MIXED ENDIAN" << std::endl;
      endianness_ = 2;
    }
  }
}

void YasEngine::DrawHudElements(double& delta_time) {
  DrawCrossHair(mouse_x_, mouse_y_, *pixels_table_, false);
}

void YasEngine::HandleInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_QUIT) {
    quit_ = true;
  }
  else {
    HandleKeyboardInput(event);
    HandleMouseInput(event);
  }
}

void YasEngine::HandleKeyboardInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.key) {
    case SDLK_ESCAPE:
      HandleGameStateWhenESCbuttonPushed();
      break;
    case SDLK_SPACE:
      HandleGameStateWhenSPACEbuttonPushed();
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
    default: ;
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
    default: ;
    }
  }
}

void YasEngine::HandleMouseInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    HandleMouseMovement();
  }
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
    event.button.button == SDL_BUTTON_LEFT) {
    switch (game_state_) {
    case kGameplay:
      player_->is_shooting_ = true;

      break;
    case kMainMenuRestart:
      HandleClickedButtons();
      break;
    case kIntro:
      game_state_ = GameState::kMainMenuRestart;
      break;
    case kOutro:
      quit_ = true;
      break;
    default: ;
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

void YasEngine::HandleMouseMovement() {
  float x;
  float y;
  SDL_GetMouseState(&x, &y);
  mouse_position_change_information_->mouseMoved = true;
  mouse_position_change_information_->x = x;
  mouse_position_change_information_->y = y;
  mouse_x_ = static_cast<float>(mouse_position_change_information_->x);
  mouse_y_ = static_cast<float>(mouse_position_change_information_->y);

  WindowPositionToCartesianPosition(mouse_x_, mouse_y_, window_dimensions_);
}

void YasEngine::DeleteNotAliveObjects() {
  for (int i = 0; i < objects_to_draw_.size(); i++) {
    if (objects_to_draw_[i]->is_alive_ == false) {
      objects_to_draw_.erase(objects_to_draw_.begin() + i);
    }
  }
}

void YasEngine::HandleSpawningCollectibles() {

}

void YasEngine::HandleProjectiles() {
  Projectile* projectile = player_->shoot();

  if (projectile != nullptr) {
    Mix_PlayChannel(-1, shoot_sound_, 0);
    objects_to_draw_.push_back(projectile);
  }

  if (projectile != nullptr) {
    projectile = nullptr;
  }
}

void YasEngine::HandlePlayer() {
  if (mouse_position_change_information_->mouseMoved || input_->up ||
    input_->down || input_->left || input_->right) {
    player_->RotateToMousePositionInLocalCoordinateSystem(
      static_cast<float>(mouse_position_change_information_->x),
      static_cast<float>(mouse_position_change_information_->y),
      window_dimensions_);
  }
}

void YasEngine::PreparePlayer() {
  srand(clock());
  int size_Of_gameplay_space = static_cast<int>(window_dimensions_->x_ * 0.25F);
  int x = Randomizer::DrawNumberClosedInterval(0, size_Of_gameplay_space) - 64;
  int y = Randomizer::DrawNumberClosedInterval(0, size_Of_gameplay_space) - 64;

  player_ =
    new Player(static_cast<float>((-size_Of_gameplay_space) + x), 0.0F + y);
  player_->set_color(kYellow);
  player_->set_input(input_);
  player_->set_input(mouse_position_change_information_);
  objects_to_draw_.push_back(player_);
}

void YasEngine::Update(double& delta_time) {
  if (level_changed_) {
    for (int i = 0; i < objects_to_draw_.size(); i++) {
      if (objects_to_draw_[i]->i_am_ != GameObject::kProtagonist) {
        objects_to_draw_[i]->is_alive_ = false;
      }
    }
    Spawner::number_of_spawned_objects_ = 0;
  }

  DeleteNotAliveObjects();

  switch (game_state_) {
  case kGameplay:
    HandleSpawningCollectibles();
    HandlePhysics();
    if (level_changed_) {
      game_state_ = kLevelChangeScreen;
    }
    if (level_changed_ && level_ == -1) {
      game_state_ = GameState::kYouWon;
    }
    MoveObjects();
    HandleProjectiles();
    HandlePlayer();
    BoxProcessing();
    break;
  }

  if (player_won_and_exited_) {
    ResetAll();
  }
  
}

void YasEngine::ResetAll() {
  DeleteNotAliveObjects();
  level_ = 1;
  previous_level_ = 0;
  level_changed_ = false;
  sine_points_harvested_ = 0;
  cosine_points_harvested_ = 0;
  primes_points_harvested_ = 0;
  fibonacci_points_harvested_ = 0;
  player_won_and_exited_ = false;
}

void YasEngine::Render(double& delta_time) {
  pixels_table_->ClearColor(kBlack);

  switch (game_state_) {
  case kIntro:
      writer_->Write(-1 * ((line_22.size() * writer_->kfont_width_) / 2),
                     writer_->vertical_top_positions_[1],
                   line_22, kLightBlue, *pixels_table_);
    writer_->Write(-1 * ((line_23.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[0],
                   line_23, kRed, *pixels_table_);
      writer_->Write(-1 * ((line_24.size() * writer_->kfont_width_) / 2),
                     writer_->vertical_bottom_positions_[0],
                   line_24, kYellow, *pixels_table_);
    break;
  case kMainMenuRestart:
    DrawButtons();
    break;
  case kGameplay:
    RenderGameObjects();
    DrawBox();
    break;
  case kOutro:
    writer_->Write(-1 * ((line_25.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[7],
                   line_25, kLightBlue, *pixels_table_);
    writer_->Write(-1 * ((line_26.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[6],
                   line_26, kPurple, *pixels_table_);
    writer_->Write(-1 * ((line_27.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[5],
                   line_27, kLightBlue, *pixels_table_);
    writer_->Write(-1 * ((line_28.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[4],
                   line_28, kPurple, *pixels_table_);
    writer_->Write(-1 * ((line_29.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[3],
                   line_29, kLightBlue, *pixels_table_);
    writer_->Write(-1 * ((line_30.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[2],
                   line_30, kPurple, *pixels_table_);
    writer_->Write(-1 * ((line_31.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[1],
                   line_31, kGreen, *pixels_table_);
    writer_->Write(-1 * ((line_32.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[0],
                   line_32, kYellow, *pixels_table_);
    writer_->Write(-1 * ((line_33.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[0],
                   line_33, kYellow, *pixels_table_);
    writer_->Write(-1 * ((line_34.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[1],
                   line_34, kBlue, *pixels_table_);
    writer_->Write(-1 * ((line_35.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[2],
                   line_35, kYellow, *pixels_table_);
    writer_->Write(-1 * ((line_36.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[3],
                   line_36, kBlue, *pixels_table_);
    writer_->Write(-1 * ((line_37.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[4],
                   line_37, kYellow, *pixels_table_);
    writer_->Write(-1 * ((line_38.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[5],
                   line_38, kPolygon, *pixels_table_);
    writer_->Write(-1 * ((line_39.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[6],
                   line_39, kXportal, *pixels_table_);

    break;
  case kLevelChangeScreen:
    RenderLevelChange();
    break;
  case kYouWon:
    RenderWonScreen();
    break;
  default: ;
  }

  DrawHudElements(delta_time);

  SDL_UpdateTexture(screen_texture_, NULL, pixels_table_->pixels_,
                    window_width_ * 4);
  SDL_RenderTexture(renderer_, screen_texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}

void YasEngine::RenderGameObjects() {
  for (auto object : objects_to_draw_) {
    if (object->is_alive_) {
      // TODO if gamestate == kGameplay

      DrawPolygon(object, *pixels_table_);
    }
  }
}

void YasEngine::RenderLevelChange() {
  switch (previous_level_) {
  case 1:

    writer_->Write(-1 * ((line_1.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[1], line_1, kLightBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_2.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[0], line_2, kBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_3.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[0], line_3, kGreen,
                   *pixels_table_);
    break;
  case 2:

    writer_->Write(-1 * ((line_4.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[1], line_4, kLightBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_5.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[0], line_5, kBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_6.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[0], line_6, kGreen,
                   *pixels_table_);
    break;
  case 3:

    writer_->Write(-1 * ((line_7.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[1], line_7, kLightBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_8.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[0], line_8, kBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_9.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[0], line_9, kGreen,
                   *pixels_table_);
    break;
  case 4:

    writer_->Write(-1 * ((line_10.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[1], line_10, kLightBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_11.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_top_positions_[0], line_11, kBlue,
                   *pixels_table_);
    writer_->Write(-1 * ((line_12.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[0], line_12, kGreen,
                   *pixels_table_);
    writer_->Write(-1 * ((line_13.size() * writer_->kfont_width_) / 2),
                   writer_->vertical_bottom_positions_[1], line_13, kYellow,
                   *pixels_table_);
    break;
  default: ;
  }
}

void YasEngine::RenderWonScreen() {
  //  8 wierszy

  writer_->Write(-1 * ((line_14.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_top_positions_[3], line_14, kLightBlue,
                 *pixels_table_);
  writer_->Write(-1 * ((line_15.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_top_positions_[2], line_15,
                 kYellow,
                 *pixels_table_);
  writer_->Write(-1 * ((line_16.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_top_positions_[1], line_16,
                 kPurple,
                 *pixels_table_);
  writer_->Write(-1 * ((line_17.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_top_positions_[0], line_17, kPurple,
                 *pixels_table_);
  writer_->Write(-1 * ((line_18.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_bottom_positions_[0], line_18,
                 kPurple, *pixels_table_);
  writer_->Write(-1 * ((line_19.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_bottom_positions_[1], line_19, kGreen,
                 *pixels_table_);
  writer_->Write(-1 * ((line_20.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_bottom_positions_[2], line_20,
                 kYellow, *pixels_table_);
  writer_->Write(-1 * ((line_21.size() * writer_->kfont_width_) / 2),
                 writer_->vertical_bottom_positions_[3], line_21,
                 kLightBlue,
                 *pixels_table_);
}

void YasEngine::HandlePhysics() {

} // END OF HandlePhysics()

void YasEngine::HandleDisassemblingGraphs(GameObject* game_object) {
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
    primes_points_harvested_ -= game_object->number_of_vertices_;
    break;

  case 2:

    fibonacci_points_harvested_ -= game_object->number_of_vertices_;
    break;

  case 3:

    sine_points_harvested_ -= game_object->number_of_vertices_;
    break;

  case 4:

    cosine_points_harvested_ -= game_object->number_of_vertices_;
    break;

  default: ;
  }
}

void YasEngine::HandleDestroingCollectibles(GameObject* game_object) {
  if (Spawner::number_of_spawned_objects_ > 0) {
    --Spawner::number_of_spawned_objects_;
  }
  else {
    Spawner::number_of_spawned_objects_ = 0;
  }
}

void YasEngine::HandlingAssemblingGraphs(GameObject* game_object) {
  int new_value_of_primes_points_harvested =
    primes_points_harvested_ + game_object->number_of_vertices_;
  int new_value_of_fibbs_points_harvested =
    fibonacci_points_harvested_ + game_object->number_of_vertices_;
  int new_sine_points_harvested =
    sine_points_harvested_ + game_object->number_of_vertices_;
  int new_cosine_points_harvested =
    cosine_points_harvested_ + game_object->number_of_vertices_;

  if (level_ == 1 && new_value_of_primes_points_harvested >=
    prime_numbers_picture_->base_points_fuel_) {
    primes_points_harvested_ = prime_numbers_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = 2;
    level_changed_ = true;
    return;
  }

  if (level_ == 2 && new_value_of_fibbs_points_harvested >=
    fibonaccie_picture_->base_points_fuel_) {
    fibonacci_points_harvested_ = fibonaccie_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = 3;
    level_changed_ = true;
    return;
  }

  int some = sine_points_harvested_;

  if (level_ == 3 &&
    new_sine_points_harvested >= sine_picture_->base_points_fuel_) {
    sine_points_harvested_ = sine_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = 4;
    level_changed_ = true;
    return;
  }

  if (level_ == 4 &&
    new_cosine_points_harvested >= cosine_picture_->base_points_fuel_) {
    cosine_points_harvested_ = cosine_picture_->base_points_fuel_;
    previous_level_ = level_;
    level_ = -1;
    level_changed_ = true;
    return;
  }

  switch (level_) {
  case 1:

    if (new_value_of_primes_points_harvested <=
      prime_numbers_picture_->base_points_fuel_) {
      primes_points_harvested_ = new_value_of_primes_points_harvested;
    }
    break;
  case 2:

    if (new_value_of_fibbs_points_harvested <=
      fibonaccie_picture_->base_points_fuel_) {
      fibonacci_points_harvested_ = new_value_of_fibbs_points_harvested;
    }

    break;
  case 3:

    if (new_sine_points_harvested <= sine_picture_->base_points_fuel_) {
      sine_points_harvested_ = new_sine_points_harvested;
    }

    break;
  case 4:

    if (new_cosine_points_harvested <= cosine_picture_->base_points_fuel_) {
      cosine_points_harvested_ = new_cosine_points_harvested;
    }

    break;
  default: ;
  }
}

bool YasEngine::IsObjectProtagonist(GameObject* game_object) {
  return game_object->i_am_ == GameObject::kProtagonist;
}

GameObject* YasEngine::GetProtagonist(GameObject* game_object_0,
                                      GameObject* game_object_1) {
  if (IsObjectProtagonist(game_object_0)) {
    return game_object_0;
  }
  if (IsObjectProtagonist(game_object_1)) {
    return game_object_1;
  }
  return nullptr;
}

GameObject* YasEngine::GetNotProtagonist(GameObject* game_object_0,
                                         GameObject* game_object_1) {
  if (!IsObjectProtagonist(game_object_0)) {
    return game_object_0;
  }
  if (!IsObjectProtagonist(game_object_1)) {
    return game_object_1;
  }
  return nullptr;
}

void YasEngine::BounceCollectibles(GameObject* game_object, Wall wall) {
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
  default: ;
    break;
  }

  float dot_product = Vector2D<float>::DotProduct(game_object->velocity_, normal);
  Vector2D<float>::MultiplyByScalar(&normal, dot_product * 2.0f);
  Vector2D<float>::Substract(&game_object->velocity_, normal);

  // TO PREVENT COLLECTIBLE STUCK IN THE WALL
  // objects_to_draw_[i]->set_x(rightWall - objects_to_draw_[i]->collider.radius_
  // - 1);
}

void YasEngine::MoveObjects() {
  for (auto object : objects_to_draw_) {
    if (object->is_alive_) {
      object->Move(static_cast<float>(delta_time_));
      object->RegeneratePolygon();
    }
  }
}

void YasEngine::PrepareSoundAndMusic() {
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

void YasEngine::pushUniqueTriangle(std::vector<Triangle3D*>& triangles,
                                   Triangle3D* triangle) {
  bool unique = true;
  for (Triangle3D* tri : triangles) {
    if (tri->first_vertex->x_ == triangle->first_vertex->x_ &&
        tri->first_vertex->y_ == triangle->first_vertex->y_ &&
        tri->first_vertex->z_ == triangle->first_vertex->z_ &&
        tri->second_vertex->x_ == triangle->second_vertex->x_ &&
        tri->second_vertex->y_ == triangle->second_vertex->y_ &&
        tri->second_vertex->z_ == triangle->second_vertex->z_&&
        tri->third_vertex->x_ == triangle->third_vertex->x_ &&
        tri->third_vertex->y_ == triangle->third_vertex->y_ &&
        tri->third_vertex->z_ == triangle->third_vertex->z_
      
      
      ) {
      unique = false;
      break;
        }
  }
  if (unique) {
    triangles.push_back(triangle);
  }
}

void YasEngine::PrepareGameWorld() {
  srand(clock());

  number_of_given_colors_.insert({"kRed", 0});
  number_of_given_colors_.insert({"GREEN", 0});
  number_of_given_colors_.insert({"kBlue", 0});
  number_of_given_colors_.insert({"YELLOW", 0});
  // PrepareDataForDrawingGraphs();

  // BOX in 3D

  box_position_.x_ = 0;
  box_position_.y_ = 0;
  box_position_.z_ = -200;
  //
  local_box_.push_back(new Vector4D<float>(-50, 50, 50, 0));    // przod od ekranu
  local_box_.push_back(new Vector4D<float>(50, 50, 50,0));     // przod od ekranu
  local_box_.push_back(new Vector4D<float>(50, -50, 50, 0));    // przod od ekranu
  local_box_.push_back(new Vector4D<float>(-50, -50, 50, 0));   // przod od ekranu

  local_box_.push_back(new Vector4D<float>(-50, 50, -50,0));   // przod od ekranu
  local_box_.push_back(new Vector4D<float>(50, 50, -50,0));    // przod od ekranu
  local_box_.push_back(new Vector4D<float>(50, -50, -50,0));   // przod od ekranu
  local_box_.push_back(new Vector4D<float>(-50, -50, -50,0));  // przod od ekranu

  trojkaty = new Vector4D<float>[36];
  trojkatySwiat = new Vector4D<float>[36];

  trojkaty[0] = local_box_.at(0);
  trojkaty[1] = local_box_.at(1);
  trojkaty[2] = local_box_.at(2);

  trojkaty[3] = local_box_.at(0);
  trojkaty[4] = local_box_.at(2);
  trojkaty[5] = local_box_.at(3);

  trojkaty[6] = local_box_.at(5);
  trojkaty[7] = local_box_.at(4);
  trojkaty[8] = local_box_.at(7);

  trojkaty[9] = local_box_.at(5);
  trojkaty[10] = local_box_.at(7);
  trojkaty[11] = local_box_.at(6);

  trojkaty[12] = local_box_.at(4);
  trojkaty[13] = local_box_.at(5);
  trojkaty[14] = local_box_.at(1);

  trojkaty[15] = local_box_.at(4);
  trojkaty[16] = local_box_.at(1);
  trojkaty[17] = local_box_.at(0);

  trojkaty[18] = local_box_.at(3);
  trojkaty[19] = local_box_.at(2);
  trojkaty[20] = local_box_.at(6);

  trojkaty[21] = local_box_.at(3);
  trojkaty[22] = local_box_.at(6);
  trojkaty[23] = local_box_.at(7);

  trojkaty[24] = local_box_.at(4);
  trojkaty[25] = local_box_.at(0);
  trojkaty[26] = local_box_.at(3);

  trojkaty[27] = local_box_.at(4);
  trojkaty[28] = local_box_.at(3);
  trojkaty[29] = local_box_.at(7);

  trojkaty[30] = local_box_.at(1);
  trojkaty[31] = local_box_.at(5);
  trojkaty[32] = local_box_.at(6);

  trojkaty[33] = local_box_.at(1);
  trojkaty[34] = local_box_.at(6);
  trojkaty[35] = local_box_.at(2);

  

  for (int i = 0; i < 36; i++) {
    trojkatySwiat[i] =
        new Vector4D<float>(trojkaty[i].x_, trojkaty[i].y_, trojkaty[i].z_, 0);
  }

  // bool end = false;
  // std::vector<Triangle3D*> triangles;
  // Triangle3D* tri;
  // while (!end) {
    // for (int i = 0; i < 8; i++) {
    //   float x = local_box_.at(i)->x_;
    //   std::vector<Vector4D<float>*> square_planes_x;
    //   for (int j = 0; j < 8; j++) {
    //     if (local_box_.at(j)->x_ == x) {
    //       square_planes_x.push_back(
    //           new Vector4D<float>(local_box_.at(j)->x_, local_box_.at(j)->y_,
    //                               local_box_.at(j)->z_, local_box_.at(j)->w_));
    //     }
    //   }
    //   tri = new Triangle3D();
    //   tri->first_vertex = new Vector4D<float>(square_planes_x.at(0));
    //   tri->second_vertex = new Vector4D<float>(square_planes_x.at(1));
    //   tri->third_vertex = new Vector4D<float>(square_planes_x.at(2));
    //   pushUniqueTriangle(triangles, tri);
    //   tri = new Triangle3D();
    //   tri->first_vertex = new Vector4D<float>(square_planes_x.at(2));
    //   tri->second_vertex = new Vector4D<float>(square_planes_x.at(3));
    //   tri->third_vertex = new Vector4D<float>(square_planes_x.at(0));
    //   pushUniqueTriangle(triangles, tri);
    //   // triangles.push_back(tri);
    //   tri = nullptr;
    //   ///////////////////////square_planes_x.clear();
    //
    //   float y = local_box_.at(i)->y_;
    //   std::vector<Vector4D<float>*> square_planes_y;
    //   for (int j = 0; j < 8; j++) {
    //     if (local_box_.at(j)->y_ == y) {
    //       square_planes_y.push_back(
    //           new Vector4D<float>(local_box_.at(j)->x_, local_box_.at(j)->y_,
    //                               local_box_.at(j)->z_, local_box_.at(j)->w_));
    //     }
    //   }
    //   tri = new Triangle3D();
    //   tri->first_vertex = new Vector4D<float>(square_planes_y.at(0));
    //   tri->second_vertex = new Vector4D<float>(square_planes_y.at(1));
    //   tri->third_vertex = new Vector4D<float>(square_planes_y.at(2));
    //   pushUniqueTriangle(triangles, tri);
    //   tri = new Triangle3D();
    //   tri->first_vertex = new Vector4D<float>(square_planes_y.at(2));
    //   tri->second_vertex = new Vector4D<float>(square_planes_y.at(3));
    //   tri->third_vertex = new Vector4D<float>(square_planes_y.at(0));
    //   pushUniqueTriangle(triangles, tri);
    //   // triangles.push_back(tri);
    //   tri = nullptr;
    //   ///////////////////////square_planes_y.clear();
    //
    //   float z = local_box_.at(i)->z_;
    //   std::vector<Vector4D<float>*> square_planes_z;
    //   for (int j = 0; j < 8; j++) {
    //     if (local_box_.at(j)->z_ == z) {
    //       square_planes_z.push_back(
    //           new Vector4D<float>(local_box_.at(j)->x_, local_box_.at(j)->y_,
    //                               local_box_.at(j)->z_, local_box_.at(j)->w_));
    //     }
    //   }
    //   tri = new Triangle3D();
    //   tri->first_vertex = new Vector4D<float>(square_planes_z.at(0));
    //   tri->second_vertex = new Vector4D<float>(square_planes_z.at(1));
    //   tri->third_vertex = new Vector4D<float>(square_planes_z.at(2));
    //   pushUniqueTriangle(triangles, tri);
    //   tri = new Triangle3D();
    //   tri->first_vertex = new Vector4D<float>(square_planes_z.at(2));
    //   tri->second_vertex = new Vector4D<float>(square_planes_z.at(3));
    //   tri->third_vertex = new Vector4D<float>(square_planes_z.at(0));
    //   pushUniqueTriangle(triangles, tri);
    //   // triangles.push_back(tri);
    //   tri = nullptr;
    //   ///////////////////////square_planes_z.clear();
    // }
    // if (triangles.size() >= 12) {
    //   end = true;
    // }
  // }
 //
 // for (int i = 0; i < triangles.size(); i++) {
 //      box_triangles_local.push_back(triangles.at(i));
 // }
 //
 //  for (int i = 0; i < triangles.size(); i++) {
 //   box_triangles_world.push_back(new Triangle3D(box_triangles_local.at(i)));
 // }

  // for (int i = 0; i < local_box_.size(); i++) {
  //   world_box_.push_back(
  //       new Vector4D(local_box_.at(i)->x_, local_box_.at(i)->y_,
  //                    local_box_.at(i)->z_, local_box_.at(i)->w_));
  // }
  
  //   for (int i = 0; i < local_box_.size(); i++) {
  //   // world_box_.at(i)->= local_box_->+ box_position_;
  //   world_box_.at(i)->x_ = local_box_.at(i)->x_ + box_position_.x_;
  //   world_box_.at(i)->y_ = local_box_.at(i)->y_ + box_position_.y_;
  //   world_box_.at(i)->z_ = local_box_.at(i)->z_ + box_position_.z_;
  //   world_box_.at(i)->w_ = local_box_.at(i)->w_ + box_position_.w_;
  // }

  // box_2d_ = new Vector2D<float>[world_box_.size()];
  //
  // for (int i = 0; i < box_triangles_local.size(); i++) {
  //   triangles_2d_.push_back(new Triangle2D);
  // }
  //
  // for (int i = 0; i < 36; i++) {
  //
  // }

  // testLines = new Vector2D<float>[8];
  // testLines[0].x_= 5;
  // testLines[0].y_= 5;
  // testLines[1].x_= 30;
  // testLines[1].y_= -80;
  // testLines[2].x_= 200;
  // testLines[2].y_= 220;
  // testLines[3].x_= 150;
  // testLines[3].y_= -90;
  // testLines[4].x_= 100;
  // testLines[4].y_= -130;
  // testLines[5].x_= 200;
  // testLines[5].y_= -50;
  // testLines[6].x_= 300;
  // testLines[6].y_= -25;
  // testLines[7].x_= 0;
  // testLines[7].y_= 0;


}

void YasEngine::PrepareDataForDrawingGraphs() {
  PreparePrimesDrawing();
  PrepareFibonacciDrawing();
  PrepareSineDrawing();
  PrepareCosineDrawing();
}

void YasEngine::PrepareSineDrawing() {
  std::map<float, float>* sines =
    GenerateSineNumbers(40); // GeneratePrimeNumbersLessThanN(1000);
  sine_points_harvested_ = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>>
  // pair_numbers_map_;

  std::map<int, std::map<float, float>> numbek_red_sines;

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

void YasEngine::PrepareCosineDrawing() {
  std::map<float, float>* cosines =
    GenerateCosineNumbers(40); // GeneratePrimeNumbersLessThanN(1000);
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

void YasEngine::PrepareFibonacciDrawing() {
  std::vector<int> fibbs = GenerateNfibonacciNumbers(40);
  fibonacci_points_harvested_ = 0;

  numbers_map_.insert(std::pair<std::string, std::map<int, float>*>(
    "Fibbs", new std::map<int, float>));

  for (int i = 0; i < fibbs.size(); i++) {
    numbers_map_.at("Fibbs")->insert(std::pair<int, int>(i, fibbs.at(i)));
  }

  fibonaccie_picture_ =
    new MathPicture(numbers_map_.at("Fibbs"), new FibonacciPointsGenerator());
}

void YasEngine::PreparePrimesDrawing() {
  std::vector<int> primes = GeneratePrimeNumbersLessThanN(1000);
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

void YasEngine::PrepareInterface() {
  // Button 1
  buttons_.push_back(new Button(Button::kRestartStart, "START", kRed, writer_));
  buttons_.at(0)->set_position(0, 50);
  dynamic_cast<Button*>(buttons_.at(0))->horizontal_margin_ = 10;
  dynamic_cast<Button*>(buttons_.at(0))->vertical_margin_ = 5;
  dynamic_cast<Button*>(buttons_.at(0))->button_width_ =
    writer_->kfont_width_ *
    static_cast<int>(
      dynamic_cast<Button*>(buttons_.at(0))->text_.size()) +
    2 * dynamic_cast<Button*>(buttons_.at(0))->horizontal_margin_;
  dynamic_cast<Button*>(buttons_.at(0))->button_height_ =
    writer_->kfont_height_ +
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
  buttons_.push_back(new Button(Button::kQuit, "QUIT", kYellow, writer_));
  buttons_.at(1)->set_position(0, -50);
  dynamic_cast<Button*>(buttons_.at(1))->horizontal_margin_ = 10;
  dynamic_cast<Button*>(buttons_.at(1))->vertical_margin_ = 5;
  dynamic_cast<Button*>(buttons_.at(1))->button_width_ =
    writer_->kfont_width_ *
    static_cast<int>(
      dynamic_cast<Button*>(buttons_.at(1))->text_.size()) +
    2 * dynamic_cast<Button*>(buttons_.at(1))->horizontal_margin_;
  dynamic_cast<Button*>(buttons_.at(1))->button_height_ =
    writer_->kfont_height_ +
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

}

void YasEngine::DrawButtons() {
  for (unsigned int i = 0; i < buttons_.size(); i++) {
    DrawPolygon(buttons_.at(i), *pixels_table_);
    writer_->Write(
      static_cast<int>(
        buttons_.at(i)->get_position().x_ -
        dynamic_cast<Button*>(buttons_.at(i))->button_text_width_ * 0.5F +
        writer_->kfont_width_ * 0.5F),
      static_cast<int>(buttons_.at(i)->get_position().y_),
      dynamic_cast<Button*>(buttons_.at(i))->text_,
      dynamic_cast<Button*>(buttons_.at(i))->color_, *pixels_table_);
  }
}

void YasEngine::BoxProcessing() {
  // std::vector<Vector4D<float>*> local_box_;
  // std::vector<Vector4D<float>*> world_box_;
  // std::vector<Vector2D<float>*> box_2d_;
  // model to world
  // for (int i = 0; i < local_box_.size(); i++) {
  //   // world_box_.at(i)->= local_box_->+ box_position_;
  //   world_box_.at(i)->x_ = local_box_.at(i)->x_ + box_position_.x_;
  //   world_box_.at(i)->y_ = local_box_.at(i)->y_ + box_position_.y_;
  //   world_box_.at(i)->z_ = local_box_.at(i)->z_ + box_position_.z_;
  //   world_box_.at(i)->w_ = local_box_.at(i)->w_ + box_position_.w_;
  // }

  // for (int i = 0; i < world_box_.size(); i++) {
  //   box_2d_[i].x_ = 0 + ((world_box_.at(i)->x_ * kdistanceFromProjectionPlane) /
  //                        world_box_.at(i)->z_);
  //   box_2d_[i].y_ = 0 - ((world_box_.at(i)->y_ * kdistanceFromProjectionPlane) /
  //                        world_box_.at(i)->z_);
  // }

  if (input_->up && !input_->down) {
    box_position_.z_ = box_position_.z_ + delta_time_ * box_speed_;
  }

  // DOWN
  if (input_->down && !input_->up) {
    box_position_.z_ = box_position_.z_ + delta_time_ * (-box_speed_);
  }

  // for (int i = 0; i < box_triangles_local.size(); i++) {
  //   box_triangles_world.at(i)->first_vertex->x_ =
  //       box_triangles_local.at(i)->first_vertex->x_ + box_position_.x_;
  //   box_triangles_world.at(i)->first_vertex->y_ =
  //       box_triangles_local.at(i)->first_vertex->y_ + box_position_.y_;
  //   box_triangles_world.at(i)->first_vertex->z_ =
  //       box_triangles_local.at(i)->first_vertex->z_ + box_position_.z_;
  //
  //   box_triangles_world.at(i)->second_vertex->x_ =
  //       box_triangles_local.at(i)->second_vertex->x_ + box_position_.x_;
  //   box_triangles_world.at(i)->second_vertex->y_ =
  //       box_triangles_local.at(i)->second_vertex->y_ + box_position_.y_;
  //   box_triangles_world.at(i)->second_vertex->z_ =
  //       box_triangles_local.at(i)->second_vertex->z_ + box_position_.z_;
  //
  //   box_triangles_world.at(i)->third_vertex->x_ =
  //       box_triangles_local.at(i)->third_vertex->x_ + box_position_.x_;
  //   box_triangles_world.at(i)->third_vertex->y_ =
  //       box_triangles_local.at(i)->third_vertex->y_ + box_position_.y_;
  //   box_triangles_world.at(i)->third_vertex->z_ =
  //       box_triangles_local.at(i)->third_vertex->z_ + box_position_.z_;
  // }

  for (int i = 0; i < 36; i++) {
    trojkatySwiat[i].x_ = trojkaty[i].x_ + box_position_.x_;
    trojkatySwiat[i].y_ = trojkaty[i].y_ + box_position_.y_;
    trojkatySwiat[i].z_ = trojkaty[i].z_ + box_position_.z_;
  }


  // for (int i = 0; i < triangles_2d_.size(); i++) {
  //   triangles_2d_.at(i)->first_vertex->x_ = 0 +
  //       ((box_triangles_world.at(i)->first_vertex->x_ *
  //         kdistanceFromProjectionPlane) / box_triangles_world.at(i)->first_vertex->z_);
  //       triangles_2d_.at(i)->first_vertex->y_ = 0 -
  //       ((box_triangles_world.at(i)->first_vertex->y_ *
  //         kdistanceFromProjectionPlane) / box_triangles_world.at(i)->first_vertex->z_);
  //
  //       triangles_2d_.at(i)->second_vertex->x_ = 0 +
  //           ((box_triangles_world.at(i)->second_vertex->x_ *
  //         kdistanceFromProjectionPlane) / box_triangles_world.at(i)->second_vertex->z_);
  //       triangles_2d_.at(i)->second_vertex->y_ = 0 -
  //           ((box_triangles_world.at(i)->second_vertex->y_ *
  //         kdistanceFromProjectionPlane) / box_triangles_world.at(i)->second_vertex->z_);
  //
  //       triangles_2d_.at(i)->third_vertex->x_ = 0 +
  //           ((box_triangles_world.at(i)->third_vertex->x_ *
  //         kdistanceFromProjectionPlane) / box_triangles_world.at(i)->third_vertex->z_);
  //       triangles_2d_.at(i)->third_vertex->y_ = 0 -
  //           ((box_triangles_world.at(i)->third_vertex->y_ *
  //         kdistanceFromProjectionPlane) / box_triangles_world.at(i)->third_vertex->z_);
  // }

    // for (int i = 0; i < world_box_.size(); i++) {
    // box_2d_[i].x_ = 0 + ((world_box_.at(i)->x_ * kdistanceFromProjectionPlane) /
    //                      world_box_.at(i)->z_);
    // box_2d_[i].y_ = 0 - ((world_box_.at(i)->y_ * kdistanceFromProjectionPlane) /
    //                      world_box_.at(i)->z_);
    // }

    for (int i = 0; i < 36; i++) {
      szescian2d[i].x_ =
          0 + ((trojkatySwiat[i].x_ * kdistanceFromProjectionPlane) /
               trojkatySwiat[i].z_);
      szescian2d[i].y_ =
          0 - ((trojkatySwiat[i].y_ * kdistanceFromProjectionPlane) /
               trojkatySwiat[i].z_);
    }

}

// Vector2D<float>* vertices,
// int maximum_number_of_vertices,
// const Vector4D<Uint8>& color,
// bool are_lines_continuous,
// PixelsTable& pixels_table) {

void YasEngine::DrawBox() {
    for (int i = 0; i < 33; i +=3 ) {
      DrawLine(szescian2d[i+0], szescian2d[i+1], *pixels_table_, kYellow);
      DrawLine(szescian2d[i + 1], szescian2d[i + 2], *pixels_table_, kYellow);
      DrawLine(szescian2d[i + 2], szescian2d[i + 0], *pixels_table_, kYellow);
  }
}

Button::ButtonId YasEngine::CheckWhichButtonClicked() {
  float x = static_cast<float>(mouse_position_change_information_->x);
  float y = static_cast<float>(mouse_position_change_information_->y);
  WindowPositionToCartesianPosition(x, y, window_dimensions_);
  for (unsigned int i = 0; i < buttons_.size(); i++) {
    if (
      // mouse cursor under top Y
      y <= (buttons_.at(i)->get_position().y_ +
        dynamic_cast<Button*>(buttons_.at(i))->button_height_ * 0.5F) &&
      // mouser cursor above bottom Y
      y >= (buttons_.at(i)->get_position().y_ -
        dynamic_cast<Button*>(buttons_.at(i))->button_height_ * 0.5F) &&
      // cursor to the right of left X
      x >= (buttons_.at(i)->get_position().x_ -
        dynamic_cast<Button*>(buttons_.at(i))->button_width_ * 0.5F) &&
      // cursor to the left of X
      x <= (buttons_.at(i)->get_position().x_ +
        dynamic_cast<Button*>(buttons_.at(i))->button_width_ * 0.5F)) {
      return dynamic_cast<Button*>(buttons_.at(i))->button_id_;
    }
  }
  return Button::kNone;
}

void YasEngine::HandleClickedButtons() {
  switch (CheckWhichButtonClicked()) {
  case Button::kRestartStart:
    game_state_ = GameState::kGameplay;
    break;
  case Button::kQuit:
    game_state_ = GameState::kOutro;
    break;
  default: ;
  }
}

void YasEngine::HandleGameStateWhenESCbuttonPushed() {
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
  default: ;
  }
}

void YasEngine::HandleGameStateWhenSPACEbuttonPushed() {
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
  default: ;
  }
}
