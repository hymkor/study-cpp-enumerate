#include <string>
#include <iostream>
#include "enumerate.h"

void put(const enumerator<std::string> &each)
{
    std::string value;
    while( each(value) ){
        std::cout << value << std::endl;
    }
}
