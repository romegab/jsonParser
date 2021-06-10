#define CATCH_CONFIG_MAIN
#include ".\..\catch2.hpp"
#include ".\..\..\jsonContainer.hpp"

TEST_CASE("json container")
{
    JsonContainer jsonContainer;
    std::string json = "{\"int\":12345,\"char\":'c',\"string\":\"text\",\"boolTrue\":true,\"boolFalse\":false,\"null\":null,\"array\":[1234,'c',\"lorem\"],\"object\":{\"name\":\"Ivan Stoilov\",\"age\":20}}";
    std::vector<std::string> commandArguments;

    SECTION("testing edit function with invalid object name")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("foo");
        commandArguments.push_back("\"boo\"");
        REQUIRE_THROWS_AS(jsonContainer.edit(commandArguments), std::invalid_argument);
    }  
    SECTION("testing edit function with invalid object value")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("int");
        commandArguments.push_back("12c");
        REQUIRE_THROWS_AS(jsonContainer.edit(commandArguments), std::invalid_argument);
    }   
    SECTION("testing edit function with valid object name and value")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("int");
        commandArguments.push_back("12");
        jsonContainer.edit(commandArguments);
        REQUIRE(jsonContainer.getJson() == "{\"int\":12,\"char\":'c',\"string\":\"text\",\"boolTrue\":true,\"boolFalse\":false,\"null\":null,\"array\":[1234,'c',\"lorem\"],\"object\":{\"name\":\"Ivan Stoilov\",\"age\":20}}");
        commandArguments.clear();
    }   
    SECTION("testing remove with valid object name")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("int");
        jsonContainer.remove(commandArguments);
        REQUIRE(jsonContainer.getJson() == "{\"char\":'c',\"string\":\"text\",\"boolTrue\":true,\"boolFalse\":false,\"null\":null,\"array\":[1234,'c',\"lorem\"],\"object\":{\"name\":\"Ivan Stoilov\",\"age\":20}}");
        commandArguments.clear();
    }    
    SECTION("testing move with two valid names")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("int");
        commandArguments.push_back("string");
        jsonContainer.move(commandArguments);
        REQUIRE(jsonContainer.getJson() == "{\"int\":12345,\"char\":'c',\"string\":12345,\"boolTrue\":true,\"boolFalse\":false,\"null\":null,\"array\":[1234,'c',\"lorem\"],\"object\":{\"name\":\"Ivan Stoilov\",\"age\":20}}");
        commandArguments.clear();
    }     
      
    SECTION("testing create with valid name and value")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("foo");
        commandArguments.push_back("\"boo\"");
        jsonContainer.create(commandArguments);
        REQUIRE(jsonContainer.getJson() == "{\"int\":12345,\"char\":'c',\"string\":\"text\",\"boolTrue\":true,\"boolFalse\":false,\"null\":null,\"array\":[1234,'c',\"lorem\"],\"object\":{\"name\":\"Ivan Stoilov\",\"age\":20},\"foo\":\"boo\"}");
        commandArguments.clear();
    }
    SECTION("testing create with valid name but invalid value")
    {
        jsonContainer.setJson(json, "");
        commandArguments.push_back("foo");
        commandArguments.push_back("12c");
        REQUIRE_THROWS_AS(jsonContainer.create(commandArguments), std::invalid_argument);
        commandArguments.clear();
    }
}
    