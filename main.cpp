#include "Commands/Commands.hpp"
#include <iostream>

int main() {

    std::cout << "Starting system...\n";

    Commands commands;

    commands.run();

    std::cout << "System stopped.\n";

    return 0;
}