#include "FileParser.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

// id|author|title|genre|description|year|rating|keyword1 keyword2 keyword3

bool FileParser::loadFromFile(const char* fileP, Library& library) {
    std::ifstream file(fileP);

    if(!file.is_open()){
        std::cout << "File not found. Creating new empty library\n";
        return false;
    }

    char buffer[1024];

    while(file.getline(buffer, 1024)) {
        // ,,,,,
    }

    file.close();
    return true;
}

bool FileParser::saveToFile(const char* fileP, Library& library) {
    std::ofstream file(fileP);

    if(!file.is_open()){
        std::cout << "File not opened for writing\n";
        return false;
    }

    const Book* books = library.getBooks();
    unsigned size = library.getSize();

    for(size_t i = 0; i < size; i++){
        file << books[i].getId() << "|"
             << books[i].getAuthor() << "|"
             << books[i].getTitle() << "|"
             << books[i].getGenre() << "|"
             << books[i].getDescription() << "|"
             << books[i].getYear() << "|"
             << books[i].getRating();
        file << std::endl;
    }

    file.close();
    return true;
}