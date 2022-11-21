#include "input_manager.hpp"
#include "../game.hpp"

void InputManager::close(){
    std::vector<InputManager*>::iterator window;
    window = game->windows.begin();
    while (window != game->windows.end()){
        if (*window == this){
            game->windows.erase(window);
            break;
        }
        window++;
    }
    // delete this;
}