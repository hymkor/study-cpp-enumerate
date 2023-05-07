#include <iostream>

template<class T> void put(T cursor,T end)
{
    for( ; cursor != end ; cursor++ ){
        std::cout << *cursor << std::endl;
    }
}
