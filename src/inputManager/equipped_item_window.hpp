#ifndef EQUIPPED_ITEM_WINDOW_HPP
#define EQUIPPED_ITEM_WINDOW_HPP

#include "../entities/entity.hpp"
#include "input_manager.hpp"

class EquippedItemWindow : public InputManager {
public:
    EquippedItemWindow(Entity* item);
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
    Entity* item;
};

#endif
