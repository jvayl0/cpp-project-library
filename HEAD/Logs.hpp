#pragma once

#include "Library.hpp"
#include "User.hpp"

class Logs {
private:
    Library library;
    User* currentUser;

    char* currentFilePath;
    bool isFileOpen;

    void freeState();

public:
    Logs();
    Logs(const Logs& other);
    Logs(Logs&& other) noexcept;
    Logs& operator=(Logs other);
    ~Logs();
};