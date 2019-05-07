#include "generator.h"
#include <algorithm>

Generator::Generator(const int min, const int max):
    gen(std::random_device()()),
    dist(min, max)
{}

std::vector<int> Generator::random(const int N)
{
    std::vector<int> ret(N);

    std::for_each(ret.begin(), ret.end(), [this](int& i)
    {
        i = dist(gen);
    });

    return ret;
}

std::vector<int> Generator::constant(const int N)
{
    std::vector<int> ret(N);

    int const_int = dist(gen);

    std::for_each(ret.begin(), ret.end(), [&const_int](int& i)
    {
        i = const_int;
    });

    return ret;
}

std::vector<int> Generator::rising(const int N)
{
    std::vector<int> ret = random(N);

    std::sort(ret.begin(), ret.end());

    return ret;
}

std::vector<int> Generator::falling(const int N)
{
    std::vector<int> ret = random(N);

    std::sort(ret.rbegin(), ret.rend());

    return ret;
}