#include "creature.hpp"
#include "entity.hpp"


int Creature::getFood(){
    return this->food;
}

void Creature::setFood(Entity* owner, int food){
    this->food = food;
    // if food is too low, make owner->mind->motive = hungry
    if (needsFood){
        this->weight = food;
    } // each food unit is 1g

    if (weight > 1.5*healthyWeight){
        // creature is fat
    } else if (weight < 0.6 * healthyWeight && weight > 0.3 * healthyWeight){
        //creature is skinny
    } else if (weight < 0.3 * healthyWeight){
        if (needsFood){
            owner->destroy();
        }
    }
    else {
        //creature is normal
    }
    /** fix later: since weight is equal to food this means that you 
     * can't make creatures weightless without them being 
     * extremely skinny.**/
}

void Creature::setWeight(int weight){
    this->weight = weight;
    this->healthyWeight = weight;
}