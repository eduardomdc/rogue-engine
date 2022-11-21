#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP


#include <SDL2/SDL.h>
#include <iostream>

class InputManager{
public:
    virtual void handleInput(SDL_Event currentEvent){std::cout<<"calling virtual InputManager handleInput method"<<std::endl; return;};
    virtual void render(){std::cout<<"calling virtual InputManager render method"<<std::endl; return;};
    void close();
    virtual ~InputManager() = default;
};

#endif