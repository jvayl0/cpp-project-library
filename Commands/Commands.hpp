#pragma once
#include "Library.hpp"
#include "User.hpp"
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

    bool isLoggedIn() const;
    bool isAdmin() const;

    void handleBooks();
    void handleUsers();

    void booksAll();
    void booksInfo();
    void booksFind();
    void booksSort();
    void booksView();
    void booksAdd();
    void booksRemove();

    void usersAdd();
    void usersRemove();

public:
    Commands();
    ~Commands();

    void run();

    void login();
    void logout();

    void open(const char* file);
    void close();

    void save();
    void saveAs(const char* file);
    
    void help();
    void exit();
};