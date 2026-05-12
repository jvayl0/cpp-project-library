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
    Logs();
    Logs(const Logs& other);
    Logs(Logs&& other) noexcept;
    Logs& operator=(Logs other);
    ~Logs();
};