#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include "input_manager.hpp"

class GameWindow : public InputManager {
public:
    GameWindow();
    int mouseX, mouseY;
    int lastMoveTick = 0;
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
};

#endif