#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP


#include <SDL2/SDL.h>
#include <iostream>

class InputManager{
public:
    virtual void handleInput(SDL_Event currentEvent){std::cout<<"nao pfvr para "<<std::endl; return;};
};

#endif