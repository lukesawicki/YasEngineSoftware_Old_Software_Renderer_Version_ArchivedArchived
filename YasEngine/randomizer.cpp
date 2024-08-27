#include "randomizer.hpp"

#include <cstdlib>
#include <ctime>

int Randomizer::DrawNumberClosedInterval(const int min, const int max) {
  srand(clock());
  int range = max - min + 1;
  return rand() % range + min;
}
