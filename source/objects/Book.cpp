#include "Book.hpp"
#include <cstring>

// HELPERS
namespace {
    template <typename T>
    void mySwap(T& first, T& second){
        T temp = first;
        first = second;
        second = temp;
    }
}

// PRIVATE METHODS

void Book::swap(Book& other) noexcept {
    mySwap(id, other.id);
    mySwap(author, other.author);
    mySwap(title, other.title);
    mySwap(genre, other.genre);
    mySwap(description, other.description);
    mySwap(year, other.year);
    mySwap(rating, other.rating);
    mySwap(keywords, other.keywords);
    mySwap(keywordsCount, other.keywordsCount);
}
