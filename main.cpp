#include <iostream>
#include <map>
#include "lib.h"

int main(int, char const **)
{
    // 1.создание экземпляра std::map<int, int>
    std::map<int, int> stdMap;
    for(int i = 0; i < 10; ++i)
        stdMap.insert({i, getFuctorial(i)});
    for (const auto& n : stdMap)
        std::cout << n.first << " " << n.second << "; " << std::endl;

    // 2. создание экземпляра std::map<int, int> с новым аллокатором
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> allocMap;
    for(int i = 0; i < 10; ++i)
        allocMap.insert({i, getFuctorial(i)});
    for (const auto& n : allocMap)
        std::cout << n.first << " " << n.second << "; " << std::endl;

    // 3. создание экземпляра своего контейнера для хранения значений типа int
    MyVector<int> vec;
    for(int i = 0; i < 10; ++i)
        vec.push_back(i);
    for(std::size_t i= 0 ; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    // 4. создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
    MyVector<int, MyAllocator<int>> vecAlloc;
    for(int i = 0; i < 10; ++i)
        vecAlloc.push_back(i);
    for(std::size_t i= 0 ; i < vecAlloc.size(); ++i)
        std::cout << vecAlloc[i] << " ";
    std::cout << std::endl;
    return 0;
}
