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

User::User(const char* username, const char* password) {
    this->username = copyString(username);
    this->password = copyString(password);
}

User::~User() {
    delete[] username;
    delete[] password;

    username = nullptr;
    password = nullptr;
}

const char* User::getUsername() const { return username; }

bool User::checkPassword(const char* pass) const {
    return strcmp(password, pass) == 0;
}