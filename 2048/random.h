#ifndef RANDOM_H
#define RANDOM_H

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

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

    void toStep(int s);

    friend ofstream& operator<< (ofstream& out, Random& r);
    friend istream& operator>> (istream& in, Random& r);

private:
    void next();

private:
    int seed;
    int step = 0;
    int init;
};

#endif // RANDOM_H
