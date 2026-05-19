#include "Commands.hpp"
#include <cstring>
#include <iostream>

void Commands::clearComs() {
    library = Library();
    isFileOpen = false;

    delete[] currentFilePath;
    currentFilePath = nullptr;
}

Commands::Commands() {
    currentUser = nullptr;
    currentFilePath = nullptr;
    isFileOpen = false;
}

Commands::~Commands() {
    delete[] currentFilePath;
    delete currentUser;
}

void Commands::run() {
    std::string command;

    std::cout << "System started\n";

    while(true) {
        std::cout << "Command: ";
        std::cin >> command;

        if(command == "login") {
            login();

        } 
        else if (command == "open") {
            char file[1024];
            std::cin >> file;
            open(file);

        }
        else if (command == "save") {
            save();
        }
        else if (command == "saveas") {
            char file[1024];
            std::cin >> file;
            saveAs(file);

        }
        else if (command == "help") {
            help();
        }
        else if (command == "exit") {
            exit();
            break;
        }
        else {
            std::cout << "Unknown command!\n";
        }
    }
}