#include "Client.hpp"

Client::Client(const char* username, const char* password) : User(username, password) {}

bool Client::isAdmin() const { return false; }