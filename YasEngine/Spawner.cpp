#include "spawner.hpp"

#include <cstdlib>

#include "collectible.hpp"
#include "randomizer.hpp"

int Spawner::number_of_spawned_objects_ = 0;

Spawner::Spawner() {
  current_time_ = time_picker_.getMiliseconds();
  previous_time_ = current_time_;
  time_between_spawns_ = Randomizer::drawNumberClosedInterval(2000, 6000);
}

Spawner::Spawner(int x, int y) {
  position_.x = x;
  position_.y = y;
  current_time_ = time_picker_.getMiliseconds();
  previous_time_ = current_time_;
  time_between_spawns_ = +Randomizer::drawNumberClosedInterval(2000, 6000);
}

void Spawner::spawnObject(GameObject*& gameObject) {
  if (!first_spawned_) {
    prepareObjectToSpawn(gameObject);
    previous_time_ = time_picker_.getMiliseconds();
    first_spawned_ = true;
    current_time_ = time_picker_.getMiliseconds();
    return;
  }

  current_time_ = time_picker_.getMiliseconds();

  if ((current_time_ - previous_time_) >= time_between_spawns_) {
    prepareObjectToSpawn(gameObject);
    previous_time_ = current_time_;
  }
}

void Spawner::resetTimes() {
  previous_time_ = current_time_ = time_picker_.getMiliseconds();
}

void Spawner::prepareObjectToSpawn(GameObject*& gameObject) {
  int oldTargetPositionX = 0;
  int oldTargetPositionY = 0;
  int xPos = Randomizer::drawNumberClosedInterval(spawning_min_radius_,
                                                  spawning_max_radius_);
  int yPos = Randomizer::drawNumberClosedInterval(spawning_min_radius_,
                                                  spawning_max_radius_);
  int dirX = Randomizer::drawNumberClosedInterval(
      1, max_value_for_drawing_spawning_direction_);
  int dirY = Randomizer::drawNumberClosedInterval(
      1, max_value_for_drawing_spawning_direction_);

  int numberOfVertices = Randomizer::drawNumberClosedInterval(3, 7);

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

  int targetPositionX = position_.x + dirX * xPos;
  int targetPositionY = position_.y + dirY * yPos;

  if (oldTargetPositionX != targetPositionX ||
      oldTargetPositionY != targetPositionY) {
    gameObject =
        new Collectible(16, static_cast<float>(targetPositionX),
                        static_cast<float>(targetPositionY), numberOfVertices);
  }
}
