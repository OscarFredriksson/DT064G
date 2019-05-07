#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "generator.h"
#include "sorts.h"

void print(const int& i)
{
    std::cout << i << " ";
}

double mean(std::vector<double> src)
{
    auto sum = std::accumulate(src.begin(), src.end(), 0.0);
    
    return sum/src.size();
}

double stdDev(std::vector<double> src)
{
    double avg = mean(src);
    
    double square_sum = std::accumulate(src.begin(), src.end(), 0.0, [&avg](double sum, double val)
    {
        return sum += std::pow(val - avg, 2);
    });
    
    return std::sqrt(1.0 / (src.size() - 1) * square_sum);
}

void test_sort()
{
    const int samples = 5;

    Generator gen(1, 500);

    std::vector<double> times;

    for(int i = 0; i < samples; i++)
    {
        std::vector<int> src = gen.random(20000);

        auto start = std::chrono::high_resolution_clock::now();

        insertion_sort(&src.front(), &src.back());

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        times.push_back(duration.count());
    }

    std::cout << "Mean:" << "\t" << mean(times) << "ms" << "\n";
    std::cout << "StdDev:" << "\t" << stdDev(times) << "ms" << "\n";
    
}

int main()
{
    test_sort();

    /*Generator gen(1, 50);

    std::vector<int> src = gen.random(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    median_quick_sort(&src.front(), &src.back());

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";*/

    /*src = gen.constant(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    src = gen.rising(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    src = gen.falling(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";*/


    /*selection_sort(&numbers.front(), &numbers.back());
    std::for_each(numbers.begin(), numbers.end(), print);
    std::cout << "\n";

    numbers = src;
    insertion_sort(&numbers.front(), &numbers.back());
    std::for_each(numbers.begin(), numbers.end(), print);

    std::cout << "\n";*/


    return 0;
}