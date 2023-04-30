#include <string>
#include <vector>
#include <set>
#include <list>
#include "enumerate.h"

extern void put(enumerator<std::string> &each);

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

    std::list<std::string> ls;
    ls.push_back( "x" );
    ls.push_back( "y" );
    ls.push_back( "z" );

    put( make_enumerator(ls) );
}
