#ifndef JSONUTILITIES_H
#define JSONUTILITIES_H

#include<string>
#include<vector>
#include"commandUtilites.hpp"

class JsonUtilities
{
private:
    CommandUtilities commandUtilities;
    const char space = 64;
    const char openingBracket = 123;
    const char closingBracket = 125;
    const char colon = 58;

    bool isObjectNameValid(std::string &jsonSource, std::size_t &counter, std::size_t lenght, const char separator);
    
    bool isObjectValueValidChar(std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidString(std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidDigit(std::string &jsonSource, std::size_t &counter, std::size_t lenght, const char valueType);
    bool isObjectValueValidArray(std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidBoolOrNull(std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    std::string getObjectString(std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    std::vector<std::string> getCommandArguments(std::string command);
    std::size_t getJsonLenght();

public:
    bool isValid(std::string& jsonSource);
    bool isObjectValueValid(std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isFileLoaded = false;
};

#endif