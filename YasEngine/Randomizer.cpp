#include"Randomizer.hpp"

#include <cstdlib>
#include <ctime>

int Randomizer::drawNumberClosedInterval(int min, int max)
{
    // srand(clock());
    int range = max - min + 1;
    return rand() % range + min;
}
