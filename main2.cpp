#include <map>
#include <string>

#include "enumerate2.h"

extern void sub(pair_enumerator<std::string,int> &each);

int main(){
    std::map<std::string,int> map;

    map["ahaha"] = 1;
    map["ihihi"] = 2;
    map["ufufu"] = 3;

    sub(make_pair_enumerator(map));
}
