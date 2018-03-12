#include "random.h"

Random::Random() : Random(time(NULL)){}

Random::Random(int seed){
    this->setSeed(seed);
}

int Random::getInt(){
    this->next();
    return (int) seed;
}

int Random::getInt(int max_value){
    this->next();
    return (int) seed%max_value;
}

    // Calcul de le prochaine nombre
void Random::next(){
     seed = ((seed * 1103515245) + 12345) & 0x7fffffff;
}

void Random::reset(){
    seed = init;
}

void Random::setSeed(int seed){
    this->seed = seed;
    this->init = seed;
}

int Random::getSeed(){
    return seed;
}

