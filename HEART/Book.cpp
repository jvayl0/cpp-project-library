#include "HEAD/Book.hpp"
#include <cstring>

// HELPERS
namespace {
    char* copyString(const char* str) {
        if(!str) return nullptr;

        char* result = new char[strlen(str) + 1];
        strcpy(result, str);

        return result;
    }
}

// PRIVATE METHODS
void Book::copyFrom(const Book& other) {
    id = other.id;
    year = other.year;
    rating = other.rating;
    keywordsCount = other.keywordsCount;

    author = copyString(other.author);
    title = copyString(other.title);
    genre = copyString(other.genre);
    description = copyString(other.description);

    if(keywordsCount > 0){
        keywords = new char*[keywordsCount];
        for(size_t i = 0; i < keywordsCount; i++){
            keywords[i] = copyString(other.keywords[i]);
        }
    } else {
        keywords = nullptr;
    }
}

void Book::free(){
    delete[] author;
    delete[] title;
    delete[] genre;
    delete[] description;
    
    if(keywords){
    for(size_t i = 0; i < keywordsCount; i++){
        delete[] keywords[i];
    }
    delete[] keywords;
    }

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

           this->author = copyString(author);
           this->title = copyString(title);
           this->genre = copyString(genre);
           this->description = copyString(description);

           if(keywordsCount > 0){
                this->keywords = new char*[keywordsCount];
                for(size_t i = 0; i < keywordsCount; i++){
                    this->keywords[i] = copyString(keywords[i]);
                }
        }   else {
                this->keywords = nullptr;
           }
}

Book::Book(const Book& other){
    copyFrom(other);
}

Book& Book::operator=(const Book& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}

Book::~Book() {
    free();
}

// GETTERS
unsigned Book::getId() const { return id; }
const char* Book::getAuthor() const { return author ;}
const char* Book::getTitle() const { return title; }
const char* Book::getGenre() const { return genre; }
const char* Book::getDescription() const { return description; }
unsigned Book::getYear() const { return year; }
double Book::getRating() const { return rating; }
const char* const* Book::getKeywords() const { return keywords; }
int Book::getKeywordsCount() const {return keywordsCount; }

// SETTERS
void Book::setId(unsigned id) { this->id = id; }
void Book::setAuthor(const char* author) {
    delete[] this->author;
    this->author = copyString(author);
}
void Book::setTitle(const char* title) {
    delete[] this->title;
    this->title = copyString(title);
}
void Book::setGenre(const char* genre) {
    delete[] this->genre;
    this->genre = copyString(genre);
}
void Book::setDescription(const char* description) {
    delete[] this->description;
    this->description = copyString(description);
}
void Book::setYear(unsigned year) { this->year = year; }
void Book::setRating(double rating) { this->rating = rating; }

void Book::setKeywords(char** keywords, int keywordsCount) {
    for(size_t i = 0; i < this->keywordsCount; i++){
        delete[] this->keywords[i];
    }
    delete[] this->keywords;

    this->keywordsCount = keywordsCount;
    if(keywordsCount > 0){
        this->keywords = new char*[keywordsCount];
        for(size_t i = 0; i < keywordsCount; i++){
            this->keywords[i] = copyString(keywords[i]);
        }
    } else {
        this->keywords = nullptr;
    }
}