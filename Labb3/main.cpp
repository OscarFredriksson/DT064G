#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>


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

int main()
{
    std::vector<int> primes = get_primes(100);

    std::for_each(primes.begin(), primes.end(), [](const int& prime)
    {
        std::cout << prime << ", ";
    });

    return 0;
}