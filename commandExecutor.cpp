#include "commandExecutor.hpp"

void CommandExecutor::setJsonFile(std::string jsonFile, std::string filePath)
{
    jsonContainer.setJson(jsonFile, filePath);
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
        if (counter == command.size())
        {
            break;
        }
        
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
}

void CommandExecutor::executeCommmand(std::string command)
{
    validateCommand(command);
    std::string commandType = getCommandType(command);
    toLowerCase(commandType);
    std::vector<std::string> commandArguments = getCommandArguments(command);
    if (commandType == "print")
    {
        if (commandArguments.size() > 0)
        {
            throw std::invalid_argument("the print command works without arguments");
        }
        
        jsonContainer.print();
    }
    else if(commandType == "edit")
    {
        if (commandArguments.size() != 2)
        {
            throw std::invalid_argument("the edit operation requires two parameters(destination and value)");
        }
        jsonContainer.edit(commandArguments);
    }
    else if(commandType == "remove")
    {
        if (commandArguments.size() != 1)
        {
            throw std::invalid_argument("the remove command works with one argument <object name>");
        }
        jsonContainer.remove(commandArguments);
    }
    else if(commandType == "move")
    {
        if (commandArguments.size() != 2)
        {
            throw std::invalid_argument("the move operation requires two parameters <source> and <destination>)");
        }

        jsonContainer.move(commandArguments);
    }
    else if (commandType == "create")
    {
        if (commandArguments.size() != 2)
        {
            throw std::invalid_argument("create operation requirs two parameters <name> and <value>)");
        }
        
        removeInsideSpaces(commandArguments.at(1));
        jsonContainer.create(commandArguments);
    }
    else if (commandType == "search")
    {
        if (commandArguments.size() != 1)
        {
            throw std::invalid_argument("search operation requirs one parameters <object name>");
        }

        jsonContainer.search(commandArguments.at(0));
    }
    else if(commandType == "save")
    {
        if (commandArguments.size() > 0)
        {
            throw std::invalid_argument("the save command works without arguments");
        }

        std::cout << "if you want to save the jsonFile with minimum volume type \"min\". \n if you want to save the jsonFile regularly type \"regularly\"";
        std::string saveType;
        std::getline(std::cin, saveType);
        if (saveType != "min" && saveType != "regularly")
        {
            throw std::invalid_argument("the save method is invalid!");
        }
        
        jsonContainer.save(saveType);
    }

    else if(commandType == "saveas")
    {
        if (commandArguments.size() != 1)
        {
            throw std::invalid_argument("the saveas command requires 1 parameter - file path");
        }

        std::cout << "if you want to saveas the jsonFile with minimum volume type \"min\". \n if you want to saveas the jsonFile regularly type \"regularly\"";
        std::string saveType;
        std::getline(std::cin, saveType);
        if (saveType != "min" && saveType != "regularly")
        {
            throw std::invalid_argument("the save method is invalid!");
        }
        
        jsonContainer.saveas(commandArguments.at(0), saveType); 
    }
    else if(commandType == "printsearch")
    {
        if (commandArguments.size() != 0)
        {
            throw std::invalid_argument("the printSearch command doesnt require");
        }
        jsonContainer.printSearchResult();
    }
    else
    {
        throw std::invalid_argument("the command is invalid");
    }
}

std::string CommandExecutor::readFile(std::string filePath)
{
    std::ifstream readFile;
    std::string currentLine;
    std::string result = "";
    readFile.open(filePath);

    if (readFile.is_open())
    {
        while (getline(readFile, currentLine))
        {
            result += currentLine;
        }
        
    }
    else
    {
        throw std::invalid_argument("the source file is not existing");
    }
    return result;
}