#include <functional>
#include <iostream>
#include <map>

void put(std::function<bool(std::pair<std::string,int> &)> each){
    std::pair<std::string,int> pair;
    while( each(pair) ){
        std::cout << pair.first << ":" << pair.second << "\n";
    }
}

int main(){
    std::map<std::string,int> map;
    map["ahaha"] = 1;
    map["ihihi"] = 2;
    map["ufufu"] = 3;

    auto iterator = map.begin();
    put( [&iterator,&map](std::pair<std::string,int> &value){
        if ( iterator == map.end() ) {
            return false;
        }
        value = *iterator;
        iterator++;
        return true;
    });
    return 0;
}
