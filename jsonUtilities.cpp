#include "jsonUtilities.hpp"
#include <stdexcept>
#include <iostream>

void trimFile(std::string &file)
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

void removeInsideSpaces(std::string &command)
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

std::size_t JsonUtilities::getJsonLenght()
{
    return jsonFile.size();
}

std::vector<std::string> JsonUtilities::getCommandArguments(std::string command)
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

bool JsonUtilities::isValid(std::string jsonSource)
{
    std::size_t lenght = jsonSource.size();

    if (lenght > 0)
    {
        trimFile(jsonSource);
        removeInsideSpaces(jsonSource);
        lenght = jsonSource.size();

        if (jsonSource.front() == openingBracket && jsonSource.back() == closingBracket)
        {
            if (lenght == 2)
            {
                return true;
            }
            
            bool currentObjectName = false;
            bool currentObjectValue = false;

            for (std::size_t counter = 1; counter < lenght; ++counter)
            {
                try
                {
                    currentObjectName = isObjectNameValid(jsonSource, counter, lenght, colon);
                    ++counter;

                    if (!currentObjectName)
                    {
                        throw std::invalid_argument("an object in the json file is missing a name");
                    }
                    
                }
                catch(const std::invalid_argument& e)
                {
                    throw e;
                }

                if (jsonSource.at(counter) == ':')
                {
                    ++counter;
                }
                else
                {
                    throw std::invalid_argument("missing separator between name and value");
                }
                
                currentObjectValue = isObjectValueValid(jsonSource, counter, lenght);
            }
            if (!isFileLoaded)
            {
                jsonFile = jsonSource;
            }
            
            return true;
        }
        else
        {
            throw std::invalid_argument("json file is missing opening or closing bracket");
        }
    }
    else
    {
        return false;
    } 
}

bool JsonUtilities::isObjectNameValid(const std::string& jsonSource, std::size_t& counter, std::size_t lenght, const char separator )
{
    bool isValid = false;

    if (jsonSource[counter] != '"')
    {
        throw std::invalid_argument("an object in the json file has invalid name -> missing openign string bracket");
    }

    ++counter;

    while (jsonSource[counter] != '"' && counter < lenght)
    {
        ++counter;
    }

    if (counter == lenght)
    {
        throw std::invalid_argument("an object in the json file has invalid name -> missing clossing bracket");
    }
    else if (jsonSource[counter] == jsonSource[counter - 1])
    {
        throw std::invalid_argument("an object in the json file has no name -> name cannot be empty string");
    }

    isValid = true;
    return isValid;
}

bool JsonUtilities::isObjectValueValid(const std::string& jsonSource, std::size_t& counter, std::size_t lenght)
{
    
    bool isValueValid = false;
    char valueType;

    valueType = jsonSource[counter];

    ++counter;

    //checks if the value is missing

    if (valueType == ',' || valueType == '}' )
    {
        throw std::invalid_argument("an object value is missing");
    }

    //checks if the value is of type char
    else if (valueType == '\'')
    {
        try
        {
            if (isObjectValueValidChar(jsonSource, counter, lenght))
            {   
                isValueValid = true;
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw e;
        }   
    }

    //checks if the value is of type string
    else if (valueType == '"')
    {
        try
        {
            if(isObjectValueValidString(jsonSource, counter, lenght))
            {
                isValueValid = true;
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw e;
        }
            
            
    }

    //checks if the value is a digit
    else if (valueType == '-' || (valueType >= 48 && valueType <= 57))
    {
        try
        {
            if(isObjectValueValidDigit(jsonSource, counter, lenght, valueType))
            {
                isValueValid = true;
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw e;
        }
    }

    else if(valueType == '[')
    {
        isValueValid = isObjectValueValidArray(jsonSource, counter, lenght);
        
    }

    else if(valueType == '{')
    {
        std::string objectString;

        objectString = getObjectString(jsonSource, counter, lenght);

        isValueValid = isValid(objectString);
    }

    //checks if the value is bool or null
    else
    {   
        try
        {
            
            if(isObjectValueValidBoolOrNull(jsonSource, counter, lenght))
            {
                isValueValid = true;
            }
            else 
            {
                isValueValid = false;
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw e;
        }
    }

    return isValueValid;
}

bool JsonUtilities::isObjectValueValidChar(const std::string& jsonSource, std::size_t &counter, std::size_t lenght)
{
    if (lenght && jsonSource[counter] != '\'' && jsonSource[counter + 1] == '\'')
    {
        counter += 2;

        if (jsonSource[counter] != ',' && jsonSource[counter] !=']' && jsonSource[counter] != '}' && counter != lenght)
        {
            throw std::invalid_argument("an object in the json file has a missing separator or closing bracket");
        }

        return true;
    }
    else
    {
        throw std::invalid_argument("an object in the json file has and ivalid char value");

        return false;
    }
}

bool JsonUtilities::isObjectValueValidString(const std::string& jsonSource, std::size_t &counter, std::size_t lenght)
{
    while (jsonSource[counter] != '"' && counter < lenght)
    {
        ++counter;

    }

    if (counter == lenght)
    {
        throw std::invalid_argument("an object in the json file has an string without closing \"");
    }  

    ++counter;

    if (jsonSource[counter] != ',' && jsonSource[counter] != '}' && jsonSource[counter] != ']' && counter != lenght)
    {
        throw std::invalid_argument("somewhere is missing comma separator");
    }
    else
    {
        return true;
    }
}

bool JsonUtilities::isObjectValueValidDigit(const std::string& jsonSource, std::size_t &counter, std::size_t lenght, const char valueType)
{
    bool isValid = true;

    while (jsonSource[counter] >= 48 && jsonSource[counter] <=57 )
    {
        ++counter;
    }
    if (jsonSource[counter] == '.')
    {
        while (jsonSource[counter] >= 48 && jsonSource[counter] <=57 )
        {
            ++counter;
        }

        if (jsonSource[counter] != ',' && jsonSource[counter] !=']' && jsonSource[counter] != '}')
        {
            isValid = false;
        }
    }
    else
    {

        if (jsonSource[counter] != ',' && jsonSource[counter] !=']' && jsonSource[counter] != '}' && counter!=lenght)
        {
            isValid = false;
        }        
    }

    if (isValid)
    {
        return isValid;
    }
    else
    {
        throw std::invalid_argument("an object with digit value is invalid");
    }
}

bool JsonUtilities::isObjectValueValidArray(const std::string& jsonSource, std::size_t &counter, std::size_t lenght)
{
    bool isValid = true;
    char valueType;
    char separator = ',';

    while (separator != ']')
    {
        try
        {
            if (isObjectValueValid(jsonSource, counter, lenght))
            {
                separator = jsonSource[counter];
                ++counter;
            }
            else
            {
                isValid = false;
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw e;
        }
    }


    return isValid;
}

bool JsonUtilities::isObjectValueValidBoolOrNull(const std::string& jsonSource, std::size_t &counter, std::size_t lenght)
{
    --counter;
    if (jsonSource[counter] == 't' && jsonSource[counter+1] == 'r' && jsonSource[counter + 2] == 'u' && jsonSource[counter + 3] == 'e')
    {
        counter = counter + 4;
    
        if (jsonSource[counter] == ',' || jsonSource[counter] ==']' || jsonSource[counter] == '}')
        {
            return true;
        }
        else
        {
            throw std::invalid_argument("missing separator or closing bracket");
        }
    }
    else if (jsonSource[counter] == 'f' && jsonSource[counter+1] == 'a' && jsonSource[counter + 2] == 'l' && jsonSource[counter + 3] == 's' && jsonSource[counter + 4] == 'e')
    {
        counter = counter + 5;

        if (jsonSource[counter] == ',' || jsonSource[counter] ==']' || jsonSource[counter] == '}')
        {
            return true;
        }
        else
        {
            throw std::invalid_argument("missing separator or closing bracket");
        }
    }
    else if (jsonSource[counter] == 'n' && jsonSource[counter+1] == 'u' && jsonSource[counter + 2] == 'l' && jsonSource[counter + 3] == 'l')
    {
        counter = counter + 4;
        if (jsonSource[counter] == ',' || jsonSource[counter] ==']' || jsonSource[counter] == '}')
        {
            return true;
        }
        else
        {
            throw std::invalid_argument("missing separator or closing bracket");
        }
    }
    else
    {
        throw std::invalid_argument("an object as an invalid value");
    }
    
}

std::string JsonUtilities::getObjectString(const std::string &jsonSource, std::size_t &counter, std::size_t lenght)
{
    bool isInString = false;
    int openingBracketCount = 1;
    int closingBracketCount = 0;
    std::string objectString = "";

    objectString.push_back('{');

    while(jsonSource[counter] != '}' && openingBracketCount!=closingBracketCount)
    {

        if (jsonSource[counter] == '"' && !isInString)
        {
            objectString.push_back('"');
            ++counter;
            isInString = true;
        }

        if (jsonSource[counter] == '"' && isInString)
        {
            isInString = false;
        }

        if (jsonSource[counter] == '}' && isInString)
        {
            objectString.push_back('}');
            ++counter;
        }

        if (jsonSource[counter] == '{' && isInString)
        {
            objectString.push_back('{');
            ++counter;
        }

        if (jsonSource[counter] == '{' && !isInString)
        {
            openingBracketCount++;
        }

        if (jsonSource[counter] == '}' && !isInString)
        {
            closingBracketCount++;
        }

        objectString.push_back(jsonSource[counter]);

        ++counter;  
            
    }

    objectString.push_back('}');
    ++counter;
    return objectString;
}

void JsonUtilities::print(std::string jsonSource)
{
    trimFile(jsonSource);
    removeInsideSpaces(jsonSource);

    int counter = 0;
    bool isInString = false;
    bool isInArray = false;
    int lenght = jsonSource.size();
    int tabCount = 0;
    std::string tab = "    ";

    for (; counter < lenght; ++counter)
    {
        
        if (jsonSource.at(counter) == '}' && !isInString )
        {
            std::cout<<std::endl;
            --tabCount;

            for (size_t i = 0; i < tabCount; i++)
            {
                std::cout << tab;
            }  
        }

        std::cout << jsonSource.at(counter);

        if (jsonSource.at(counter) == '{' && !isInString)
        {
            ++tabCount;
            std::cout << std::endl;
            for (size_t i = 0; i < tabCount; i++)
            {
                std::cout << tab;
            }            
        }
        

        if (jsonSource.at(counter) == '[' && !isInString && !isInArray)
        {
            isInArray = true;
        }
        if (jsonSource.at(counter) == ']' && !isInString && !isInArray)
        {
            isInArray = false;
        }

        if(jsonSource.at(counter) == '"' && !isInString)
        {
            isInString = true;
        }
        if (jsonSource.at(counter) == '"' && isInString)
        {
            isInString = false;
        }

        if(jsonSource.at(counter) == ',' && !isInString && !isInArray)
        {
            std::cout << std::endl;
            for (size_t i = 0; i < tabCount; i++)
            {
                std::cout << tab;
            }     
        }    
    }
}

void JsonUtilities::remove(std::string objectPath)
{
    trimFile(objectPath);
    //removeInsideSpaces(objectPath);
    std::vector<std::string> parameters = getCommandArguments(objectPath);
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
    std::cout << '\n'
              << jsonFile << '\n';
    print(jsonFile);
}

void JsonUtilities::edit(std::string command)
{
    std::vector<std::string> commandArguments = getCommandArguments(command);
    std::string objectName = commandArguments.at(0);
    std::string objectValue = commandArguments.at(1);
    std::cout << "object name " << objectName << "\n object value: " << objectValue;
    std::size_t obejctValueCounter = 0;
    std::string currentObjectName = "";
    std::size_t jsonLenght = getJsonLenght();
    bool isObjectFounded = false;
    bool isInArray = false;
    bool isInString = false;
    bool isInObject = false;
    std::size_t counter = 1;
    std::cout << jsonFile << std::endl;
    if (!isObjectValueValid(objectValue, obejctValueCounter, objectValue.size()))
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
            jsonFile.replace(currentElementPosition, elementsCount, objectValue);

            break;
        }
        currentObjectName = "";
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
            ++counter;
        }
    }
    
    if (!isObjectFounded)
    {
        throw std::invalid_argument("there is not object with such name");
    }
    
    print(jsonFile);
}