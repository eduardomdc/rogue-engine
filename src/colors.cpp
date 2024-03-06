#include "colors.hpp"
#include <random>

color colorManager::randomize(color c){
    if(c.redRand != 0)
        c.red += rand() % (c.redRand + 1);
    if(c.greenRand != 0)
        c.green += rand() % (c.greenRand + 1);
    if(c.blueRand != 0)
        c.blue += rand() % (c.blueRand + 1);
    return c;
}

const color colors::null =					{1, 2, 3, 0, 0, 0, 0, false};
const color colors::white =					{255, 255, 255, 0, 0, 0, 0, false};
const color colors::red =					{255,   0,   0, 0,   0,	0, 0, false};
const color colors::green =					{0,   255,   0, 0,   0,	0, 0, false};
const color colors::blue =					{0,   0,   255, 0,   0,	0, 0, false};
const color colors::lightBlue =				{100,   100,   255, 0,   0,	0, 0, false};
const color colors::yellow =                {255, 255, 0, 0, 0, 0, 0, false};
const color colors::brown =                 {139, 39, 19, 0, 0, 0, 0, false};
const color colors::black = 				{0, 0, 0, 0, 0,	0,	0,	false};
const color colors::grey =					{95, 95, 95, 0, 0, 0, 0, false};
const color colors::pearly =				{155, 155, 155, 100, 100, 100, 0, false};
const color colors::yellowFire = 			{155,   105,   0, 60,   30,	0, 0, true};
const color colors::fire = 					{155,   0,   0, 100,   60,	0, 0, true};
const color colors::playerFire = 			{155,   30,   30, 100,   60,	0, 0, true};
const color colors::blueMagic = 			{0,   100,   200, 0,   60,	55, 0, true};
const color colors::fireAverage = 			{255,   90,   10, 0,   0,	0, 0, true};
const color colors::dark =					{25, 25, 25, 2, 2, 25, 0, false};
const color colors::caveBlue =				{40,40,	80, 50, 50, 50, 0,	false};
const color colors::goblinGreen =           {0,70,	0, 0, 100, 100, 0, false};
const color colors::mossyGreen =			{30,50,	60, 0, 100, 100, 0, false};
const color colors::rusty = 				{85,   30,   30, 50,   0,	0, 0, false};
const color colors::rocky =                 {55,55,55, 10, 10 , 20, 0, false};
const color colors::snow =                  {165,165,165, 30, 30 , 30, 0, false};
const color colors::grassyGreen =           {120, 190, 20, 50, 30, 0, 0, false};
const color colors::darkGrassy =            {50,50,50,5,10,5,0,false};
