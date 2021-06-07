#include".\commandUtilites.hpp"

void CommandUtilities::trimCommand(std::string &file)
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

void CommandUtilities::removeInsideSpaces(std::string &command)
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

        if (command[counter] == ' ')
        {
            command.erase(counter, 1);
            --counter;
            --commandLenght;
        }
    }
    
}

std::vector<std::string> CommandUtilities::getCommandArguments(std::string command)
{
    int counter = 0;
    std::vector<std::string> parameters;
    std::string currentParamete = "";
    bool isInString = false;

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
        
        if (command.at(counter) == ' ' && !isInString)
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