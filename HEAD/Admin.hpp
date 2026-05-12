#pragma once

#include "User.hpp"

class Admin : public User {
public:
    Admin(const char* username, const char* password);
    Admin(const Admin& other);
    Admin(Admin&& other) noexcept;
    Admin& operator=(Admin other);

    bool isAdmin() const override;
    User* clone() const override;
};