#include "perlin.hpp"

unitVector Perlin::randomUnitVector()
{
    unitVector vec;
    vec.x = rand()-RAND_MAX/2;
    vec.y = rand()-RAND_MAX/2;
    float length = sqrt(vec.x*vec.x + vec.y*vec.y);
    vec.x /= length;
    vec.y /= length;
    return vec;
}

Perlin::Perlin()
{
    // init grid vector
    for (int i = 0; i<this->size; i++){
        grid.push_back(std:: vector<unitVector >());
    }

    // generate grid of random unit vectors
    for(int i=0; i<this->size; i++){
        for (int j=0; j<this->size; j++){
            grid[i].push_back(randomUnitVector());
        }
    }
}

float Perlin::value(float x, float y){
    /**
     * we need to find the coordinates of the cell's
     * corners in which our (x,y) point lies inside.
     * The corners of a cell are
     *(x0,y0) X----------
        *        |         |
        *        |         |
        *        |         |
        *        ----------X (x1,y1)
        **/
    int x0 = floor(x);
    int y0 = floor(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float dx0 = x - x0; // distance vector from point to corners
    float dy0 = y - y0;
    float dx1 = x1 - x;
    float dy1 = y1 - y;
    
    /**
    * now calculate the dot product of each corner gradient vector 
    * with it's corresponding distance vector
    **/

    float dotVec0 = dotProd(grid[x0][y0].x, grid[x0][y0].y,  dx0,dy0);
    float dotVec1 = dotProd(grid[x1][y0].x, grid[x1][y0].y,  dx1,dy0);
    float dotVec2 = dotProd(grid[x1][y1].x, grid[x1][y1].y,  dx1,dy1);
    float dotVec3 = dotProd(grid[x0][y1].x, grid[x0][y1].y,  dx0,dy1);

    /**
    * interpolate between the two upper corners
    * and two bottom corners,
    * then interpolate vertically between those two
    * using the dy value
    **/

    float upper = interpolate(dotVec0, dotVec1, dx0);
    float bottom = interpolate(dotVec3, dotVec2, dx0);
    float value = interpolate(upper, bottom, dy0);

    return value;
}

float Perlin::dotProd(float x0, float y0, float x1, float y1){
    float dotProd = x0*x1 + y0*y1;
    return dotProd;
}

float Perlin::interpolate(float a0, float a1, float x){
    // smoothstep between values a0 to a1 through x:[0,1]
    return (a1 - a0) * (3.0 - x * 2.0) * x * x + a0;
}