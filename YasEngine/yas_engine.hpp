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
#include "map_frame.hpp"
#include "math_picture.hpp"
#include "mathematics_graphs_surface.hpp"
#include "node.hpp"
#include "pixels_table.hpp"
#include "player.hpp"
#include "screen_writer.hpp"
#include "vector_2d.hpp"

class YasEngine {
 public:
  bool tests_ = false;
  std::string engine_version_;
  int MAJOR_REVISION = 1;
  int MINOR_REVISION = 3;
  int BUG_FIX_RELEASE = 0;
  int BUILD_NUMBER = 0;

  rapidjson::Document settings;
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

  struct NodeNumbersOnTwoProceedingLevels {
    int first_level_node = 0;
    int second_level_node = 0;

    NodeNumbersOnTwoProceedingLevels() {
      first_level_node = 0;
      second_level_node = 0;
    }

    NodeNumbersOnTwoProceedingLevels(int first, int second) {
      this->first_level_node = first;
      this->second_level_node = second;
    }
  };

  std::vector<Vector2D<int>*> test_positions_;

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
  TimePicker time_picker_;

  Vector2D<float> A = Vector2D<float>(-300, 200);
  Vector2D<float> B = Vector2D<float>(100, -350);

  static YasEngine* instance_;

  int endianness_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_Texture* screen_texture_;

  PixelsTable* pixels_table_;
  Vector2D<int>* window_dimensions_;
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

  int window_width_ = 1600;
  int window_height_ = 800;

  std::vector<GameObject*> objects_to_draw_;
  bool first_16_spawned_ = false;
  int how_many_ = 0;
  Player* player_;
  MathematicsGraphsSurface* mathematics_graphs_surface_;
  std::vector<NodeNumbersOnTwoProceedingLevels*> spawners_positions_;

  const int kmax_collectibles_to_spawn_ = 64;

  std::map<std::string, std::map<int, float>*> numbers_map_;
  std::map<std::string, std::map<int, std::map<float, float>*>*>
      pair_numbers_map_;

  SDL_AudioSpec audio_specs_;

  Mix_Music* music_;
  Mix_Chunk* shoot_sound_;
  Mix_Chunk* hit_sound_;
  Mix_Chunk* other_sound_;

  MathPicture* sine_picture_;
  MathPicture* cosine_picture_;
  MathPicture* fibonaccie_picture_;
  MathPicture* prime_numbers_picture_;

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
  Node* spawners_;

  Vector2D<float> test_point_0_;
  Vector2D<float> test_point_1_;

  ScreenWriter writer_;
  int step_ = 0;

  MapFrame map_frame_;

  YasEngine() {};
  bool should_application_stop_running_ = false;
  YasInOut::Input* input_ = new YasInOut::Input();
  YasInOut::MousePositionChangeInformation* mouse_position_change_information_ =
      new YasInOut::MousePositionChangeInformation();
  int red_shot_downs_ = 0;
  int green_shotdowns_ = 0;
  int blue_shotdowns_ = 0;
  bool engine_instantiated_ = false;
  void readSettingsFromFile();
  void prepareRendering();
  void prepareBasicSettings();
  void checkEndianness();
  void handlePhysics();
  void handleDisassemblingGraphs(GameObject* gameObj);
  void handleDestroingCollectibles(GameObject* gameObj);
  void handlingAssemblingGraphs(GameObject* gameObj);
  void handleCollectiblesWithWallsCollisions(GameObject* object);
  bool isObjectProtagonist(GameObject* object);
  GameObject* getProtagonist(GameObject* object0, GameObject* object1);
  GameObject* getNotProtagonist(GameObject* object0, GameObject* object1);
  void handleProtagonistWithWallsCollisions(GameObject* object);
  void moveObjectToMapBoundries(GameObject* gameObject, Wall wall,
                                int shift = 0);
  void bounceCollectibles(GameObject* gameObject, Wall wall);
  void moveObjects();
  void prepareGameWorld();
  void setFrameAroundGameplaySpace();
  void prepareDataForDrawingGraphs();
  void prepareSineDrawing();
  void prepareCosineDrawing();
  void prepareFibonacciDrawing();
  void preparePrimesDrawing();
  void preparePlayer();
  void prepareInterface();
  void handleInput(SDL_Event& event);
  void handleKeyboardInput(SDL_Event& event);
  void handleMouseInput(SDL_Event& event);
  void handleMouseMovement();
  void deleteNotAliveObjects();
  void handleSpawningCollectibles();
  bool isObjectInSameQuarterAsProtagonist(int randomSpawner);
  void handleProjectiles();
  void handlePlayer();
  void update(double& deltaTime);
  void resetAll();
  void drawHudElements(double& deltaTime);
  void drawFrame(double& deltaTime);
  void render(double& deltaTime);
  void renderGameObjects(double& deltaTime);
  void renderOnViewports(double& deltaTime);
  void renderLevelChange();
  void renderWonScreen();
  Button::ButtonId checkWhichButtonClicked();
  void handleClickedButtons();
  void handleGameStateWhenESCbuttonPushed();
  void handleGameStateWhenSPACEbuttonPushed();
  void prepareSoundAndMusic();
  void drawButtons();
};

#endif
