#ifndef EQUIPMENT_WINDOW_HPP
#define EQUIPMENT_WINDOW_HPP

#include "input_manager.hpp"

class EquipmentWindow : public InputManager {
public:
    EquipmentWindow();
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
};

#endif