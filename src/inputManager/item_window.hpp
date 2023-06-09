#ifndef ITEM_WINDOW_HPP
#define ITEM_WINDOW_HPP

#include "../entities/entity.hpp"
#include "input_manager.hpp"

class ItemWindow : public InputManager {
public:
    ItemWindow(Entity* item);
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
    Entity* item;
};

#endif
