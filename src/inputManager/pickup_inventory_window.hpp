#ifndef PICKUP_INVENTORY_WINDOW_HPP
#define PICKUP_INVENTORY_WINDOW_HPP

#include "input_manager.hpp"

class Entity;

class PickupInventoryWindow : public InputManager {
public:
    PickupInventoryWindow(Entity* holder);
    Entity* holder;
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
};

#endif
