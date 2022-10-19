#include "fov.hpp"
#include "../game.hpp"
#include "../map.hpp"

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

std::vector< std::vector < bool > > getVisibleRadius(int x, int y, int radius) {
    // Symmetric Shadowcasting Algorithm by Albert Ford
    // init array[radius][radius] filled with false
    int size = 2*radius+1;
    std::vector<std::vector <bool>> visible( size, std::vector <bool>(size, false));
    
    /**
    int mapX, mapY; // corresponding coordinates on game map
    for (int i = 0; i < size; i++){
        for (int j=0; j < size; j++){
            mapX = i - radius + x;
            mapY = j - radius + y;
            if (mapX >= 0 && mapX < game->map->mapWidth
            &&  mapY >= 0 && mapY < game->map->mapHeight){ //check if is inside map
                
                
            }
        }
    }
    **/
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
                    if (game->map->tileMap[it->x - radius + x][it->y - radius + y].transparent)
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