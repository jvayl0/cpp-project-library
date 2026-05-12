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

    char* copyString(const char* str) {
        if(!str) return nullptr;

        char* result = new char[strlen(str) + 1];
        strcpy(result, str);

        return result;
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

void Book::free(){
    delete[] author;
    delete[] title;
    delete[] genre;
    delete[] description;
    
    for(size_t i = 0; i < keywordsCount; i++){
        delete[] keywords[i];
    }
    delete[] keywords;

    author = nullptr;
    title = nullptr;
    genre = nullptr;
    description = nullptr;
    keywords = nullptr;
    keywordsCount = 0;
}

// CONSTRUCTORS AND DESTRUCTOR
Book::Book() : id(0), author(nullptr), title(nullptr), genre(nullptr), description(nullptr),
               year(0), rating(0.0), keywords(nullptr), keywordsCount(0) {}

Book::Book(unsigned id, const char* author, const char* title, const char* genre,
           const char* description, unsigned year, double rating, 
           char** keywords, int keywordsCount) :
           id(id), year(year), rating(rating), keywordsCount(keywordsCount) {

           
}

