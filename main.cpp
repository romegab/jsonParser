/*#include <iostream>
#include "commandExecutor.hpp"

void printCommands()
{
    std::cout << "commands list:"
              << "\n"
              << "print -> prints the json file"
              << "\n"
              << "search <object name> - tells you if the object exists and save its value"
              << "\n"
              << "edit <object name> <new object value> -> set the object's value to the new one"
              << "\n"
              << "create <object name> <object value> -> create new object if the name isnt already used "
              << "\n"
              << "remove <object name> -> if object with this name exists it will be deleted from the file"
              << "\n"
              << "move <source object name> <destination object name> -> set the destination object's value equal to the source object's value"
              << "\n"
              << "save -> save the file at the same destination as the already opened file (overrides it)"
              << "\n"
              << "saveas <destination> -> save the file at this destination no matter if file already exists or not"
              << "\n"
              << "================================================================================================================================"
              << "\n";
}

int main(int argc, char* argv[])
{
    CommandExecutor commandExecutor;

    printCommands();

    if (argc == 2)
    {
        try
        {
            std::string filePath (argv[1]);
            std::string file = commandExecutor.readFile(filePath);
            commandExecutor.setJsonFile(file, filePath);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "the program will continiue with empty json file \n";
        }
    }
    else if(argc > 2)
    {
        std::cout << "the program can accept only one parameter - file path";
    }

    std::string commandInput;
    std::cout << "command: ";
    std::getline(std::cin, commandInput);

    while (commandInput != "end")
    {
        try
        {
            commandExecutor.executeCommmand(commandInput);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        std::cout << "command: ";
        std::getline(std::cin, commandInput);
    }
}*/