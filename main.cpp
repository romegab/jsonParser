#include <iostream>
#include "jsonUtilities.hpp"

int main()
{
    JsonUtilities ju;
    std::string file = "{\"int\":1234, \"char\": 's' , \"string\": \"Ivan Stoilov\", \"object\":{\"digit\": 1234}, \"boolFalse\": false, \"boolTrue\": true, \"null\":null, \"array\" : [12, \"hello\"]         }";

    std::cout << ju.isValid(file);
    ju.remove("remove object digit");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";
   /* ju.remove("remove char");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";
    ju.remove("remove string");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";                    
    ju.remove("remove boolFalse");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";
    ju.remove("remove boolTrue");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";
    ju.remove("remove null");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";
    ju.remove("remove array");
    std::cout << "--------------------------------------" << '\n'
              << "--------------------------------";*/
}