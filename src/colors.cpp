#include "colors.hpp"
#include <random>

color colorManager::randomize(color c){
    c.red += rand() % (c.redRand + 1);
    c.green += rand() % (c.greenRand + 1);
    c.blue += rand() % (c.blueRand + 1);
    return c;
}

const color colors::white =					{255, 255, 255, 0, 0, 0, 0, false};
const color colors::red =					{185,   0,   0, 70,   0,	0, 0, false};
const color colors::blue =					{30,	 30,	   180, 	50,		50,			50,			0,		false};
const color colors::black = 				{0,		 0,	   	 0, 	0,		0,			0,			0,		false};
const color colors::grey =					{95, 95, 95, 0, 0, 0, 0, false};
const color colors::pearly =				{155, 155, 155, 100, 100, 100, 0, false};
const color colors::fire = 					{255,   0,   0, 0,   220,	0, 0, true};
const color colors::dark =					{25, 25, 25, 0, 0, 25, 0, false};
const color colors::rusty = 				{85,   30,   30, 50,   0,	0, 0, false};
const color colors::rocky =                 {55,55,75, 10, 10 , 30, 0, false};
