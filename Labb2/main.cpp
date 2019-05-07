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

int main()
{
    Generator gen(1, 50);

    std::vector<int> src = gen.random(30);

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

    //partition(&src.front(), &src.back());

    median_quick_sort(&src.front(), &src.back());

    std::for_each(src.begin(), src.end(), print);
    std::cout << "\n";

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