#include "Admin.hpp"

Admin::Admin(const char* username, const char* password) : User(username, password) {}

bool Admin::isAdmin() const { return true; }