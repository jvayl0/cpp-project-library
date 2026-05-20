#include "FileParser.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

// id|author|title|genre|description|year|rating|kw1 kw2

bool FileParser::loadFromFile(const char* file, Library& library) {

    std::ifstream in(file);

    if(!in.is_open()){
        std::cout << "Books file not found!\n";
        return false;
    }

    char buffer[2048];

    while(in.getline(buffer, 2048)) {
        if(strlen(buffer) == 0) continue;

        char* token = strtok(buffer, "|");

        unsigned id = atoi(token);
        char* author = strtok(nullptr, "|");
        char* title = strtok(nullptr, "|");
        char* genre = strtok(nullptr, "|");
        char* desc = strtok(nullptr, "|");
        unsigned year = atoi(strtok(nullptr, "|"));
        double rating = atof(strtok(nullptr, "|"));
        char* kwStr = strtok(nullptr, "|");

        char* keywords[50];
        int count = 0;

        if (kwStr) {

            char* kw = strtok(kwStr, " ");

            while (kw) {
                keywords[count++] = kw;
                kw = strtok(nullptr, " ");
            }
        }

        Book b(
            id,
            author,
            title,
            genre,
            desc,
            year,
            rating,
            (char**)keywords,
            count
        );

        library.addBook(b);
    }

    in.close();
    return true;
}

bool FileParser::saveToFile(const char* file, Library& library) {

    std::ofstream out(file);

    if(!out.is_open()){
        std::cout << "Cannot write books in file\n";
        return false;
    }

    const Book* books = library.getBooks();
    unsigned size = library.getSize();

    for(size_t i = 0; i < size; i++){

        out << books[i].getId() << "|"
            << books[i].getAuthor() << "|"
            << books[i].getTitle() << "|"
            << books[i].getGenre() << "|"
            << books[i].getDescription() << "|"
            << books[i].getYear() << "|"
            << books[i].getRating() << "|";

        const char* const* kw = books[i].getKeywords();
        int kwCount = books[i].getKeywordsCount();

        for (int j = 0; j < kwCount; j++) {
            out << kw[j];
            if (j < kwCount - 1) out << " ";
        }

        out << "\n";
    }

    out.close();
    return true;
}
