#define CATCH_CONFIG_MAIN
#include ".\..\catch2.hpp"
#include ".\..\..\commandUtilites.hpp"

TEST_CASE("command utilities")
{
    CommandUtilities commandUtilities;
    std::string command;

    SECTION("testing trim command with command without starting and ending spaces")
    {
        command = "command";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command");
    }

    SECTION("testing trim command with command without starting but with ending spaces")
    {
        command = "command            ";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command");
    }

    SECTION("testing trim command with command with starting but without ending spaces")
    {
        command = "         command";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command");
    }

    SECTION("testing trim command with command with starting and ending spaces")
    {
        command = "        command         ";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command");
    }

    SECTION("testing trim mutli parameter command with command with starting and ending spaces")
    {
        command = "    command parameter    ";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command parameter");
    }

    SECTION("testing trim mutli parameter command with command wothout starting but with ending spaces")
    {
        command = "command parameter    ";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command parameter");
    }

    SECTION("testing trim mutli parameter command with command with starting but without ending spaces")
    {
        command = "    command parameter";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command parameter");
    }

    SECTION("testing trim mutli parameter command with command without starting and ending spaces")
    {
        command = "command parameter";
        commandUtilities.trimCommand(command);

        REQUIRE(command == "command parameter");
    }

    SECTION("testing removeInsideSpaces miltu parameter command with one space separator")
    {
        command = "command parameter";
        commandUtilities.removeInsideSpaces(command);

        REQUIRE(command == "commandparameter");
    }

    SECTION("testing removeInsideSpaces miltu parameter command with multi space separator")
    {
        command = "command               parameter";
        commandUtilities.removeInsideSpaces(command);

        REQUIRE(command == "commandparameter");
    }

    SECTION("testing getCommandArguments with command without arguments")
    {
        command = "command";
        std::vector<std::string> arguments = commandUtilities.getCommandArguments(command);

        REQUIRE(arguments.size() == 0);
    }

    SECTION("testing getCommandArguments with command with one argument")
    {
        command = "command 124";
        std::vector<std::string> arguments = commandUtilities.getCommandArguments(command);

        REQUIRE(arguments.size() ==1);
        REQUIRE(arguments.at(0) == "124");
    }

    SECTION("testing getCommandArguments with command with two arguments")
    {
        command = "command 1234 456";
        std::vector<std::string> arguments = commandUtilities.getCommandArguments(command);

        REQUIRE(arguments.size() == 2);
        REQUIRE(arguments.at(0) == "1234");
        REQUIRE(arguments.at(1) == "456");
    }
}
    