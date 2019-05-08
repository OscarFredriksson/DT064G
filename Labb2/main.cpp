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

template<typename Sort>
void test_sort(Sort sort)
{
    const int samples = 5;
    int start_N =   20000;
    int end_N =     400000;

    Generator gen(1, 500);

    std::string path = sort.path + "random.data";
    std::ofstream file;

    file.open(path.c_str());

    file << sort.name << "\n";
    file << "N" << "\t\t\t" << "T[ms]" << "\t\t" << "Stdev[ms]" << "\t" << "Samples" << "\n";

    for(int N = start_N; N <= end_N; N+= 20000)
    {
        std::vector<double> times;

        for(int i = 0; i < samples; i++)
        {
            std::vector<int> src = gen.random(N);

            auto start = std::chrono::high_resolution_clock::now();

            sort(&src.front(), &src.back());

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            times.push_back(duration.count());

            //std::cout << duration.count() << ", ";
        }
        //std::cout << "\n";

        file << N << "\t\t" << mean(times) << "\t\t" << stdDev(times) << "\t\t" << samples << "\n";
    }
    std::cout << "\n";
}

int main()
{
    test_sort(Insertion_Sort());
    
    /*test_sort(Selection_Sort());

    test_sort(Partition_Quick_Sort());

    test_sort(Median_Quick_Sort());*/
    
    //test_sort(Std_Sort());

    return 0;
}