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
  int oldTargetPositionX = 0;
  int oldTargetPositionY = 0;
  int xPos = Randomizer::DrawNumberClosedInterval(spawning_min_radius_,
                                                  spawning_max_radius_);
  int yPos = Randomizer::DrawNumberClosedInterval(spawning_min_radius_,
                                                  spawning_max_radius_);
  int dirX = Randomizer::DrawNumberClosedInterval(
      1, max_value_for_drawing_spawning_direction_);
  int dirY = Randomizer::DrawNumberClosedInterval(
      1, max_value_for_drawing_spawning_direction_);

  int numberOfVertices = Randomizer::DrawNumberClosedInterval(3, 7);

  if (dirX <= max_value_for_drawing_spawning_direction_ * 0.5) {
    dirX = -1;
  }

  if (dirX >= max_value_for_drawing_spawning_direction_ * 0.5) {
    dirX = 1;
  }

  if (dirY <= max_value_for_drawing_spawning_direction_ * 0.5) {
    dirY = -1;
  }

  if (dirY >= max_value_for_drawing_spawning_direction_ * 0.5) {
    dirY = 1;
  }

  int targetPositionX = position_.x_ + dirX * xPos;
  int targetPositionY = position_.y_ + dirY * yPos;

  if (oldTargetPositionX != targetPositionX ||
      oldTargetPositionY != targetPositionY) {
    game_object =
        new Collectible(16, static_cast<float>(targetPositionX),
                        static_cast<float>(targetPositionY), numberOfVertices);
  }
}
