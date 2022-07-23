#ifndef COLOR_HPP
#define COLOR_HPP

typedef struct lightColor {
	short red;
	short green;
	short blue;
} lightColor;

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
	extern const color null; // for entities with no background
    extern const color white;
    extern const color red;
	extern const color blue;
	extern const color black;
	extern const color grey;
	extern const color pearly;
	extern const color fire;
	extern const color dark;
	extern const color rusty;
	extern const color rocky;
}

class colorManager {
public:
	static color randomize(color c);
};

#endif