#pragma once

#include "Library.hpp"
#include "UserCollection.hpp"
#include "User.hpp"

class Comamands {
private:
    Library library;
    UserCollection users;

    User* currentUser;

    bool isRunning;
    bool isFileOpen;

    char currentFile[1024];

    bool hasUserAcces() const;
    bool isAdmin() const;

        // GENERAL FILE COMMANDS
    void open(const char* file);
    void close();
    void save();
    void saveAs(const char* file);
    void help();

    void loing();
    void logout();

        // BOOOK COMMANDS
    void booksAll() const;
    void booksInfo(unsigned id);
    void booksFind(const char* option, const char* str);
    void booksSort(const char* option, const char* order);

    void booksAdd();
    void booksRemove();

    // USER COOMANDS
    void userAdd();
    void userRemove();

public:
    Comamands();

    void run();
};