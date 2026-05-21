#pragma once
#include "../User/UserCollection.hpp"

class UserFileParser {
public:
    static bool loadFromFile(const char* file, UserCollection& users);
    static bool saveToFile(const char* file, UserCollection& users);
};