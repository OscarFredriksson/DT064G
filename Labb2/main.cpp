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

double mean(std::vector<double> src)
{
    double sum = std::accumulate(src.begin(), src.end(), 0.0); 

    double ret = double(sum)/src.size();

    return ret;
}

double stdDev(std::vector<double> src)
{
    double avg = mean(src);
    
    double square_sum = std::accumulate(src.begin(), src.end(), 0.0, [&avg](double sum, double val)
    {
        return sum += std::pow(val - avg, 2);
    });
    
    double ret = std::sqrt(1.0 / (src.size() - 1) * square_sum);

    return ret;  
}

enum DataType
{
    Random,
    Constant,
    Rising,
    Falling
};

template<typename Sort>
void benchmark(Sort sort, DataType datatype)
{
    const int samples = 5;
    int start_N = std::pow(10, 3);
    int end_N = start_N * 10;

    std::string datatype;

    switch(datatype)
    {  
        case Random:    datatype = "random";
                        break;
        case Constant:  datatype = "constant";
                        break;
        case Rising:    datatype = "rising";
                        break;
        case Falling:   datatype = "falling";
    }

    const std::string path = sort.path + datatype + ".data";
    
    std::ofstream file;
    file.open(path.c_str());

    file << sort.name << " - " << datatype << "\n";
    file << "N" << "\t\t\t" << "T[ms]" << "\t\t" << "Stdev[ms]" << "\t" << "Samples" << "\n";

    Generator gen(1, 9999);

    for(int N = start_N; N <= end_N; N += start_N)
    {
        std::vector<double> times;

        for(int i = 0; i < samples; i++)
        {
            std::vector<int> src;

            switch(datatype)
            {  
                case Random:    src = gen.random(N);
                                break;
                case Constant:  src = gen.constant(N);
                                break;
                case Rising:    src = gen.rising(N);
                                break;
                case Falling:   src = gen.falling(N);
                                break;
            }

            auto start = std::chrono::high_resolution_clock::now();

            sort(&src.front(), &src.back());

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duration = end - start;

            times.push_back(duration.count());

            std::cout << times.back() << ", ";
        }

        std::cout << "\n";

        file << N << "\t\t" << mean(times) << "\t\t" << stdDev(times) << "\t\t" << samples << "\n";
    }
    std::cout << "\n";

    file.close();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Starting standard sort" << "\n";
    std::cout << "Random value:" << "\n";
    benchmark(Std_Sort(), DataType::Random);
    std::cout << "Constant value:" << "\n";
    benchmark(Std_Sort(), DataType::Constant);
    std::cout << "Falling value:" << "\n";
    benchmark(Std_Sort(), DataType::Falling);
    std::cout << "Rising value:" << "\n";
    benchmark(Std_Sort(), DataType::Rising);
    std::cout << "Standard sort done!\n\n";

    std::cout << "Starting median quick sort" << "\n";
    std::cout << "Random value:" << "\n";
    benchmark(Median_Quick_Sort(), DataType::Random);
    std::cout << "Constant value:" << "\n";
    benchmark(Median_Quick_Sort(), DataType::Constant);
    std::cout << "Falling value:" << "\n";
    benchmark(Median_Quick_Sort(), DataType::Falling);
    std::cout << "Rising value:" << "\n";
    benchmark(Median_Quick_Sort(), DataType::Rising);
    std::cout << "Median quick sort done!\n\n";

    std::cout << "Starting partition sort" << "\n";
    std::cout << "Random value:" << "\n";
    benchmark(Partition_Quick_Sort(), DataType::Random);
    std::cout << "Constant value:" << "\n";
    benchmark(Partition_Quick_Sort(), DataType::Constant);
    std::cout << "Falling value:" << "\n";
    benchmark(Partition_Quick_Sort(), DataType::Falling);
    std::cout << "Rising value:" << "\n";
    benchmark(Partition_Quick_Sort(), DataType::Rising);
    std::cout << "Partition quick sort done!\n\n";

    std::cout << "Insertion sort, timestamps:" << "\n";
    std::cout << "Random value:" << "\n";
    benchmark(Insertion_Sort(), DataType::Random);
    std::cout << "Constant value:" << "\n";
    benchmark(Insertion_Sort(), DataType::Constant);
    std::cout << "Falling value:" << "\n";
    benchmark(Insertion_Sort(), DataType::Falling);
    std::cout << "Rising value:" << "\n";
    benchmark(Insertion_Sort(), DataType::Rising);
    std::cout << "Insertion sort done!\n\n"; 

    std::cout << "Selection sort, timestamps:" << "\n";
    std::cout << "Random value:" << "\n";
    benchmark(Selection_Sort(), DataType::Random);
    std::cout << "Constant value:" << "\n";
    benchmark(Selection_Sort(), DataType::Constant);
    std::cout << "Falling value:" << "\n";
    benchmark(Selection_Sort(), DataType::Falling);
    std::cout << "Rising value:" << "\n";
    benchmark(Selection_Sort(), DataType::Rising);
    std::cout << "Selection sort done!\n\n";

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Total time to test all sorts: " << duration.count()/60 << " minutes.\n";

    return 0;
}