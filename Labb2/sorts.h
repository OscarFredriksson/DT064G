#include <algorithm>

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

int* partition(int* begin, int* end, int pivot = -1)
{
    if(pivot == -1) pivot = *end;

    int* i = begin;

    for(int* j = begin; j != end; j++)
    {
        if(*j < pivot)
        {
            std::swap(*i, *j);
            i++;
        }
    }
    std::swap(*i, *end);
    return i;
}

int medianOfThree(int* begin, int* end)
{
    int* mid = begin + (end - begin) /2;

    if(*end < *begin)   std::swap(*end, *begin);
    if(*mid < *begin)   std::swap(*mid, *begin);
    if(*end < *mid)     std::swap(*end, *mid);

    return *end;   
}

void partition_quick_sort(int* begin, int* end)
{
    if(begin >= end) return;
        
    auto pivot = partition(begin, end);

    partition_quick_sort(begin, pivot - 1);
    partition_quick_sort(pivot + 1, end);
}

void median_quick_sort(int* begin, int* end)
{
    if(begin >= end) return;
        
    auto pivot = partition(begin, end, medianOfThree(begin, end));

    median_quick_sort(begin, pivot - 1);    
    median_quick_sort(pivot + 1, end);
}
