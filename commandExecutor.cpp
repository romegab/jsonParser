#include "commandExecutor.hpp"

void CommandExecutor::trimCommand(std::string &command)
{
    //trim left side
    while (command[0] == ' ')
    {
        command.erase(0, 1);
    }

    //trim right side
    std::size_t lastIndex = command.size() - 1;
    
    while (command[lastIndex] == ' ')
    {
        command.erase(lastIndex, 1);
        --lastIndex;
    }
}

void CommandExecutor::removeInsideSpaces(std::string &command)
{
    std::size_t commandLenght = command.size();

    for (std::size_t counter = 0; counter < commandLenght - 1; ++counter)
    {      
        if (command[counter] == ' ' && command[counter + 1] == ' ')
        {
            command.erase(counter, 1);
            --counter;
            --commandLenght;
        }
        
        if (command[counter] == '"')
        {
            ++counter;
            while(command[counter] != '"' && counter < commandLenght - 1)
            {                
                ++counter;
            }
        }
    }    
}

void CommandExecutor::toLowerCase(std::string &command)
{
    std::size_t commandLenght = command.size();

    for(int i = 0; i < commandLenght; i++) 
    {
        command.at(i) = tolower(command.at(i));
    }
}

void CommandExecutor::validateCommand(std::string &command)
{
    trimCommand(command);
    removeInsideSpaces(command);
    toLowerCase(command);
}

void CommandExecutor::executeCommmand(std::string command)
{
    validateCommand(command);

    if (command == "print")
    {
        
    }
    
}