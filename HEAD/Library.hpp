#pragma once

#include "Book.hpp"

class Library {
private:
    Book* books;

    unsigned size;
    unsigned capacity;

    void resize();
    void swap(Library& other) noexcept;
    void free();

public:
    Library();
    Library(const Library& other);
    Library(Library&& other) noexcept;
    Library& operator=(Library other);
    ~Library();

    const Book* getBooks() const;
    unsigned getSize() const;
    unsigned getCapacity() const;
};

