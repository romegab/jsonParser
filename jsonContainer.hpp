#ifndef JSONCONTAINER_H
#define JSONCONTAINER_H
#include ".\jsonUtilities.hpp"
#include<iostream>

class JsonContainer
{
private:
    std::string jsonFile;
    JsonUtilities utilites;
    
public:
    void setJson(std::string jsonSource);
    void print();
    void edit(std::vector<std::string> commandArguments);
    void remove(std::vector<std::string> parameters);
    void move(std::vector<std::string> commandArguments);
};

#endif