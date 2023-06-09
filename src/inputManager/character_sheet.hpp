#ifndef CHARACTER_SHEET_HPP
#define CHARACTER_SHEET_HPP

#include "input_manager.hpp"

class CharacterSheet : public InputManager {
public:
    CharacterSheet();
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
};

#endif
