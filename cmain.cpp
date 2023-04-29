#include <string>
#include <vector>
#include <set>
#include "cenumerate.h"

extern void put(const enumerator<std::string> &each);

int main(void)
{
    std::vector<std::string> v;
    v.push_back( "a" );
    v.push_back( "b" );
    v.push_back( "c" );

    put( make_const_enumerator(v) );

    std::set<std::string> s;
    s.insert( "1" );
    s.insert( "2" );
    s.insert( "3" );

    put( make_const_enumerator(s) );
}
