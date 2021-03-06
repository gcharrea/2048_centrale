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

    // Calcul de le prochain nombre
void Random::next(){
     step++;
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

void Random::toStep(int s){
    if(s < step){
        step = 0;
        seed = init;
    }
    while(step < s){
        next();
    }
}

ofstream& operator<< (ofstream& out, Random& r){
    out << r.init << " " << r.step << " " << r.seed << " ";
    return out;
}

istream& operator>> (istream& in, Random& r){
    in >> r.init;
    in >> r.step;
    in >> r.seed;
    return in;
}



