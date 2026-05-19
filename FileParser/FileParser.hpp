#pragma once
#include "Library.hpp"

class FileParser {
public:
    static bool loadFromFile(const char* fileP, Library& library);
    static bool saveToFile(const char* fileP, Library& library);
};