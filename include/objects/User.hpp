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
    User(User&& other) noexcept;
    virtual ~User();

    // getters
    const char* getUsername() const;
    const char* getPassword() const;

    // setters
    void setUsername(const char* username);
    void setPassword(const char* password);

    virtual bool isAdmin() const = 0;
    virtual User* clone() const = 0;
};