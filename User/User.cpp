#include "User.hpp"
#include <cstring>

namespace {
    char* copyString(const char* string) {
        if(!string) return nullptr;

        char* result = new char[strlen(string) + 1];
        strcpy(result, string);
        return result;
    }
}

void User::copyFrom(const User& other) {
    username = copyString(other.username);
    password = copyString(other.password);
}

void User::free() {
    delete[] username;
    delete[] password;

    username = nullptr;
    password = nullptr;
}

User::User(const char* username, const char* password) {
    this->username = copyString(username);
    this->password = copyString(password);
}

User::User(const User& other) {
    copyFrom(other);
}

User& User::operator=(const User& other) {
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}

User::~User() {
    free();
}

const char* User::getUsername() const {
    return username;
}

const char* User::getPassword() const {
    return password;
}

bool User::checkPassword(const char* password) const {
    return strcmp(this->password, password) == 0;
}
