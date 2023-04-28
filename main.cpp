#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <functional>

#include "enumerate.h"

void put(const std::function<bool(std::string&)> &each)
{
    std::string value;
    while( each(value) ){
        std::cout << value << std::endl;
    }
}

int main(void)
{
    std::vector<std::string> v;
    v.push_back( "a" );
    v.push_back( "b" );
    v.push_back( "c" );

    put( enumerator<std::vector<std::string>>(v.begin(),v.end()) );

    std::set<std::string> s;
    s.insert( "1" );
    s.insert( "2" );
    s.insert( "3" );

    put( enumerator<std::set<std::string>>(s.begin(),s.end()) );
}
