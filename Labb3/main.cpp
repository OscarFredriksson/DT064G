#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <chrono>
#include <random>
#include "algorithms.h"
#include "bst.h"
#include "hash.h"

std::vector<int> get_primes(const int N)
{
    std::vector<bool> prime(N, true); 

    prime[0] = false;
    prime[1] = false;
  
    for (int i = 2; i <= std::sqrt(N); i++) 
    { 
        if (prime[i]) 
        {
            for(int j = i*i; j <= N; j += i) 
                prime[j] = false; 
        }
    } 
  
    std::vector<int> ret;

    for(int i = 2; i <= N; i++)
        if(prime[i])    ret.push_back(i);
    
    return ret;
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

template<typename Algorithm>
void benchmark(Algorithm alg)
{
    std::mt19937 gen(std::random_device{}());

    const int samples = 5;
    int start_N = std::pow(10, 4);
    int end_N = start_N * 10;

    const std::string path = alg.path + ".data";
    
    std::ofstream file;
    file.open(path.c_str(), std::fstream::out);

    file << alg.name << "\n";
    file << "N" << "\t\t\t" << "T[ms]" << "\t\t" << "Stdev[ms]" << "\t" << "Samples" << "\n";

    for(int N = start_N; N <= end_N; N += start_N)
    {
        std::vector<double> times;

        for(int i = 0; i < samples; i++)
        {
            std::vector<int> src = get_primes(N);

            //std::cout << N << "\n";

            const int val = std::uniform_int_distribution<int>(0, N)(gen);

            //std::cout << "Number to find: " << val << "\n";

            auto start = std::chrono::high_resolution_clock::now();

            auto found = alg(src.begin(), src.end(), val);

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            times.push_back(duration.count());

            if(!found)  std::cout << "Hittade inte värdet: " << val << "\n";
            else        std::cout << "Hittade värdet: " << val << "\n";

            if((found != nullptr) != std::binary_search(src.begin(), src.end(), val))
            {
                std::cout << "CRITICAL: Algoritmen hittade fel!    \n";
            }

            //std::cout << times.back() << ", ";
        }

        //std::cout << "\n";

        file << N << "\t\t" << mean(times) << "\t\t" << stdDev(times) << "\t\t" << samples << "\n";
    }
    //std::cout << "\n";

    file.close();
}

void print(const int i)
{
    std::cout << i << ", ";
}

int main()
{
    //std::vector<int> primes = get_primes(100000);

    //HashTable<int> hashtable(primes.begin(), primes.end());

    //std::cout << *hashtable.find(13) << "\n";

    //BinarySearchTree<int> bst(primes.begin(), primes.end());

    //std::cout << *bst.find(13);

    //benchmark(Linear_Search());
    //benchmark(Binary_Search());
    //benchmark(Binary_Search_Tree());
    benchmark(Hash_Table());


    //std::for_each(primes.begin(), primes.end(), print);
    //std::cout << "\n";

    //std::cout << *LinearSearch(primes.begin(), primes.end(), 90);
    //std::cout << "\n";

   // std::cout << *BinarySearch(primes.begin(), primes.end(), 90);
    //std::cout << "\n";

    return 0;
}