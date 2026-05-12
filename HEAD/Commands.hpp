#pragma once
#include "Library.hpp"
#include "User.hpp"

class Commands {
private:
    Library library;
    User* currentUser;

    char* currentFilePath;
    bool isFileOpen;

    void clearComs();

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
};