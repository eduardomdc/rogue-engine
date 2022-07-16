#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL2/SDL.h>

class EventManager{
public:
    static int parseKeypress(SDL_Event event);
};

#endif