#include "spawner.hpp"

#include <cstdlib>

#include "collectible.hpp"
#include "randomizer.hpp"

int Spawner::number_of_spawned_objects_ = 0;

Spawner::Spawner() {
  current_time_ = time_picker_.GetMiliseconds();
  previous_time_ = current_time_;
  time_between_spawns_ = Randomizer::DrawNumberClosedInterval(2000, 6000);
}

Spawner::Spawner(int x, int y) {
  position_.x_ = x;
  position_.y_ = y;
  current_time_ = time_picker_.GetMiliseconds();
  previous_time_ = current_time_;
  time_between_spawns_ = +Randomizer::DrawNumberClosedInterval(2000, 6000);
}

void Spawner::SpawnObject(GameObject*& game_object) {
  if (!first_spawned_) {
    PrepareObjectToSpawn(game_object);
    previous_time_ = time_picker_.GetMiliseconds();
    first_spawned_ = true;
    current_time_ = time_picker_.GetMiliseconds();
    return;
  }

  current_time_ = time_picker_.GetMiliseconds();

  if ((current_time_ - previous_time_) >= time_between_spawns_) {
    PrepareObjectToSpawn(game_object);
    previous_time_ = current_time_;
  }
}

void Spawner::ResetTimes() {
  previous_time_ = current_time_ = time_picker_.GetMiliseconds();
}

void Spawner::PrepareObjectToSpawn(GameObject*& game_object) {
  int old_target_position_x = 0;
  int old_target_position_y = 0;
  int position_x = Randomizer::DrawNumberClosedInterval(spawning_min_radius_,
                                                  spawning_max_radius_);
  int position_y = Randomizer::DrawNumberClosedInterval(spawning_min_radius_,
                                                  spawning_max_radius_);
  int direction_x = Randomizer::DrawNumberClosedInterval(
      1, max_value_for_drawing_spawning_direction_);
  int direction_y = Randomizer::DrawNumberClosedInterval(
      1, max_value_for_drawing_spawning_direction_);

  int number_of_vertices = Randomizer::DrawNumberClosedInterval(3, 7);

  if (direction_x <= max_value_for_drawing_spawning_direction_ * 0.5) {
    direction_x = -1;
  }

  if (direction_x >= max_value_for_drawing_spawning_direction_ * 0.5) {
    direction_x = 1;
  }

  if (direction_y <= max_value_for_drawing_spawning_direction_ * 0.5) {
    direction_y = -1;
  }

  if (direction_y >= max_value_for_drawing_spawning_direction_ * 0.5) {
    direction_y = 1;
  }

  int targetPositionX = position_.x_ + direction_x * position_x;
  int targetPositionY = position_.y_ + direction_y * position_y;

  if (old_target_position_x != targetPositionX ||
      old_target_position_y != targetPositionY) {
    game_object =
        new Collectible(16, static_cast<float>(targetPositionX),
                        static_cast<float>(targetPositionY), number_of_vertices);
  }
}
