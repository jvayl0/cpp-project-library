#include "Logs.hpp"
#include <iostream>
#include <cstring>

Logs::Logs() {
    currentUser = nullptr;
    currentFilePath = nullptr;
    isFileOpen = false;
}

Logs::~Logs() {
    delete[] currentFilePath;
    delete currentUser;
}

Logs::freeState() {
    library = Library();
    isFileOpen = false;

    delete[] currentFilePath;
    currentFilePath = nullptr;
}