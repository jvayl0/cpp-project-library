#pragma once

#include "User.hpp"

class Client : public User {
public:
    Client(const char* username, const char* password);
    bool isAdmin() const override;
};