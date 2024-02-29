#ifndef LOOK_HPP
#define LOOK_HPP

#include "../entities/entity.hpp"
#include "input_manager.hpp"

class Look : public InputManager {
public:
    Look();
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
    int cursorX;
    int cursorY;
};

#endif
