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
    const color white =					{100,	100,	100,	0,		0,			0,			0,		false};
    const color red =					{155,	60,	    60, 	0,		0,			0,			0,		false};
	const color blue =					{60,	 0,	   180, 	0,		0,			0,			0,		false};
}

#endif