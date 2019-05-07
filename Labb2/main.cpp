#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>
#include "generator.h"
#include "sorts.h"

void print(const int& i)
{
    std::cout << i << " ";
}

double round(double val, int decimal_places)
{
    return std::floor(val * std::pow(10, decimal_places) + 0.5) / std::pow(10, decimal_places);
}

double mean(std::vector<double> src)
{
    double sum = std::accumulate(src.begin(), src.end(), 0.0); 

    double ret = sum/src.size();

    return round(ret, 4);
}

double stdDev(std::vector<double> src)
{
    double avg = mean(src);
    
    double square_sum = std::accumulate(src.begin(), src.end(), 0.0, [&avg](double sum, double val)
    {
        return sum += std::pow(val - avg, 2);
    });
    
    double ret = std::sqrt(1.0 / (src.size() - 1) * square_sum);

    return round(ret, 4);
}

void test_sort()
{
    const int samples = 5;
    int N = 0;

    Generator gen(1, 500);

    for(int j = 0; j < 10; j++)
    {
        N += 20000;

        std::vector<double> times;

        for(int i = 0; i < samples; i++)
        {
            std::vector<int> src = gen.random(N);

            auto start = std::chrono::high_resolution_clock::now();

            insertion_sort(&src.front(), &src.back());

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            times.push_back(duration.count());
        }

        //std::cout << "Mean:" << "\t" << mean(times) << "ms" << "\n";
        //std::cout << "StdDev:" << "\t" << stdDev(times) << "ms" << "\n";

        std::string path = "benchmarks/insertion_sort/random.data";
        std::ofstream file;

        file.open(path.c_str(), std::fstream::app);

        file << N << "\t\t" << mean(times) << "\t\t" << stdDev(times) << "\t\t" << samples << "\n";
    }
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