#include "colors.hpp"
#include <random>

color colorManager::randomize(color c){
    c.red += rand() % (c.redRand + 1);
    c.green += rand() % (c.greenRand + 1);
    c.blue += rand() % (c.blueRand + 1);
    return c;
}