#include <string>
#include <vector>
#include <set>
#include <list>

template<class T> void put(T cursor,T end);
extern template void put<std::vector<std::string>::iterator>(std::vector<std::string>::iterator cursor,std::vector<std::string>::iterator end);
extern template void put<std::set<std::string>::iterator>(std::set<std::string>::iterator cursor,std::set<std::string>::iterator end);

int main(){
    std::vector<std::string> v;
    v.push_back( "a" );
    v.push_back( "b" );
    v.push_back( "c" );

    put( v.begin() , v.end() );

    std::set<std::string> s;
    s.insert( "1" );
    s.insert( "2" );
    s.insert( "3" );

    put( s.begin() , s.end() );
}
