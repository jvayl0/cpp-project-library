#pragma once

class Book {
private:
    unsigned id;

    char* author;
    char* title;
    char* genre;
    char* description;

    unsigned year;
    double rating;

    char** keywords;
    int keywordsCount;

    void copyFrom(const Book& other);
    void free();
    
public:
    Book();
    Book(unsigned id, const char* author, const char* title, 
         const char* genre, const char* description, unsigned year, 
         double rating, char** keywords, int keywordsCount);

    Book(const Book& other);
    Book& operator=(const Book& other);
    ~Book();

    unsigned getId() const;
    const char* getAuthor() const;
    const char* getTitle() const;
    const char* getGenre() const;
    const char* getDescription() const;
    unsigned getYear() const;
    double getRating() const;
    const char* const* getKeywords() const;
    int getKeywordsCount() const;

    void setId(unsigned id);
    void setAuthor(const char* author);
    void setTitle(const char* title);
    void setGenre(const char* genre);
    void setDescription(const char* description);
    void setYear(unsigned year);
    void setRating(double rating);
    void setKeywords(char** keywords, int keywordsCount);
};