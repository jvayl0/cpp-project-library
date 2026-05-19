#include "Library.hpp"

void Library::resize() {
    capacity *= 2;

    Book* newArr = new Book[capacity];

    for(unsigned i = 0; i < size; i++){
        newArr[i] = books[i];
    }

    delete[] books;
    books = newArr;
}

void Library::copyFrom(const Library& other) {
    size = other.size;
    capacity = other.capacity;

    books = new Book[capacity];

    for(unsigned i = 0; i < size; i++){
        books[i] = other.books[i];
    }
}

void Library::free() {
    delete[] books;
    books = nullptr;
    size = 0;
    capacity = 0;
}

