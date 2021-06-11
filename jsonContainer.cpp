#include "jsonContainer.hpp"
#include<ostream>

bool JsonContainer::isObjectExists(std::string sourceName)
{ 

    bool isInArray = false;
    bool isInString = false;
    bool isInObject = false;

    std::string currentObjectName = "";
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
            return true;
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

    return false;
}

void JsonContainer::setJson(std::string jsonSource, std::string jsonSourcePath)
{
    try
    {
        bool isValid = utilites.isValid(jsonSource);

        if(isValid)
        {
            jsonFile = jsonSource;
            filePath = jsonSourcePath;
        }
        else
        {
            std::cout << "The json file is incorrect! \n";
        }
    }
    catch(const std::invalid_argument& e)
    {
        throw e;
    }
    
    
}

void JsonContainer::print()
{    
    std::cout << getJsonAsStrings()<<std::endl;
}

void JsonContainer::remove(std::vector<std::string> parameters)
{
    if (jsonFile.size() <= 2)
    {
        throw std::invalid_argument("remove command cannot be applied to empty file");
    }
    
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
    if (jsonFile.size() <= 2)
    {
        throw std::invalid_argument("remove command cannot be applied to empty file");
    }

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

    if (!utilites.isObjectValueValid(objectValue, obejctValueCounter, objectValue.size()))
    {
        throw std::invalid_argument("the value that you want to set is invalid");
    }
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
    bool isExecuted = false;
    if (jsonFile.size() <= 2)
    {
        throw std::invalid_argument("remove command cannot be applied to empty file");
    }

    std::string sourceName = commandArguments.at(0);
    std::string currentObjectName = "";
    std::string currentObjectValue = "";
    std::string destinationName = commandArguments.at(1);
    bool isInArray = false;
    bool isInString = false;
    bool isInObject = false;

    if (!isObjectExists(sourceName) || !isObjectExists(destinationName))
    {
        std::invalid_argument("the source or the destination name are invalid");
    }

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
            isExecuted = true;
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

void JsonContainer::create(std::vector<std::string> commandArguments)
{
    std::string objectName = commandArguments.at(0);
    std::string objectValue = commandArguments.at(1);
    bool isObjectValueValid;
    std::size_t objectValueCounter = 0;
    std::string objectAsString = "";

    try
    {
        isObjectValueValid = utilites.isObjectValueValid(objectValue, objectValueCounter, objectValue.size());
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("the object cannot be created because of invalid value");
    }
    

    if(isObjectValueValid)
    {
        if (isObjectExists(objectName))
        {
            throw std::invalid_argument("an object with the same name already exists");
        }

        objectAsString = ",\""+objectName + "\":" + objectValue + '}';
        if (jsonFile.size() == 2)
        {
            objectAsString = "\"" + objectName + "\":" + objectValue + '}';
        }
        

        jsonFile.replace(jsonFile.size() - 1, 1, objectAsString);
    }    
}

void JsonContainer::search(std::string commandParameter)
{
    searchResult.clear();

    bool isInArray = false;
    bool isInString = false;
    bool isInObject = false;
    std::string searchResult = "";
    std::string currentObjectName = "";
    if (jsonFile.size() <= 2)
    {
        throw std::invalid_argument("search command cannot be applied to empty file");
    }

    if (!isObjectExists(commandParameter))
    {
        throw std::invalid_argument("the object you search doesn't exist");
    }

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
        if (currentObjectName == commandParameter)
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
                searchResult.push_back(jsonFile.at(counter));
                ++counter;
            }

            break;
        }
        else
        {
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
        currentObjectName = "";
    }

    if(searchResult.at(0) != '{')
    {
        searchResult = "{\"" + commandParameter + "\":" + searchResult + "}";
        this->searchResult.push_back(searchResult);
    }
    else
    {
        for (std::size_t counter = 1; counter <jsonFile.size() ; ++counter)
        {
            if(counter == searchResult.size())
            {
                break;
            }

            std::string searchResultCurrentElement = "";
            while ((searchResult.at(counter) != ',' && searchResult.at(counter) != '}') || isInArray || isInString)
            {
                if (searchResult.at(counter) == '{' && !isInObject)
                {
                    isInObject = true;
                }
                if (searchResult.at(counter) == '}' && isInObject)
                {
                    isInObject = false;
                }
                if (searchResult.at(counter) == '[' && !isInArray)
                {
                    isInArray = true;
                }
                if (searchResult.at(counter) == ']' && isInArray)
                {
                    isInArray = false;
                }
                if (searchResult.at(counter) == '"' && !isInString)
                {
                    isInString = true;
                }
                if (searchResult.at(counter) == '"' && isInString)
                {
                    isInString = false;
                }
                searchResultCurrentElement.push_back(searchResult.at(counter));
                ++counter;
            }

            searchResultCurrentElement = '{' + searchResultCurrentElement + '}';
            this->searchResult.push_back(searchResultCurrentElement);
        }
    }
}

std::string JsonContainer::getJsonAsStrings()
{
    if (jsonFile.size() == 2)
    {
        return jsonFile;
    }
    

    std::string result = "";
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
            result += '\n';
            --tabCount;

            for (size_t i = 0; i < tabCount; i++)
            {
                result += tab;
            }  
        }

        result += jsonFile.at(counter);

        if (jsonFile.at(counter) == '{' && !isInString)
        {
            ++tabCount;
            result += '\n';
            for (size_t i = 0; i < tabCount; i++)
            {
                result += tab;
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
            result += '\n';
            for (size_t i = 0; i < tabCount; i++)
            {
                result += tab;
            }     
        }    
    }

    return result;
}

void JsonContainer::save(std::string parameter)
{

    std::ofstream write;
    write.open(filePath);
    if (!write.is_open())
    {
        throw std::invalid_argument("no file was setted so json cannot be saved");
    }
    if(parameter == "min")
    {
        write << jsonFile;
    }
    else
    {
        std::string regularJsonFile = getJsonAsStrings();
        write << regularJsonFile;
    }

    write.close();
}

void JsonContainer::saveas(std::string path, std::string saveMode)
{
    std::ofstream write;
    write.open(path);
    if (!write.is_open())
    {
        throw std::invalid_argument("file cannot be created - path is invalid!");
    }
    if(saveMode == "min")
    {
        write << jsonFile;
    }
    else
    {
        std::string regularJsonFile = getJsonAsStrings();
        write << regularJsonFile;
    }

    write.close();
}

std::string JsonContainer::getJson()
{
    return jsonFile;
}

void JsonContainer::printSearchResult()
{
    if(searchResult.size() ==0)
    {
        throw std::invalid_argument("there is not result from search command");
    }
    else if (searchResult.size() == 1)
    {
        std::cout << "result:" << std::endl;
        std::cout << searchResult.at(0);
    }
    else
    {
        std::cout << "result:" << std::endl;
        for (std::size_t i = 0; i < searchResult.size(); i++)
        {
            std::cout << searchResult.at(i) << std::endl;
        }
        
    }
}