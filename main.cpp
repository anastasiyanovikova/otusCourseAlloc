#include <iostream>
#include <map>
#include "lib.h"

int main(int, char const **)
{
    {
        // std::map
        std::map<int, int> stdMap;
        for(int i = 0; i < 10; ++i)
            stdMap.insert({i, getFuctorial(i)});

        for(auto it = stdMap.begin(); it != stdMap.end(); ++it)
            std::cout << it->first << " " << it->second << std:: endl;
    }
    {
        // std::map with MyAllocator
        std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> allocMap;
        for(int i = 0; i < 10; ++i)
            allocMap.insert({i, getFuctorial(i)});

        for(auto it = allocMap.begin(); it != allocMap.end(); ++it)
            std::cout << it->first << " " << it->second << std:: endl;
    }
    {
        // my container
        MyVector<int> vec;
        for(int i = 0; i < 10; ++i)
            vec.push_back(i);
        
        for(std::size_t i= 0 ; i < vec.size(); ++i)
            std::cout << vec[i] << " ";
        std::cout << std::endl;
    }

    {
        // my container with MyAllocator
        MyVector<int, MyAllocator<int>> vec;
        for(int i = 0; i < 10; ++i)
            vec.push_back(i);
        for(std::size_t i= 0 ; i < vec.size(); ++i)
            std::cout << vec[i] << " ";
        std::cout << std::endl;
    }

    return 0;
}
