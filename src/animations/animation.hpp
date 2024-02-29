#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "../colors.hpp"
#include "../entities/entity.hpp"

class Animation{
public:
    int posX;
    int posY;
    int subPosX = 0; // position within the cell at posX, posY. Cells are divided into 4 subcells (0,0) (0,1) (1,0) (1,1)
    int subPosY = 0;
    SDL_Rect src;
    SDL_Rect dest;
    Uint32 frameStart;
    int currentFrame;
    int frames; // amount of frames
    int speed; // amount of ms between each frame
    SDL_Texture* codepage;
    int tileWidth; // resolution of tiles used
    int tileHeight;
    color foreRgb;
    color backRgb;
    lightColor illumination = {0,0,0};

    bool onMap = false; // is the animation on the map or in the UI?
    bool lit = false;
    bool done = false; // is the animation finished?

    bool damageNumber = false;
    short int damageNumberMove = 0;

    Animation();

    void setFrames(std::vector<std::vector<std::string>> framesASCII);

    void nextFrame();
    void render();

private:
    std::vector<std::vector<std::string>> chFrames;
};

void bipedalStepAnimation(int posX, int posY, int targetX, int targetY, bool rightStep);
void punchAnimation(int posX, int posY, int dirX, int dirY);
void slashAnimation(int posX, int posY);
void pickUpAnimation(Entity* item);
void receiveAnimation(Entity* receiver, Entity* item);
#endif
