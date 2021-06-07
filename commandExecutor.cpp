#include "commandExecutor.hpp"

void CommandExecutor::setJsonFile(std::string jsonFile)
{
    jsonContainer.setJson(jsonFile);
}

void CommandExecutor::trimFile(std::string &file)
{
    //trim left side
    while (file[0] == ' ')
    {
        file.erase(0, 1);
    }

    //trim right side
    std::size_t lastIndex = file.size() - 1;
    
    while (file[lastIndex] == ' ')
    {
        file.erase(lastIndex, 1);
        --lastIndex;
    }
}

std::string CommandExecutor::getCommandType(std::string command)
{
    std::string result = "";

    for (std::size_t counter = 0; counter < command.size(); ++counter)
    {
        if (command.at(counter) == ' ')
        {
            break;
        }

        result.push_back(command.at(counter));
    }

    return result;
}

void CommandExecutor::removeInsideSpaces(std::string &command)
{
    std::size_t commandLenght = command.size();

    for (std::size_t counter = 0; counter < commandLenght; ++counter)
    {      
        if (command[counter] == '"')
        {
            ++counter;
            while(command[counter] != '"' && counter < commandLenght - 1)
            {                                
                ++counter;

                if (command[counter] == '\\' && command[counter + 1] == '\"')
                {
                    counter += 2;
                }
                
            }
        }

        if (command[counter] == ' ' && command[counter - 1] == ' ')
        {
            command.erase(counter, 1);
            --counter;
            --commandLenght;
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

std::vector<std::string> CommandExecutor::getCommandArguments(std::string command)
{
    int counter = 0;
    std::vector<std::string> parameters;
    std::string currentParamete = "";
    bool isInString = false;
    bool isInArray = false;
    bool isInObject = false;

    while (command.at(counter) !=' ')
    {
        ++counter;
    }
    ++counter;
    for (; counter < command.size(); ++counter)
    {
        if (command.at(counter) == '"' && isInString)
        {
            isInString = false;
        }

        if (command.at(counter) == '"' && !isInString)
        {
            isInString = true;
        }
        if (command.at(counter) == ']' && isInString)
        {
            isInArray = false;
        }

        if (command.at(counter) == '[' && !isInArray)
        {
            isInArray = true;
        }
        if (command.at(counter) == '}' && isInObject)
        {
            isInObject = false;
        }

        if (command.at(counter) == '{' && !isInObject)
        {
            isInObject = true;
        }
        
        if (command.at(counter) == ' ' && !isInString && !isInObject && !isInArray)
        {
            std::cout << isInString;
            parameters.push_back(currentParamete);
            currentParamete = "";
        }       

        else
        {
            currentParamete.push_back(command.at(counter));
        }
        
        if (counter == command.size() - 1)
        {
            parameters.push_back(currentParamete);
            break;
        }
    }

    return parameters;
}

void CommandExecutor::validateCommand(std::string &command)
{
    trimFile(command);
    removeInsideSpaces(command);
    std::cout << command;
}

void CommandExecutor::executeCommmand(std::string command)
{
    validateCommand(command);

    std::string commandType = getCommandType(command);
    toLowerCase(commandType);

    if (commandType == "print")
    {
        jsonContainer.print();
    }
    else if(commandType == "edit")
    {
        std::vector<std::string> commandArguments = getCommandArguments(command);
        jsonContainer.edit(commandArguments);
    }
    else if(commandType == "remove")
    {
        std::vector<std::string> commandArguments = getCommandArguments(command);
        jsonContainer.remove(commandArguments);
    }
    else if(commandType == "move")
    {
        std::vector<std::string> commandArguments = getCommandArguments(command);
        if (commandArguments.size() <2)
        {
            throw std::invalid_argument("the move operation requires two parameters(source and destination)");
        }

        jsonContainer.move(commandArguments);
    }
}

