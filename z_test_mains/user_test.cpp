#include <iostream>

#include "User/UserCollection.hpp"
#include "User/Admin.hpp"
#include "User/Client.hpp"

void printUsers(const UserCollection& users) {

    std::cout << "\n===== USERS =====\n";

    const User* const* allUsers =
        reinterpret_cast<const User* const*>(users.getUsers());

    for (unsigned i = 0; i < users.getSize(); i++) {

        std::cout << "Username: "
                  << allUsers[i]->getUsername();

        if (allUsers[i]->isAdmin()) {
            std::cout << " [ADMIN]";
        }
        else {
            std::cout << " [CLIENT]";
        }

        std::cout << "\n";
    }

    std::cout << "=================\n";
}

int main() {

    // ===================== CREATE =====================

    UserCollection users;

    printUsers(users);

    // ===================== ADD USERS =====================

    users.addUser(new Client("ivan", "1234"));
    users.addUser(new Client("pesho", "abcd"));
    users.addUser(new Admin("root", "rootpass"));

    std::cout << "\nAfter adding users:\n";

    printUsers(users);

    // ===================== DUPLICATE TEST =====================

    std::cout << "\nTrying duplicate user:\n";

    users.addUser(new Client("ivan", "test"));

    // ===================== LOGIN TEST =====================

    std::cout << "\n===== LOGIN TEST =====\n";

    User* logged = users.login("ivan", "1234");

    if (logged) {

        std::cout << "Login successful: "
                  << logged->getUsername()
                  << "\n";
    }
    else {

        std::cout << "Login failed.\n";
    }

    // wrong password
    logged = users.login("ivan", "wrong");

    if (!logged) {
        std::cout << "Wrong password test passed.\n";
    }

    // ===================== REMOVE TEST =====================

    std::cout << "\nRemoving user 'pesho'\n";

    users.removeUser("pesho");

    printUsers(users);

    // ===================== COPY TEST =====================

    std::cout << "\n===== COPY TEST =====\n";

    UserCollection copiedUsers = users;

    printUsers(copiedUsers);

    // ===================== ASSIGNMENT TEST =====================

    std::cout << "\n===== ASSIGNMENT TEST =====\n";

    UserCollection assignedUsers;

    assignedUsers = users;

    printUsers(assignedUsers);

    return 0;
}