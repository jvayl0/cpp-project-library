#pragma once

#include "User.hpp"

class Client : public User {
public:
    Client(const char* username, const char* password);
    Client(const Client& other);
    Client(Client&& other) noexcept;
    Client& operator=(Client other);

    bool isAdmin() const override;
    User* clone() const override;
};