#include "yas_engine.hpp"

#include <SDL_mixer.h>

#include <bit>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "time_picker.hpp"
#include "game_object.hpp"
#include "yas_graphics_library.hpp"

YasEngine* YasEngine::instance_ = nullptr;

void YasEngine::initialize() {
  engine_version_ = "YasEngine 1 | Beauty of Math 1 version: " +
    std::to_string(major_revision_) + "." +
    std::to_string(minor_revision_) + "." +
    std::to_string(bug_fix_release_) + "." +
    std::to_string(build_number_);
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

  settings_.Parse(settings_string.c_str());

  if (settings_.HasParseError()) {
    std::cerr << "Error parsing JSON" << std::endl;
    exit(1);
  }

  const rapidjson::Value& sound_settings = settings_["SOUND_MUSIC"];

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

  window_width_ = 640;  // static_cast<int>(display_mode->w * 0.75);
  window_height_ = 480;  // static_cast<int>(display_mode->h * 0.75);

  window_dimensions_ = new Dimensions2D(window_width_, window_height_);
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
      break;
    case SDLK_TAB:
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
  int x = 0;  // Randomizer::DrawNumberClosedInterval(0, size_Of_gameplay_space)
              // - 64;
  int y = 0;  // Randomizer::DrawNumberClosedInterval(0, size_Of_gameplay_space)
              // - 64;

  player_ = new Player(x, y);
  player_->set_color(kYellow);
  player_->set_input(input_);
  player_->set_input(mouse_position_change_information_);
  objects_to_draw_.push_back(player_);
}

void YasEngine::Update(double& delta_time) {
  if (level_changed_) {
    for (int i = 0; i < objects_to_draw_.size(); i++) {
      if (objects_to_draw_[i]->i_am_ != GameObject::kPlayer) {
        objects_to_draw_[i]->is_alive_ = false;
      }
    }
  }

  DeleteNotAliveObjects();

  switch (game_state_) {
  case kGameplay:
    HandlePhysics();
    MoveObjects();
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
      DrawPolygon(object, *pixels_table_);
    }
  }
}

void YasEngine::HandlePhysics() {
  if (player_->i_am_ == GameObject::kPlayer) {
  
    if (player_->GetColliderLeftSide() < (-window_width_ / 2)) {
      player_->set_position(
          (-window_width_ / 2) + (player_->collider_.radius_),
          player_->get_position().y_);
    }

    if (player_->GetColliderRightSide() > (window_width_ / 2)) {
      player_->set_position(
          (window_width_ / 2) - (player_->collider_.radius_),
          player_->get_position().y_);
    }

    if (player_->GetColliderTopSide() > (window_height_ / 2)) {
      player_->set_position(
          player_->get_position().x_,
          (window_height_ / 2) - (player_->collider_.radius_));
    }

    if (player_->GetColliderBottomSide() < (-window_height_ / 2)) {
      player_->set_position(
          player_->get_position().x_,
          (-window_height_ / 2) + (player_->collider_.radius_));
    }
  }
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

void YasEngine::PrepareGameWorld() {
  srand(clock());

  number_of_given_colors_.insert({"kRed", 0});
  number_of_given_colors_.insert({"GREEN", 0});
  number_of_given_colors_.insert({"kBlue", 0});
  number_of_given_colors_.insert({"YELLOW", 0});

  box_position_.x_ = 0;
  box_position_.y_ = 0;
  box_position_.z_ = -200;

  local_box_.push_back(new Vector4D(-50, 50,  50,0));  // top plane / wall
  local_box_.push_back(new Vector4D( 50, 50,  50,0));  // top plane / wall
  local_box_.push_back(new Vector4D( 50, 50, -50,0));  // top plane / wall
  local_box_.push_back(new Vector4D(-50, 50, -50,0));  // top plane / wall

  local_box_.push_back(new Vector4D(-50, -50,  50,0)); // bottom plane / wall
  local_box_.push_back(new Vector4D( 50, -50,  50,0)); // bottom plane / wall
  local_box_.push_back(new Vector4D( 50, -50, -50,0)); // bottom plane / wall
  local_box_.push_back(new Vector4D(-50, -50, -50,0)); // bottom plane / wall

  trojkaty = new Vector4D[36];
  trojkatySwiat = new Vector4D[36];

  trojkaty[0] = local_box_.at(3);
  trojkaty[1] = local_box_.at(0);
  trojkaty[2] = local_box_.at(1);

  trojkaty[3] = local_box_.at(1);
  trojkaty[4] = local_box_.at(2);
  trojkaty[5] = local_box_.at(3);

  trojkaty[6] = local_box_.at(4);
  trojkaty[7] = local_box_.at(5);
  trojkaty[8] = local_box_.at(1);

  trojkaty[9] = local_box_.at(1);
  trojkaty[10] = local_box_.at(0);
  trojkaty[11] = local_box_.at(4);

  trojkaty[12] = local_box_.at(1);
  trojkaty[13] = local_box_.at(5);
  trojkaty[14] = local_box_.at(6);

  trojkaty[15] = local_box_.at(6);
  trojkaty[16] = local_box_.at(2);
  trojkaty[17] = local_box_.at(1);

  trojkaty[18] = local_box_.at(3);
  trojkaty[19] = local_box_.at(7);
  trojkaty[20] = local_box_.at(4);

  trojkaty[21] = local_box_.at(4);
  trojkaty[22] = local_box_.at(0);
  trojkaty[23] = local_box_.at(3);

  trojkaty[24] = local_box_.at(4);
  trojkaty[25] = local_box_.at(7);
  trojkaty[26] = local_box_.at(6);

  trojkaty[27] = local_box_.at(6);
  trojkaty[28] = local_box_.at(5);
  trojkaty[29] = local_box_.at(4);

  trojkaty[30] = local_box_.at(6);
  trojkaty[31] = local_box_.at(7);
  trojkaty[32] = local_box_.at(3);

  trojkaty[33] = local_box_.at(3);
  trojkaty[34] = local_box_.at(2);
  trojkaty[35] = local_box_.at(6);

  for (int i = 0; i < 36; i++) {
    trojkatySwiat[i] =
        new Vector4D(trojkaty[i].x_, trojkaty[i].y_, trojkaty[i].z_, 0);
  }
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
  buttons_.at(0)->local_vertices_ = new Vector2D[4];
  buttons_.at(0)->world_vertices_ = new Vector2D[4];
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
  buttons_.at(1)->local_vertices_ = new Vector2D[4];
  buttons_.at(1)->world_vertices_ = new Vector2D[4];
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

  if (input_->up && !input_->down) {
    box_position_.z_ = box_position_.z_ + delta_time_ * box_speed_;
  }

  if (input_->down && !input_->up) {
    box_position_.z_ = box_position_.z_ + delta_time_ * (-box_speed_);
  }

  for (int i = 0; i < 36; i++) {
    trojkatySwiat[i].x_ = trojkaty[i].x_ + box_position_.x_;
    trojkatySwiat[i].y_ = trojkaty[i].y_ + box_position_.y_;
    trojkatySwiat[i].z_ = trojkaty[i].z_ + box_position_.z_;
  }

    for (int i = 0; i < 36; i++) {
      szescian2d[i].x_ =
          0 + ((trojkatySwiat[i].x_ * kdistanceFromProjectionPlane) /
               trojkatySwiat[i].z_);
      szescian2d[i].y_ =
          0 - ((trojkatySwiat[i].y_ * kdistanceFromProjectionPlane) /
               trojkatySwiat[i].z_);
    }

}

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
