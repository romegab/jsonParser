#define CATCH_CONFIG_MAIN
#include ".\..\catch2.hpp"
#include ".\..\..\jsonUtilities.hpp"

TEST_CASE("json utilities")
{
    JsonUtilities jsonUtilities;
    std::string json = "";
    std::string objectValue = "";
    std::size_t counter = 0;

    SECTION("testing isValid with empty string")
    {
        bool result;
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    }

    SECTION("testing isValid with invalid object name ")
    {
        bool result;
        json = "{error}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    }  

    SECTION("testing isValid with valid int object value ")
    {
        bool result;
        json = "{\"int\":123}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid string object value ")
    {
        bool result;
        json = "{\"string\":\"string\"}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid char object value ")
    {
        bool result;
        json = "{\"char\":'a'}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid null object value ")
    {
        bool result;
        json = "{\"null\":null}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid bool object value ")
    {
        bool result;
        json = "{\"bool\":false}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid bool object value ")
    {
        bool result;
        json = "{\"bool\":true}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid array object value ")
    {
        bool result;
        json = "{\"arrat\":[123, 456, 789]}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    } 

    SECTION("testing isValid with valid object object value ")
    {
        bool result;
        json = "{\"object\":{\"int\": 1234}}";
        result = jsonUtilities.isValid(json);
        REQUIRE(result == true);
    }

     SECTION("testing isValid with invalid int object value ")
    {
        bool result;
        json = "{\"int\":1c23}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid string object value ")
    {
        bool result;
        json = "{\"string\":string\"}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid char object value ")
    {
        bool result;
        json = "{\"char\":'aa'}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid null object value ")
    {
        bool result;
        json = "{\"null\":nll}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid bool object value ")
    {
        bool result;
        json = "{\"bool\":flse}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid bool object value ")
    {
        bool result;
        json = "{\"bool\":tue}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid array object value ")
    {
        bool result;
        json = "{\"arrat\":[123, '12', 789]}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isValid with invalid object object value ")
    {
        bool result;
        json = "{\"object\":{\"char\": 'aa'}}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isValid(json), std::invalid_argument);
    } 

    SECTION("testing isObjectValueValid with invalid object value int")
    {
        bool result;
        objectValue = "12s4";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

    SECTION("testing isObjectValueValid with invalid object value string")
    {
        bool result;
        objectValue = "\"124";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

    SECTION("testing isObjectValueValid with invalid object value char")
    {
        bool result;
        objectValue = "'as'";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

    SECTION("testing isObjectValueValid with invalid object value bool")
    {
        bool result;
        objectValue = "fase";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

    SECTION("testing isObjectValueValid with invalid object value null")
    {
        bool result;
        objectValue = "nul";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

    SECTION("testing isObjectValueValid with invalid object value array")
    {
        bool result;
        objectValue = "[124, 124s]";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

    SECTION("testing isObjectValueValid with invalid object value object")
    {
        bool result;
        objectValue = "{\"name\": 124s}";
        REQUIRE_THROWS_AS(result = jsonUtilities.isObjectValueValid(json, counter, objectValue.size()), std::invalid_argument);
        counter = 0;
    }

       
}
    