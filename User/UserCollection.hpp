#pragma once
#include "User.hpp"

class UserCollection {
private:
    User** users;

    unsigned size;
    unsigned capacity;

    void resize();
    void copyFrom(const UserCollection& other);
    void free();

public:
    UserCollection();
    UserCollection(const UserCollection& other);
    UserCollection& operator=(const UserCollection& other);
    ~UserCollection();

    void addUser(User* user);
    void removeUser(const char* username);

    User* login(const char* username, const char* password);

    const User* getUsers() const;
    unsigned getSize() const;
};