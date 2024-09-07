#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include <SDL_mixer.h>
#include <document.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "button.hpp"
#include "game_object.hpp"
#include "input_output_handler.hpp"
#include "pixels_table.hpp"
#include "player.hpp"
#include "screen_writer.hpp"
#include "triangle_2d.hpp"
#include "triangle_3d.hpp"
#include "vector_2d.hpp"
#include "dimensions_2d.hpp"

class YasEngine {
 public:
  bool tests_ = false;
  std::string engine_version_;
  int major_revision_ = 1;
  int minor_revision_ = 3;
  int bug_fix_release_ = 0;
  int build_number_ = 0;

  rapidjson::Document settings_;
  int music_volume_ = MIX_MAX_VOLUME;
  int shoot_volume_ = MIX_MAX_VOLUME;
  int hit_volume_ = MIX_MAX_VOLUME;
  int other_volume_ = MIX_MAX_VOLUME;

  bool collided_ = false;
  GameObject* game_object_;

  enum GameState {
    kIntro,
    kMainMenuRestart,
    kGameplay,
    kOutro,
    kPause,
    kLevelChangeScreen,
    kYouWon
  };

  bool player_won_and_exited_ = false;

  enum Wall { kLeft, kRight, kTop, kBottom };

  std::vector<Vector2D*> test_positions_;

  GameState game_state_ = GameState::kIntro;

  std::vector<GameObject*> buttons_;

  int base_points_number_ = 64;

  std::vector<std::string> main_menu_texts_;
  std::vector<std::string> intro_texts_;
  std::vector<std::string> outro_texts_;
  std::vector<std::string> in_game_texts_;

  static YasEngine* GetInstance() {
    if (instance_ != nullptr) {
      return instance_;
    }
    instance_ = new YasEngine();
    return instance_;
  }

  void initialize();
  void YasEngineStart();
  void clean();

 private:

  Vector2D A = Vector2D(-300, 200);
  Vector2D B = Vector2D(100, -350);

  static YasEngine* instance_;

  int endianness_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_Texture* screen_texture_;

  PixelsTable* pixels_table_;
  Dimensions2D* window_dimensions_;
  SDL_Event event_;
  bool quit_ = false;

  double time_;
  double new_time_;
  double delta_time_;
  double fps_;
  double fps_time_;
  unsigned int frames_;

  float mouse_x_;
  float mouse_y_;

  int window_width_ = 0;
  int window_height_ = 0;

  std::vector<GameObject*> objects_to_draw_;
  bool first_16_spawned_ = false;
  int how_many_ = 0;
  Player* player_;
  
  const int kmax_collectibles_to_spawn_ = 64;

  std::map<std::string, std::map<int, float>*> numbers_map_;
  std::map<std::string, std::map<int, std::map<float, float>*>*>
      pair_numbers_map_;

  SDL_AudioSpec audio_specs_;

  Mix_Music* music_;
  Mix_Chunk* shoot_sound_;
  Mix_Chunk* hit_sound_;
  Mix_Chunk* other_sound_;

  int level_ = 1;
  int previous_level_ = 0;
  bool level_changed_ = false;
  const int kmax_level_ = 4;
  int sine_points_harvested_ = 0;
  int cosine_points_harvested_ = 0;
  int primes_points_harvested_ = 0;
  int fibonacci_points_harvested_ = 0;

  int max_n_to_calculate_primes_ = 1000;
  int max_n_to_calculate_fibonacci_ = 40;
  int max_n_to_calculate_sine_ = 100;
  int max_n_to_calculate_cosine_ = 100;

  std::map<std::string, int> number_of_given_colors_;

  Vector2D test_point_0_;
  Vector2D test_point_1_;

  ScreenWriter* writer_;
  int step_ = 0;

  YasEngine() {};
  bool should_application_stop_running_ = false;
  YasInOut::Input* input_ = new YasInOut::Input();
  YasInOut::MousePositionChangeInformation* mouse_position_change_information_ =
      new YasInOut::MousePositionChangeInformation();
  int red_shot_downs_ = 0;
  int green_shotdowns_ = 0;
  int blue_shotdowns_ = 0;
  bool is_engine_instantiated_ = false;

  std::string line_22 = "BEAUTY.OF.MATH";
  std::string line_23 = "POWERED.BY";
  std::string line_24 = "YAS.ENGINE";

  std::string line_25 = "GAME.DESIGN.PROGRAMMING.AND.MARKETING";
  std::string line_26 = "LUKASZ.SAWICKI";

  std::vector<Vector4D*> local_box_;
  std::vector<Vector4D*> world_box_;
  std::vector<Triangle3D*> box_triangles_world;
  std::vector<Triangle3D*> box_triangles_local;
  Vector4D* trojkaty;
  Vector4D* trojkatySwiat;
  std::vector<Vector4D*> czworoscian;

  Vector2D* box_2d_;
  Vector2D* szescian2d = new Vector2D[36];


  std::vector<Triangle2D*> triangles_2d_;
  
  float box_speed_ = 30;

  //
  Vector2D* testLines;
  //
  const int kdistanceFromProjectionPlane = -50;
  //
  Vector4D box_position_;

  void ReadSettingsFromFile();
  void PrepareRendering();
  void PrepareBasicSettings();
  void CheckEndianness();
  void HandlePhysics();
  void MoveObjects();
  void PrepareGameWorld();
  void PreparePlayer();
  void PrepareInterface();
  void HandleInput(SDL_Event& event);
  void HandleKeyboardInput(SDL_Event& event);
  void HandleMouseInput(SDL_Event& event);
  void HandleMouseMovement();
  void DeleteNotAliveObjects();
  void HandlePlayer();
  void Update(double& delta_time);
  void ResetAll();
  void DrawHudElements(double& delta_time);
  void Render(double& delta_time);
  void RenderGameObjects();
  Button::ButtonId CheckWhichButtonClicked();
  void HandleClickedButtons();
  void HandleGameStateWhenESCbuttonPushed();
  void HandleGameStateWhenSPACEbuttonPushed();
  void PrepareSoundAndMusic();
  void DrawButtons();
  void BoxProcessing();
  void DrawBox();
};

#endif
