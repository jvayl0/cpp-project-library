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

    // Един operator= за copy и move
    Library& operator=(Library other);

    ~Library();
};

