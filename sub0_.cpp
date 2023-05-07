#include <iostream>
#include <vector>
#include <set>
#include <list>

template<class T> void put(T cursor,T end)
{
    for( ; cursor != end ; cursor++ ){
        std::cout << *cursor << std::endl;
    }
}

template void put<std::vector<std::string>::iterator>(std::vector<std::string>::iterator cursor,std::vector<std::string>::iterator end);
template void put<std::set<std::string>::iterator>(std::set<std::string>::iterator cursor,std::set<std::string>::iterator end);
