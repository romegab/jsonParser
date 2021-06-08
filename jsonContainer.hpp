#ifndef JSONCONTAINER_H
#define JSONCONTAINER_H
#include ".\jsonUtilities.hpp"
#include<iostream>

class JsonContainer
{
private:
    std::string jsonFile;
    JsonUtilities utilites;
    bool isObjectExists(std::string name);

public:
    void setJson(std::string jsonSource);
    void print();
    void edit(std::vector<std::string> commandArguments);
    void remove(std::vector<std::string> parameters);
    void move(std::vector<std::string> commandArguments);
    void create(std::vector<std::string> commandArguments);
};

#endif