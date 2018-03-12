#ifndef RANDOM_H
#define RANDOM_H

#include <time.h>
#include <stdio.h>

class Random
{
public:
    Random();
    Random(int seed);

    int getInt();
    int getInt(int max_value);

    int getSeed();
    void setSeed(int seed);
    void reset();

private:
    void next();

private:
    int seed;
    int init;
};

#endif // RANDOM_H
