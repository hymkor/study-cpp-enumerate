#include <string>
#include <iostream>
#include "enumerate2.h"

void sub(pair_enumerator<std::string,int> &each)
{
    std::string key;
    int value;
    while( each(key,value) ){
        std::cout << key << ":" << value << std::endl;
    }
}

