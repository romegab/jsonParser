#include <iostream>
#include "commandExecutor.hpp"


int main()
{
    CommandExecutor commandExecutor;
    std::string file = "{\"int\":34, \"char\": 's' , \"string\": \"Ivan Stoilov\", \"object\":{\"digit\": 1234}, \"boolFalse\": false, \"boolTrue\": true, \"null\":null, \"array\" : [12, \"hello\"]         }";

    commandExecutor.setJsonFile(file);
    commandExecutor.executeCommmand("move array int");
    commandExecutor.executeCommmand("print");
}