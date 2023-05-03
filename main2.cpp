#include <string>
#include <map>
#include <unordered_map>

#include "enumerate2.h"

extern void sub(pair_enumerator<std::string,int> &each);

int main(){
    std::map<std::string,int> map;
    map["ahaha"] = 1;
    map["ihihi"] = 2;
    map["ufufu"] = 3;
    sub(make_pair_enumerator(map));

    std::unordered_map<std::string,int> umap;
    umap["AHAHA"] = 1;
    umap["IHIHI"] = 2;
    umap["UFUFU"] = 3;
    sub(make_pair_enumerator(umap));
}
