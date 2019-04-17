#include <iostream>
#include <random>
#include <chrono>
#include <vector>

std::mt19937 gen;

std::uniform_int_distribution<int> dist(1, 999);

int* find_min(int* begin, int* end)
{
    auto min = begin;
    while(begin++ != end)
    {
        if(*begin < *min)   min = begin;
    }

    return min;
} 

void selection_sort(int* begin, int* end)
{
    for(int * i = begin; i != end; i++)
    {
        int* min = find_min(i, end);

        std::swap(*i, *min);
    }
}

void insertion_sort(int* begin, int* end)
{
    for(int* i = begin; i != end+1; i++)
    {
        for(int* j = i; j != begin && *(j-1) > *j; j--)
        {
            std::swap(*j, *(j-1));
        }
    }
}

void print(const int& i)
{
    std::cout << i << " ";
}

int main()
{
    std::vector<int> numbers;

    for(int i = 0; i < 20; i++)
        numbers.push_back(dist(gen));

    std::for_each(&numbers.front(), &numbers.back(), print);
    std::cout << "\n";

    //selection_sort(&numbers.front(), &numbers.back());
    
    insertion_sort(&numbers.front(), &numbers.back());

    std::for_each(&numbers.front(), &numbers.back(), print);
    std::cout << "\n";


    return 0;
}