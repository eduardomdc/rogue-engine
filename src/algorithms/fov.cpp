#include "../game.hpp"

//std::vector < std::vector < int > > raycast(int x, int y, int destX, int destY) {
    // bresenham's
//} 

std::vector< std::vector < bool > > getVisibleRadius(int x, int y, int radius) {
    // Symmetric Shadowcasting Algorithm by Albert Ford
    return {{true, false},{false,true}};
}