#ifndef COLOR_HPP
#define COLOR_HPP

typedef struct color {
    // from brogue
	// base RGB components:
	short red; // red
	short green;
	short blue;
	
	// random RGB components to add to base components:
	short redRand;
	short greenRand;
	short blueRand;
	
	// random scalar to add to all components:
	short rand;
	
	// Flag: this color "dances" with every refresh:
	bool colorDances;
} color;

namespace colors {
    const color white =					{255, 255, 255, 0, 0, 0, 0, false};
    const color red =					{185,   0,   0, 70,   0,	0, 0, false};
	const color blue =					{30,	 30,	   180, 	50,		50,			50,			0,		false};
	const color black = 				{0,		 0,	   	 0, 	0,		0,			0,			0,		false};
	const color grey =					{95, 95, 95, 0, 0, 0, 0, false};
	const color pearly =				{155, 155, 155, 100, 100, 100, 0, false};
	const color fire = 					{255,   0,   0, 0,   220,	0, 0, true};
	const color dark =					{25, 25, 25, 0, 0, 25, 0, false};
	const color rusty = 				{85,   30,   30, 50,   0,	0, 0, false};
	const color rocky = 				{55,55,75, 10, 10 , 30, 0, false};
}

class colorManager {
public:
	static color randomize(color c);
};

#endif