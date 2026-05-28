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

Library::Library() {
    size = 0;
    capacity = 2;
    books = new Book[capacity];
}

Library::Library(const Library& other) {
    copyFrom(other);
}

Library& Library::operator=(const Library& other) {
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}

Library::~Library() {
    free();
}

void Library::addBook(const Book& book) {
    if(size >= capacity){
        resize();
    }

    books[size++] = book;
}

void Library::removeBook(unsigned id) {
    for(unsigned i = 0; i < size; i++){

        if(books[i].getId() == id) {
            for(unsigned j = i; j < size - 1; j++){
                books[j] = books[j + 1];
            }
            size--;
            return;
        }
    }
}

Book* Library::getBookById(unsigned id) {
    for(unsigned i = 0; i < size; i++){
        if(books[i].getId() == id){
            return &books[i];
        }
    }
    return nullptr;
}

const Book* Library::getBooks() const {
    return books;
}
Book* Library::getBook(){
    return books;
}

unsigned Library::getSize() const {
    return size;
}