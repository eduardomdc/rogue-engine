#include "dice.hpp"
#include <cstdlib>

int roll(int amount, int die){
    int result = 0;
    for(int i=0; i<amount; i++){
        result += 1+(rand()%die);
    }
    return result;
}
