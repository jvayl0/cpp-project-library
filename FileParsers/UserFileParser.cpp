#include "UserFileParser.hpp"
#include "Admin.hpp"
#include "Client.hpp"

#include <fstream>
#include <iostream>
#include <cstring>

// type|username|password

bool UserFileParser::loadFromFile(const char* file, UserCollection& users) {

    std::ifstream in(file);

    if(!in.is_open()){
        std::cout << "Users file not found!\n";
        return false;
    }

    char buffer[1024];

    while(in.getline(buffer, 1024)){
        char* type = strtok(buffer, "|");
        char* user = strtok(nullptr, "|");
        char* pass = strtok(nullptr, "|");

        if(!type || !user || !pass) continue;

        if(strcmp(type, "admin") == 0){
            users.addUser(new Admin(user, pass));

        }else {
            users.addUser(new Client(user, pass));
        }
    }

    in.close();
    return true;
}

bool UserFileParser::saveToFile(const char* file, UserCollection& users) {

    std::ofstream out(file);

    if(!out.is_open()){
        std::cout << "Cannot write in users file!\n";
        return false;
    }

    const User* const* arr = users.getUsers();

    for(size_t i = 0; i < users.getSize(); i++){
        if(arr[i]->isAdmin()){
            out << "admin|";
        } else {
            out << "client|";
        }
        out << arr[i]->getUsername() << "|" << arr[i]->getPassword() << std::endl;
    }

    out.close();
    return true;
}