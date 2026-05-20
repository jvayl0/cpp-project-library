#include "Commands.hpp"
#include <cstring>
#include <iostream>


void Commands::copyStringAt(char*& dest, const char* src) {
    if(!src){
        dest = nullptr;
        return;
    }

    dest = new char[strlen(src) + 1];
    strcpy(dest, src);
}

void Commands::free() {
    for(size_t i = 0; i < usersCount; i++) {
        delete[] users[i];
    }
    delete[] users;
    users = nullptr;

    delete[] currentFilePath;
    currentFilePath = nullptr;

    currentUser = nullptr;
    usersCount = 0;
    isFileOpen = false;
}

bool Commands::isLoggedIn() const {
    return currentUser != nullptr;
}

bool Commands::isAdmin() const {
    return currentUser && currentUser->isAdmin();
}

Commands::Commands() {
    currentUser = nullptr;
    currentFilePath = nullptr;
    isFileOpen = false;

    usersCount = 1;
    users = new User*[usersCount];

    users[0] = new Admin("admin", "i<3c++");
}

Commands::~Commands() {
    free();
}

void Commands::run() {
    std::string command;

    std::cout << "System started. Type (help) for commands\n";

    while(true) {
        std::cout << "# ";
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

void Commands::login() {

    if(currentUser != nullptr) {
        std::cout << "Already logged in\n";
        return;
    }

    char username[50];
    char password[50];

    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> password;

    for(size_t i = 0; i < usersCount; i++) {
        if(strcmp(users[i]->getUsername(), username) == 0 && users[i]->checkPassword(password)){

            currentUser = users[i];

            std::cout << "Welcome, " << currentUser->getUsername() << "!\n";

            return;
        }
    }
    
    std::cout << "Wrong username or password!\n";
}

void Commands::open(const char* file) {
    if(isFileOpen){
        std::cout << "File already opened\n";
        return;
    }

    delete[] currentFilePath;
    currentFilePath = new char[strlen(file) + 1];
    strcpy(currentFilePath, file);

    isFileOpen = true;

    std::cout << "Opened " << file << "\n";
}

void Commands::close(){
    if(!isFileOpen){
        std::cout << "No file opened\n";
        return;
    }

    delete[] currentFilePath;
    currentFilePath = nullptr;

    isFileOpen = false;

    std::cout << "Closed file\n";
}

void Commands::save() {
    if(!isFileOpen){
        std::cout << "No file opened\n";
        return;
    }

    std::cout << "Saved " << currentFilePath << std::endl;
}

void Commands::saveAs(const char* file) {


    std::cout << "Saved " << currentFilePath << std::endl;
}

void Commands::help() {
    std::cout << "Commands: \n" << "login\n" << "open\n" << "close\n" << "save\n"
              << "saveas\n" << "help\n" << "exit\n" ;
}

void Commands::exit(){
    std::cout << "Exiting System\n";
}