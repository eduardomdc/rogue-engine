#ifndef CREATURE_HPP
#define CREATURE_HPP

class Entity;

class Creature {
public:
    void setWeight(int weight);
    bool needsFood = true; // creature needs food to live
    void setFood(Entity* owner, int food);
    int getFood();
    int fitnessLevel;
private:
    /**
     *  for a creature that weighs (x)g 
     *  it will  need (x)g of food to be healthy
     * **/
    int weight; // weight in grams;
    int healthyWeight; // healthy weight for creature
    int food; // amount of food the creature has
};

enum fitness {
    skinny,
    normal,
    fat
};

#endif