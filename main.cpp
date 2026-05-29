#include "Commands/Commands.hpp"
#include <iostream>

int main() {

    std::cout << "Starting system...\n";

    Commands commands;

    commands.run();

    std::cout << "System stopped.\n";

    return 0;
}

// g++ -std=c++17 main.cpp \
Commands/*.cpp \
FileParsers/*.cpp \
User/*.cpp \
Library/*.cpp \
-I. \
-o app