#pragma once

#include "User.hpp"

class Admin : public User {
public:
    Admin(const char* username, const char* password);
    bool isAdmin() const override;
};