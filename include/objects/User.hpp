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

    virtual bool isAdmin() const = 0;

    const char* getUsername() const;
    const char* getPassword() const;

    // deep copy
    virtual User* clone() const = 0;
    virtual ~User();
};