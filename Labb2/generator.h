#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>
#include <vector>

class Generator
{
public:
    Generator(const int min, const int max);

    std::vector<int> random(const int N);

    std::vector<int> constant(const int N);

    std::vector<int> rising(const int N);

    std::vector<int> falling(const int N);

private:
    void set_dist(const int N);

    std::mt19937 gen;

    using distribution = std::uniform_int_distribution<int>;

    distribution dist;
};

#endif