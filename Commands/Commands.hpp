#pragma once
#include "Library.hpp"
#include "Admin.hpp"
#include "Client.hpp"

class Commands {
private:
    Library library;
    User** users;
    unsigned usersCount;

    User* currentUser;

    char* currentFilePath;
    bool isFileOpen;

    void copyStringAt(char*& dest, const char* src);
    void free();

public:
    Commands();
    ~Commands();

    void run();

    void login();

    void open(const char* file);
    void close();
    void save();
    void saveAs(const char* file);
    void help();
    void exit();

    bool isLoggedIn() const;
    bool hasFileOpen() const;
};