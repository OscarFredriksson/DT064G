#ifndef LINEAR_H
#define LINEAR_H

#include <string>

template<typename Iter>
class Linear_Search
{
    Linear_Search(Iter begin, Iter end):
        begin(begin),
        end(end)
    {}

    template<typename T>
    T* find(T val)
    {
        while(begin++ != end)
        {
            if(*begin == val)   return &(*begin);
        }

        return nullptr;
    }
    
    inline static const std::string path = "benchmarks/linear_search";
    inline static const std::string name = "Linear Search";

private:
    Iter begin;
    Iter end;
};

#endif