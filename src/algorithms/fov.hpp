#ifndef FOV_HPP
#define FOV_HPP

#include <vector>
#include <list>

typedef struct position{
    int x;
    int y;
} position;

std::list< position > bresenham(position orig, position dest);

std::vector< std::vector < bool > > getVisibleRadius(int x, int y, int radius);



#endif