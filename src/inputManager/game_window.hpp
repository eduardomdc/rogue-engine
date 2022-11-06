#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <SDL2/SDL.h>
#include "input_manager.hpp"

class GameWindow : public InputManager {
public:
    GameWindow();
    virtual void handleInput(SDL_Event currentEvent);
};

#endif