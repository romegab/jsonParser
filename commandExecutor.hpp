#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include<string>

class CommandExecutor
{
private:
    void validateCommand(std::string &command);
    //command peraparation command
    void trimCommand(std::string &command);
    void removeInsideSpaces(std::string &command);
    void toLowerCase(std::string &command);

public:
    void executeCommmand(std::string command);
};

#endif