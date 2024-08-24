#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "game_object.hpp"
#include "time_picker.hpp"
#include "vector_2d.hpp"

class Spawner {
 public:
  int time_between_spawns_;
  TimePicker time_picker_;
  Vector2D<int> position_;
  Vector2D<int> spawn_position_;
  int spawning_max_radius_ = 24;
  int spawning_min_radius_ = 8;
  int max_value_for_drawing_spawning_direction_ = 4;
  double start_time_ = 0;
  double current_time_ = 0;
  double previous_time_ = 0;
  bool first_spawned_ = false;

  static int number_of_spawned_objects_;

  Spawner();

  Spawner(int x, int y);
  void SpawnObject(GameObject*& game_object);
  void ResetTimes();

 private:
  void PrepareObjectToSpawn(GameObject*& game_object);
};

#endif
