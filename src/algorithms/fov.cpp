#include "fov.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <iostream>
#include <algorithm>

std::list<position> bresenham(position orig, position dest) {
    std::list<position> line;
    line.push_back({0,0});

    bool flip = false; // if slope is steep we will flip x to y
    bool negativeX = false; // if x is negative
    bool negativeY = false; // if y is negative
    position temp = dest; // destiny position casting to the 0th octant
    //{-3,-4}
    if (dest.x < 0){
        temp.x = -dest.x;//{3,-4}
        negativeX = true;
    }
    if (dest.y < 0){
        temp.y = -dest.y;//{3,4}
        negativeY = true;
    } 
    // check if slope is steeper than y=x then flip over the y=x axis
    if (abs(dest.y)>abs(dest.x)) {
        flip = true;
        int swap = temp.x;
        temp.x = temp.y;
        temp.y = swap;
    }

    position current = {0,0};
    // bresenham, integer only version
    while (current.x != temp.x){
        if ( (2*temp.y*(current.x+1)-temp.x*(2*current.y+1)) > 0 ){
            current.x += 1;
            current.y += 1;
            line.push_back(current);
        }  else  {
            current.x +=1;
            line.push_back(current);
        }
    }
    // flip x,y to original steeper slope
    std::list<position>::iterator it;
    if (flip){
        int temp;
        for (it = line.begin(); it != line.end(); ++it){
            temp = it->x;
            it->x = it-> y;
            it->y = temp;
        }
    }
    // bring back to original sign
    for (it = line.begin(); it != line.end(); ++it){
        if (negativeX) it->x = -it->x;
        if (negativeY) it->y = -it->y;
    }

    // shift all points to origin
    for (it = line.begin(); it != line.end(); ++it){
        it->x += orig.x;
        it->y += orig.y;
    }

    return line;
}

std::list<position> straightPath(position orig, position dest){
    // returns in map straight path from orig to dest
    // without orig
    // returns empty list if there is no unobstructed straight path => go to A*
    std::list<position> path;
    std::list<position> line = bresenham(orig,{dest.x - orig.x, dest.y - orig.y});
    std::list<position>::iterator it;
    it = line.begin();
    bool hasPath = true;
    while ((it != line.end()) and hasPath){
        if (game->map->inMap(it->x, it->y)){
            if (game->map->tileMap[it->x][it->y].walkable ){
                path.push_back(*it);
            }
            else {
            hasPath = false;
                path.clear();
            }
        }
        else {
            hasPath = false; // if one tile in the path is not walkable then there's no path
            path.clear();
        }
        it++;
    }
    if (path.size() > 1){
        path.pop_front(); // remove origin
    }
    return path;
}

std::list<position> straightPathToWall(position orig, position dest){
    // returns in map straight path from orig to dest
    // without orig
    // returns current list if there is a wall in the straight path
    std::list<position> path = {};
    std::list<position> line = bresenham(orig,{dest.x - orig.x, dest.y - orig.y});
    std::list<position>::iterator it;
    it = line.begin();
    while ((it != line.end())){
        if (game->map->inMap(it->x, it->y)){
            if (game->map->tileMap[it->x][it->y].walkable){
                path.push_back(*it);
            }
            else {
                if (path.size() > 1){
                    path.pop_front(); // remove origin
                }
                return path;
            }
        }
        
        else {
            if (path.size() > 1){
                path.pop_front(); // remove origin
            }
            return path;
        }
        it++;
    }
    if (path.size() > 1){
        path.pop_front(); // remove origin
    }
    return path;
}

std::vector< std::vector < bool > > getVisibleRadius(int x, int y, int radius){
    // need to implement Symmetric Shadowcasting Algorithm by Albert Ford
    // really bad algorithm by me!
    // init array[radius][radius] filled with false
    int size = 2*radius+1;
    std::vector<std::vector <bool>> visible( size, std::vector <bool>(size, false));
    
    std::list<position> line;
                
    for (int oct = 0; oct < 4; oct++){
        for (int k = -radius; k <= radius; k++){
            switch (oct){
                case 0:
                    line  = bresenham({radius, radius},{radius,k});
                    break;
                case 1:
                    line  = bresenham({radius, radius},{-radius,k});
                    break;
                case 2:
                    line  = bresenham({radius, radius},{k,radius});
                    break;
                case 3:
                    line  = bresenham({radius, radius},{k,-radius});
                    break;
            }
            
    
            std::list<position>::iterator it;
            for (it = line.begin(); it != line.end(); ++it){
                int mapX = it->x - radius + x;
                int mapY = it->y - radius + y;
                if (mapX >= 0 && mapX < game->map->mapWidth
                &&  mapY >= 0 && mapY < game->map->mapHeight){
                    if (game->map->tileMap[mapX][mapY].transparent)
                        visible[it->x][it->y] = true;
                    else{
                        visible[it->x][it->y] = true;
                        break;
                    }
                }
            }
        }
    }
    return visible;
}

bool isBlocking(position position){
    if (!(position.x >= 0 && position.y>= 0 && position.x < game->map->mapWidth && position.y < game->map->mapHeight)){
        return true;
    }
    return !(game->map->tileMap[position.x][position.y].transparent);
}

// SYMMETRIC SHADOWCASTING




int roundTiesUp(float n){
    return floor(n + 0.5);
}

int roundTiesDown(float n){
    return ceil(n - 0.5);
}
/**
    Quadrant transformation matrixes.
    {xx, xy, yx, yy}
 */
static const int quadrant_table[4][4] = {
    {1,     0,      0,      1},
    {0,     1,      1,      0},
    {0,    -1,     -1,      0},
    {-1,    0,      0,     -1},
};
/**
    Information for the current active row.
 */
typedef struct Row {
  const int pov_x;  // The origin point-of-view.
  const int pov_y;
  const int quadrant;  // The quadrant index.
  int depth;  // The depth of this row.
  float slope_low;
  const float slope_high;
} Row;

static bool is_symmetric(const Row* __restrict row, int column) {
  return column >= row->depth * row->slope_low && column <= row->depth * row->slope_high;
}

static float slope(int row_depth, int column) { return (2.0f * column - 1.0f) / (2.0f * row_depth); }

position getArrayPos(position mapPos, position origin, int radius){
    return {mapPos.x + radius - origin.x , mapPos.y + radius - origin.y};
}

static void scan(Row* __restrict row, std::vector<std::vector <short>>* visible, int radius){
    try{
    const int xx = quadrant_table[row->quadrant][0];
    const int xy = quadrant_table[row->quadrant][1];
    const int yx = quadrant_table[row->quadrant][2];
    const int yy = quadrant_table[row->quadrant][3];
    // int mapX = row->pov_x + row->depth * xx;
    // int mapY = row->pov_y + row->depth * yx;
    // if (!game->map->inMap(mapX,mapY)){
    //     return; //Row->depth out of bounds
    // }
    if (row->depth > radius){
        return;
    }
    const int column_min = roundTiesUp(row->depth * row->slope_low);
    const int column_max = roundTiesDown(row->depth * row->slope_high);
    bool prev_tile_is_wall = false;
    for (int column = column_min; column <= column_max; column++){
        const int map_x = row->pov_x + row->depth * xx + column * xy;
        const int map_y = row->pov_y + row->depth * yx + column * yy;
        // if (!game->map->inMap(map_x, map_y)){
        //     return; // tile is out of bounds
        // }
        const bool isWall = isBlocking({map_x, map_y});
        if (isWall || is_symmetric(row, column)){
            position fovMatrixPos = getArrayPos({map_x, map_y}, {row->pov_x,row->pov_y}, radius);
            (*visible)[fovMatrixPos.x][fovMatrixPos.y] = 1;
        }
        if (prev_tile_is_wall && !isWall){
            row->slope_low = slope(row->depth, column);
        }
        if (column != column_min && !prev_tile_is_wall && isWall){
            Row next_row = {
                .pov_x = row->pov_x,
                .pov_y = row->pov_y,
                .quadrant = row->quadrant,
                .depth = row->depth + 1,
                .slope_low = row->slope_low,
                .slope_high = slope(row->depth, column),
            };
            scan(&next_row, visible, radius);
        }
        prev_tile_is_wall = isWall;
    }
    if (!prev_tile_is_wall){
        row->depth += 1;
        scan(row, visible, radius);
    }
    }
    catch(...){
        std::cout << "scan() error" << std::endl;
    }
}



std::vector<std::vector<short>> computeFOV(int x, int y, int radius){
    // symmetric shadowcasting algorithm by Albert Ford from libtcod source
    try{
    int size = 2*radius+1;
    std::vector<std::vector <short>> visible(size, std::vector <short>(size, 0));
    position fovMatrixPos = getArrayPos({x, y}, {x,y}, radius);
    visible[fovMatrixPos.x][fovMatrixPos.y] = 1;

    for (int i = 0; i< 4; i++){
        Row row = {
        .pov_x = x,
        .pov_y = y,
        .quadrant = i,
        .depth = 1,
        .slope_low = -1,
        .slope_high = 1,
        };
        scan(&row, &visible, radius);
    }
    return visible;
    }
    catch(...){
        std::cout<<"computeFOV() error"<<std::endl;
        return std::vector<std::vector <short>>(2*radius+1, std::vector <short>(2*radius+1, 0));
    }
}
