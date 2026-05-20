#pragma once

class User {
protected:
    char* username;
    char* password;

    void copyFrom(const User& other);
    void free();

public:
    User(const char* username, const char* password);
    User(const User& other);
    User& operator=(const User& other);
    virtual ~User();

    const char* getUsername() const;
    bool checkPassword(const char* password) const;

    virtual bool isAdmin() const = 0;
    virtual User* clone() const = 0;
};