#include <iostream>
#include "jsonUtilities.hpp"

int main()
{
    JsonUtilities ju;
    std::string file = "{\"int\":1234, \"char\": 's' , \"string\": \"Ivan Stoilov\", \"object\":{\"digit\": 1234}, \"bool\": false, \"bool\": true, \"null\":null, \"array\" : [12, \"hello\"]         }";

    //std::cout << ju.isValid(file);
    ju.print(file);
}