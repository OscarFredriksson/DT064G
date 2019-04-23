#include <iostream>
#include <chrono>
#include <vector>
#include "generator.h"

int& find_min(int* begin, int* end)
{
    int* min = begin;
    
    while(begin++ != end)
    {
        if(*begin < *min)   min = begin;
    }

    return *min;
} 

void selection_sort(int* begin, int* end)
{
    std::for_each(begin, end, [&end](int& iter)
    {
        int& min = find_min(&iter, end);

        std::swap(iter, min);
    });
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
    Generator gen(1, 50);

    std::vector<int> src = gen.random(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    src = gen.constant(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    src = gen.rising(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    src = gen.falling(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";


    /*selection_sort(&numbers.front(), &numbers.back());
    std::for_each(numbers.begin(), numbers.end(), print);
    std::cout << "\n";

    numbers = src;
    insertion_sort(&numbers.front(), &numbers.back());
    std::for_each(numbers.begin(), numbers.end(), print);

    std::cout << "\n";*/


    return 0;
}