#include "Commands.hpp"

#include "FileParser.hpp"
#include "UserFileParser.hpp"

#include "Admin.hpp"
#include "Client.hpp"

#include <iostream>
#include <cstring>

Commands::Commands() {
    currentUser = nullptr;

    isRunning = true;
    isFileOpen = false;

    currentFile[0] = '\0';
}

// HELPERS

bool Commands::hasUserAcces() const {
    return currentUser != nullptr;
}

bool Commands::isAdmin() const {
    return currentUser && currentUser->isAdmin();
}

// RUN

void Commands::run() {
    char line[1024];
    std::cout << "System started!\n";

    while(isRunning) {
        std::cout << "> ";

        std::cin.getline(line, 1024);
        executeCommand(line);
    }
}

// EXECUTE COMMAND

void Commands::executeCommand(char* line) {

    if(strncmp(line, "open ", 5) == 0) {
        open(line + 5);
    }
    else if(strcmp(line, "close") == 0) {
        close();
    }
    else if(strcmp(line, "save") == 0) {
        save();
    }
    else if(strncmp(line, "saveas ", 7) == 0) {
        saveAs(line + 7);
    }
    else if(strcmp(line, "login") == 0) {
        login();
    }
    else if(strcmp(line, "logout") == 0) {
        logout();
    }
    else if(strcmp(line, "books all") == 0) {
        booksAll();
    }
    else if(strncmp(line, "books info ", 11) == 0) {
        unsigned id = atoi(line + 11);
        booksInfo(id);
    }
    else if(strncmp(line, "books find ", 11) == 0) {
        char* ptr = line + 11;
        char* option = strtok(ptr, " ");
        char* str = strtok(nullptr, "");

        if(option && str) {
            while(*str == ' '){
                str++;
            }
            booksFind(option, str);
        }
    }
    else if(strncmp(line, "books sort ", 11) == 0) {
        char* ptr = line + 11;
        char* option = strtok(ptr, " ");
        char* order = strtok(nullptr, " ");
        
        if(!order){
            order = (char*)"asc";
        }

        if(option){
            booksSort(option, order);
        }
    }
    else if(strcmp(line, "books add") == 0) {
        booksAdd();
    }
    else if(strcmp(line, "books remove") == 0) {
        booksRemove();
    }
    else if(strcmp(line, "user add") == 0) {
        userAdd();
    }
    else if(strcmp(line, "user remove") == 0) {
        userRemove();
    }
    else if(strcmp(line, "help") == 0) {
        help();
    }
    else if(strcmp(line, "exit") == 0){
        isRunning = false;
        std::cout << "Exiting System!\n";
    }
    else {
        std::cout << "Unknown command!\n";
    }
}