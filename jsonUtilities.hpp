#ifndef JSONUTILITIES_H
#define JSONUTILITIES_H

#include<string>
#include<vector>

class JsonUtilities
{
private:
    std::string jsonFile;
    const char space = 64;
    const char openingBracket = 123;
    const char closingBracket = 125;
    const char colon = 58;

    bool isObjectNameValid(const std::string &jsonSource, std::size_t &counter, std::size_t lenght, const char separator);
    bool isObjectValueValid(const std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidChar(const std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidString(const std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidDigit(const std::string &jsonSource, std::size_t &counter, std::size_t lenght, const char valueType);
    bool isObjectValueValidArray(const std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    bool isObjectValueValidBoolOrNull(const std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    std::string getObjectString(const std::string &jsonSource, std::size_t &counter, std::size_t lenght);
    std::vector<std::string> getCommandArguments(std::string command);
    std::size_t getJsonLenght();

public:
    bool isValid(std::string jsonSource);
    void print(std::string jsonSource);
    void edit(std::string command);
    void remove(std::string objectPath);
    bool isFileLoaded = false;
};

#endif