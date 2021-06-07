#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include<string>
#include".\jsonContainer.hpp"

class CommandExecutor
{
private:
    void validateCommand(std::string &command);
    //command peraparation command
    void trimFile(std::string &command);
    void removeInsideSpaces(std::string &command);
    void toLowerCase(std::string &command);
    std::vector<std::string> getCommandArguments(std::string command);
    std::string getCommandType(std::string command);
    JsonContainer jsonContainer;

public:
    void executeCommmand(std::string command);
    void setJsonFile(std::string jsonFile);
};

#endif