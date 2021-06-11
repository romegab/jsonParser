#ifndef JSONCONTAINER_H
#define JSONCONTAINER_H
#include ".\jsonUtilities.hpp"
#include<iostream>
#include<fstream>

class JsonContainer
{
private:
    std::string filePath = "";
    std::string jsonFile = "{}";
    JsonUtilities utilites;
    bool isObjectExists(std::string name);
    std::vector<std::string> searchResult;
    std::string getJsonAsStrings();

public:
    void setJson(std::string jsonSource, std::string jsonSourcePath);
    void print();
    void printSearchResult();
    void edit(std::vector<std::string> commandArguments);
    void remove(std::vector<std::string> parameters);
    void move(std::vector<std::string> commandArguments);
    void create(std::vector<std::string> commandArguments);
    void search(std::string commandArgument);
    void save(std::string parameter);
    void saveas(std::string path, std::string saveMode);
    std::string getJson();
};

#endif