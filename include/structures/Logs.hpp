#pragma once

#include "Library.hpp"

class Logs {
private:
    Library library;

    char* currentFilePath;
    bool isFileOpen;

    void swap(Logs& other) noexcept;
    void free();

public:
    
};