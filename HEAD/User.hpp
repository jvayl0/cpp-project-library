#pragma once

class User {
protected:
    char* username;
    char* password;

public:
    User(const char* username, const char* password);
    virtual ~User();

    virtual bool isAdmin() const = 0;
    const char* getUsername() const;
};