#include "jsonContainer.hpp"

void JsonContainer::setJson(std::string jsonSource)
{
    try
    {
        bool isValid = utilites.isValid(jsonSource);

        if(isValid)
        {
            jsonFile = jsonSource;
        }
        else
        {
            std::cout << "The json file is incorrect! \n";
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << e.what();
    }
    
    
}

void JsonContainer::print()
{
    int counter = 0;
    bool isInString = false;
    bool isInArray = false;
    int lenght = jsonFile.size();
    int tabCount = 0;
    std::string tab = "    ";

    for (; counter < lenght; ++counter)
    {
        
        if (jsonFile.at(counter) == '}' && !isInString )
        {
            std::cout<<std::endl;
            --tabCount;

            for (size_t i = 0; i < tabCount; i++)
            {
                std::cout << tab;
            }  
        }

        std::cout << jsonFile.at(counter);

        if (jsonFile.at(counter) == '{' && !isInString)
        {
            ++tabCount;
            std::cout << std::endl;
            for (size_t i = 0; i < tabCount; i++)
            {
                std::cout << tab;
            }            
        }
        

        if (jsonFile.at(counter) == '[' && !isInString && !isInArray)
        {
            isInArray = true;
        }
        if (jsonFile.at(counter) == ']' && !isInString && isInArray)
        {
            isInArray = false;
        }

        if(jsonFile.at(counter) == '"' && !isInString)
        {
            isInString = true;
        }
        if (jsonFile.at(counter) == '"' && isInString)
        {
            isInString = false;
        }

        if(jsonFile.at(counter) == ',' && !isInString && !isInArray)
        {
            std::cout << std::endl;
            for (size_t i = 0; i < tabCount; i++)
            {
                std::cout << tab;
            }     
        }    
    }
}

void JsonContainer::remove(std::vector<std::string> parameters)
{
    bool isInString = false;
    bool isInArray = false;
    bool isInObject = false;
    std::string currentName = "";
    std::size_t parametersCount = parameters.size();
    std::size_t parametersMatch = 0;

    for (size_t counter = 1; counter< jsonFile.size(); ++counter)
    {

        if (jsonFile.at(counter) == '"')
        {
            ++counter;
            while (jsonFile.at(counter) != '"')
            {
                currentName.push_back(jsonFile.at(counter));
                ++counter;
            }
            std::cout << parameters.at(parametersMatch) << " = " << currentName << '\n';
            if (parameters.at(parametersMatch) == currentName)
            {
                ++parametersMatch;
                if (parametersMatch == parametersCount)
                {
                    while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '}') || isInArray || isInString || isInObject)
                    {
                        if (jsonFile.at(counter) == '{' && !isInObject)
                        {
                            isInObject = true;
                        }
                        if (jsonFile.at(counter) == '}' && isInObject)
                        {
                            isInObject = false;
                        }
                        if (jsonFile.at(counter) == '[' && !isInArray)
                        {
                            isInArray = true;
                        }
                        if (jsonFile.at(counter) == ']' && isInArray)
                        {
                            isInArray = false;
                        }
                        if (jsonFile.at(counter) == '"' && !isInString)
                        {
                            isInString = true;
                        }
                        if (jsonFile.at(counter) == '"' && isInString)
                        {
                            isInString = false;
                        }
                        std::cout << jsonFile.at(counter);
                        jsonFile.erase(jsonFile.begin() + counter);
                    }
                    if (jsonFile.at(counter) == ',')
                    {
                        jsonFile.erase(jsonFile.begin() + counter);
                    }
                    
                    --counter;
                    while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '{') || isInArray || isInString)
                    {
                        if (jsonFile.at(counter) == '[' && !isInArray)
                        {
                            isInArray = true;
                        }
                        if (jsonFile.at(counter) == ']' && isInArray)
                        {
                            isInArray = false;
                        }
                        if (jsonFile.at(counter) == '"' && !isInString)
                        {
                            isInString = true;
                        }
                        if (jsonFile.at(counter) == '"' && isInString)
                        {
                            isInString = false;
                        }
                        std::cout << jsonFile.at(counter);
                        jsonFile.erase(jsonFile.begin() + counter);
                        --counter;
                    }
                    if (jsonFile.at(counter+1) == '}' && jsonFile.at(counter) == ',')
                    {
                        jsonFile.erase(jsonFile.begin() + counter);
                    }
                }
                else 
                {
                    counter = 1;
                }
                
            }
            currentName = "";
        }

        if (parametersCount == parametersMatch)
        {
            break;
        }
        

        while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '}') || isInArray || isInString)
        {
            if (jsonFile.at(counter) == '[' && !isInArray)
            {
                isInArray = true;
            }
            if (jsonFile.at(counter) == ']' && isInArray)
            {
                isInArray = false;
            }
            if (jsonFile.at(counter) == '"' && !isInString)
            {
                isInString = true;
            }
            if (jsonFile.at(counter) == '"' && isInString)
            {
                isInString = false;
            }
            if (jsonFile.at(counter) == '{' && !isInString)
            {
                std::cout << counter;
                break; 
            }
            
            ++counter;                          
        }
    }

    if(parametersCount != parametersMatch)
    {
        throw std::invalid_argument("there is no object with this name ot path in the file");
    }
}

void JsonContainer::edit(std::vector<std::string> commandArguments)
{
    std::string objectName = commandArguments.at(0);
    std::string objectValue = commandArguments.at(1);
    std::size_t obejctValueCounter = 0;
    std::string currentObjectName = "";
    std::size_t jsonLenght = jsonFile.size();
    bool isObjectFounded = false;
    bool isInArray = false;
    bool isInString = false;
    bool isInObject = false;
    std::size_t counter = 1;
    std::cout << '\n'
              << objectValue << '\n';

    if (!utilites.isObjectValueValid(objectValue, obejctValueCounter, objectValue.size()))
    {
        throw std::invalid_argument("the value that you want to set is invalid");
    }
    std::cout << jsonFile << std::endl;
    for (; counter < jsonLenght; ++counter)
    {
        
        
        if (jsonFile.at(counter) == '"')
        {
            ++counter;
           
            while (jsonFile.at(counter) != '"')
            {
                currentObjectName.push_back(jsonFile.at(counter));
                ++counter;
            }
           
            counter += 2;
        }
        if (currentObjectName == objectName)
        {
            isObjectFounded = true;
            int currentElementPosition = counter;

            int elementsCount = 0;
            while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '}') || isInArray || isInString || isInObject)
            {
                if (jsonFile.at(counter) == '{' && !isInObject)
                {
                    isInObject = true;
                }
                if (jsonFile.at(counter) == '}' && isInObject)
                {
                    isInObject = false;
                }
                if (jsonFile.at(counter) == '[' && !isInArray)
                {
                    isInArray = true;
                }
                if (jsonFile.at(counter) == ']' && isInArray)
                {
                    isInArray = false;
                }
                if (jsonFile.at(counter) == '"' && !isInString)
                {
                    isInString = true;
                }
                if (jsonFile.at(counter) == '"' && isInString)
                {
                    isInString = false;
                }

                ++elementsCount;
                ++counter;
            }
            if (jsonFile.at(counter - 1) == '}' && counter == jsonLenght)
            {
                --elementsCount;
            }
            
            jsonFile.replace(currentElementPosition, elementsCount, objectValue);

            break;
        }
        currentObjectName = "";
        while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '}') || isInArray || isInString || isInObject)
        {
            if (jsonFile.at(counter) == '{' && !isInObject)
            {
                isInObject = true;
                break;
            }
            if (jsonFile.at(counter) == '}' && isInObject)
            {
                isInObject = false;
            }
            if (jsonFile.at(counter) == '[' && !isInArray)
            {
                isInArray = true;
            }
            if (jsonFile.at(counter) == ']' && isInArray)
            {
                isInArray = false;
            }
            if (jsonFile.at(counter) == '"' && !isInString)
            {
                isInString = true;
            }
            if (jsonFile.at(counter) == '"' && isInString)
            {
                isInString = false;
            }
            ++counter;
        }
    }
    
    if (!isObjectFounded)
    {
        throw std::invalid_argument("there is not object with such name");
    }
}

void JsonContainer::move(std::vector<std::string> commandArguments)
{
    std::string sourceName = commandArguments.at(0);
    std::string currentObjectName = "";
    std::string currentObjectValue = "";
    std::string destinationName = commandArguments.at(1);
    bool isInArray = false;
    bool isInString = false;
    bool isInObject = false;

    for (std::size_t counter = 1; counter <jsonFile.size() ; ++counter)
    {
        if (jsonFile.at(counter) == '"')
        {
            ++counter;
           
            while (jsonFile.at(counter) != '"')
            {
                currentObjectName.push_back(jsonFile.at(counter));
                ++counter;
            }
           
            counter += 2;
        }
        if (currentObjectName == sourceName)
        {
            int elementsCount = 0;
            while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '}') || isInArray || isInString || isInObject)
            {
                if (jsonFile.at(counter) == '{' && !isInObject)
                {
                    isInObject = true;
                }
                if (jsonFile.at(counter) == '}' && isInObject)
                {
                    isInObject = false;
                }
                if (jsonFile.at(counter) == '[' && !isInArray)
                {
                    isInArray = true;
                }
                if (jsonFile.at(counter) == ']' && isInArray)
                {
                    isInArray = false;
                }
                if (jsonFile.at(counter) == '"' && !isInString)
                {
                    isInString = true;
                }
                if (jsonFile.at(counter) == '"' && isInString)
                {
                    isInString = false;
                }
                currentObjectValue.push_back(jsonFile.at(counter));
                ++counter;
            }
            std::vector<std::string> parameters;
            parameters.push_back(destinationName);
            parameters.push_back(currentObjectValue);
            edit(parameters);
        }

        currentObjectName = "";
        while ((jsonFile.at(counter) != ',' && jsonFile.at(counter) != '}') || isInArray || isInString || isInObject)
        {
            if (jsonFile.at(counter) == '{' && !isInObject)
            {
                isInObject = true;
                break;
            }
            if (jsonFile.at(counter) == '}' && isInObject)
            {
                isInObject = false;
            }
            if (jsonFile.at(counter) == '[' && !isInArray)
            {
                isInArray = true;
            }
            if (jsonFile.at(counter) == ']' && isInArray)
            {
                isInArray = false;
            }
            if (jsonFile.at(counter) == '"' && !isInString)
            {
                isInString = true;
            }
            if (jsonFile.at(counter) == '"' && isInString)
            {
                isInString = false;
            }
            ++counter;
        }
    }
}