#pragma once
#include "Book.hpp"

class Library {
private:
    Book* books;
    unsigned size;
    unsigned capacity;

    void resize();
    void copyFrom(const Library& other);
    void free();

public:
    Library();
    Library(const Library& other);
    Library& operator=(const Library& other);
    ~Library();

    void addBook(const Book& book);
    void removeBook(unsigned id);

    Book* getBookById(unsigned id);

    const Book* getBooks() const;
    Book* getBook();
    unsigned getSize() const;
};