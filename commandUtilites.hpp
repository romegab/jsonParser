#ifndef COMMANDUTILITIES_H
#define COMMANDUTILITIES_H
#include<vector>
#include<string>

class CommandUtilities
{
public:
    std::vector<std::string> getCommandArguments(std::string command);
    void removeInsideSpaces(std::string &command);
    void trimCommand(std::string &file);
};

#endif