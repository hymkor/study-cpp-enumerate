#include <string>
#include <vector>
#include <iostream>
#include <set>

#include "enumerate.h"

void put(const enumerator<std::string> &each)
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

    put( make_enumerator(v) );

    std::set<std::string> s;
    s.insert( "1" );
    s.insert( "2" );
    s.insert( "3" );

    put( make_enumerator(s) );
}
