#include "Commands.hpp"

#include "../FileParsers/FileParser.hpp"
#include "../FileParsers/UserFileParser.hpp"
#include "../Library/Library.hpp"
#include "../User/UserCollection.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

Commands::Commands() {
    currentUser = nullptr;

    isRunning = true;
    isFileOpen = false;
    isClosed = false;

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

// FILE COMMANDS

void Commands::open(const char* file) {
    if(isFileOpen){
        std::cout << "File already opened\n";
        return;
    }

    std::ifstream test(file);

    if(!test.is_open()) {
        library = Library();
        users = UserCollection();

        strcpy(currentFile, file);
        isFileOpen = true;

        std::cout << "File not found. Creating new empty file: " << file << std::endl;
        return;
    }
    test.close();

    bool ok = FileParser::loadFromFile(file, library);

    if(!ok) {
        std::cout << "Error loading file\n";
        exit();
    }

    UserFileParser::loadFromFile("users.txt", users);

    strcpy(currentFile, file);
    isFileOpen = true;

    std::cout << "Successfully opened " << file << std::endl;
}

void Commands::close() {
    if(!isFileOpen) {
        std::cout << "No file opened!\n";
        return;
    }

    library = Library();
    users = UserCollection();

    currentUser = nullptr;
    currentFile[0] = '\0';

    isFileOpen = false;
    isClosed = true;

    std::cout << "Successfully closed!\n";
}

void Commands::save() {
    if(!isFileOpen) {
        std::cout << "No file opened\n";
        return;
    }

    if(currentFile[0] == '\0') {
        std::cout << "No file selected!\n";
        return;
    }

    bool ok = FileParser::saveToFile(currentFile, library);

    if(!ok) {
        std::cout << "Error saving data\n";
        return;
    }

    UserFileParser::saveToFile("users.txt", users);

    std::cout << "Saved" << currentFile << std::endl;
}

void Commands::saveAs(const char* file) {
    if(!isFileOpen) {
        std::cout << "No file opened!\n";
        return;
    }

    if(!file || file[0] == '\0') {
        std::cout << "Invalid file name\n";
        return;
    }

    bool ok = FileParser::saveToFile(file, library);

    if(!ok) {
        std::cout << "Error saving file\n";
        return;
    }

    UserFileParser::saveToFile("users.txt", users);

    std::cout << "Saved as " << file << std::endl;
}

void Commands::help() {
    std::cout << "The following commands are supported:\n\n"

        << "FILE OPERATIONS:\n"
        << "open <file>     - opens a file\n"
        << "close           - closes current file\n"
        << "save            - saves current file\n"
        << "saveas <file>   - saves as new file\n\n"

        << "AUTH:\n"
        << "login           - logs into system\n"
        << "logout          - logs out user\n\n"

        << "BOOKS (CLIENT):\n"
        << "books all       - lists all books\n"
        << "books info <id> - shows book details\n"
        << "books find ...  - searches books\n"
        << "books sort ...  - sorts books\n\n"

        << "BOOKS (ADMIN ONLY):\n"
        << "books add       - adds new book\n"
        << "books remove    - removes book\n\n"

        << "USERS (ADMIN ONLY):\n"
        << "users add       - adds new user\n"
        << "users remove    - removes user\n\n"

        << "SYSTEM:\n"
        << "help            - shows this help\n"
        << "exit            - exits program\n";
}

void Commands::exit() {
    isRunning = false;

    std::cout << "Exiting the program\n";
}

// LOGIN AND LOGOUT - AUTH

void Commands::login() {
    if(currentUser) {
        std::cout << "Already logged in\n";
        return;
    }

    char username[50];
    char password[50];

    std::cout << "Username: ";
    std::cin.getline(username, 50);

    std::cout << "Password: ";
    std::cin.getline(password, 50);

    currentUser = users.login(username, password);

    if(currentUser){
        std::cout << "Welcome, " << currentUser->getUsername() << std::endl;
    }else {
        std::cout << "Wrong username or password!\n";
    }
}

void Commands::logout() {
    if(!currentUser){
        std::cout << "No user is logged in\n";
        return;
    }

    std::cout << "Goodbye, " << currentUser->getUsername() << std::endl;

    currentUser = nullptr;
}


// EXECUTE COMMAND

void Commands::executeCommand(char* line) {

    if (isClosed) {
        if (strncmp(line, "open ", 5) == 0) {
            open(line + 5);
            return;
        }
        std::cout
            << "File is closed. Only 'open' is allowed.\n";
        return;
    }

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
        exit();
    }
    else {
        std::cout << "Unknown command!\n";
    }
}

void Commands::booksAdd() {
    std::cout << "booksAdd not implemented yet\n";
}

void Commands::booksRemove() {
    std::cout << "booksRemove not implemented yet\n";
}

void Commands::userAdd() {
    std::cout << "userAdd not implemented yet\n";
}

void Commands::userRemove() {
    std::cout << "userRemove not implemented yet\n";
}

void Commands::booksFind(const char*, const char*) {
    std::cout << "booksFind not implemented yet\n";
}

void Commands::booksInfo(unsigned) {
    std::cout << "booksInfo not implemented yet\n";
}

void Commands::booksSort(const char*, const char*) {
    std::cout << "booksSort not implemented yet\n";
}

void Commands::booksAll() const {
    std::cout << "booksAll not implemented yet\n";
}