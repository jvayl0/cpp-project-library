#include "UserCollection.hpp"
#include "Admin.hpp"
#include "Client.hpp"
#include <cstring>
#include <iostream>

void UserCollection::resize() {
    capacity *= 2;

    User** newUsers = new User*[capacity];

    for(size_t i = 0; i < size; i++){
        newUsers[i] = users[i];
    }
    
    delete[] users;
    users = newUsers;
}

void UserCollection::copyFrom(const UserCollection& other) {
    size = other.size;
    capacity = other.capacity;

    users = new User*[capacity];

    for(size_t i = 0; i < size; i++){
        users[i] = other.users[i]->clone();
    }
}

void UserCollection::free() {
    for(size_t i = 0; i < size; i++){
        delete users[i];
    }
    delete[] users;

    users = nullptr;
    size = 0;
    capacity = 0;
}

UserCollection::UserCollection() {
    size = 0;
    capacity = 2;

    users = new User*[capacity];

    addUser(new Admin("admin","i<3c++"));
}

UserCollection::UserCollection(const UserCollection& other) {
    users = nullptr;
    size = 0;
    capacity = 0;

    copyFrom(other);
}

UserCollection& UserCollection::operator=(const UserCollection& other) {
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}

UserCollection::~UserCollection(){
    free();
}

void UserCollection::addUser(User* user) {
    for(size_t i = 0; i < size; i++){
        if(strcmp(users[i]->getUsername(), user->getUsername()) == 0){
            std::cout << "User already exists\n";

            delete user;
            return;
        }
    }

    if(size >= capacity){
        resize();
    }

    users[size++] = user;
}

void UserCollection::removeUser(const char* username) {
    for(size_t i = 0; i < size; i++){
        if(strcmp(users[i]->getUsername(), username) == 0){
            delete users[i];

            for(size_t j = i; j < size - 1; j++){
                users[j] = users[j + 1];
            }

            size--;
            return;
        }
    }
    std::cout << "User not found\n";
}

User* UserCollection::login(const char* username, const char* password) {
    for(size_t i = 0; i < size; i++){
        if(strcmp(users[i]->getUsername(), username) == 0 && users[i]->checkPassword(password)) {
            return users[i];
        }
    }
    return nullptr;
}

const User* const* UserCollection::getUsers() const {
    return users;
}

unsigned UserCollection::getSize() const {
    return size;
}