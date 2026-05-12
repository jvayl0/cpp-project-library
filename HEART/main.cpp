#include "HEAD/Book.hpp"
#include <iostream>

int main() {

    char* keywords[] = {
        (char*)"dystopia",
        (char*)"freedom",
        (char*)"society"
    };

    char* kw1[] = {
        (char*)"magic",
        (char*)"fantasy",
        (char*)"dragon"
    };

    char* kw2[] = {
        (char*)"dark",
        (char*)"adventure"
    };

    std::cout << "===== CREATE BOOK =====\n";

    Book book1(
        1,
        "George Orwell",
        "1984",
        "Dystopian",
        "Classic dystopian novel",
        1949,
        4.9,
        keywords,
        3
    );

    Book book(
        1,
        "J.R.R Tolkien",
        "The Hobbit",
        "Fantasy",
        "Adventure book",
        1937,
        4.8,
        kw1,
        3
    );

    std::cout << "ID: " << book1.getId() << "\n";
    std::cout << "Author: " << book1.getAuthor() << "\n";
    std::cout << "Title: " << book1.getTitle() << "\n";
    std::cout << "Genre: " << book1.getGenre() << "\n";
    std::cout << "Description: " << book1.getDescription() << "\n";
    std::cout << "Year: " << book1.getYear() << "\n";
    std::cout << "Rating: " << book1.getRating() << "\n";

    std::cout << "Keywords: ";
    for (int i = 0; i < book1.getKeywordsCount(); i++) {
        std::cout << book1.getKeywords()[i] << " ";
    }
    std::cout << "\n\n";

    // ======================================================
    // COPY TEST
    // ======================================================

    std::cout << "===== COPY BOOK =====\n";

    Book book2 = book1;

    std::cout << "Author: " << book2.getAuthor() << "\n";
    std::cout << "Title: " << book2.getTitle() << "\n\n";

    // ======================================================
    // ASSIGNMENT TEST
    // ======================================================

    std::cout << "===== ASSIGNMENT TEST =====\n";

    Book book3;

    book3 = book2;

    std::cout << "Author: " << book3.getAuthor() << "\n";
    std::cout << "Title: " << book3.getTitle() << "\n\n";

    // ======================================================
    // SETTERS TEST
    // ======================================================

    std::cout << "===== SETTERS TEST =====\n";

    book3.setAuthor("J.R.R Tolkien");
    book3.setTitle("The Hobbit");
    book3.setYear(1937);
    book3.setRating(4.8);

    std::cout << "Author: " << book3.getAuthor() << "\n";
    std::cout << "Title: " << book3.getTitle() << "\n";
    std::cout << "Year: " << book3.getYear() << "\n";
    std::cout << "Rating: " << book3.getRating() << "\n\n";

    std::cout << "Initial keywords:\n";
    for (int i = 0; i < book.getKeywordsCount(); i++) {
        std::cout << book.getKeywords()[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "===== SET NEW KEYWORDS =====\n";

    book.setKeywords(kw2, 2);

    std::cout << "After setKeywords:\n";
    for (int i = 0; i < book.getKeywordsCount(); i++) {
        std::cout << book.getKeywords()[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "===== SET EMPTY KEYWORDS =====\n";

    book.setKeywords(nullptr, 0);

    std::cout << "After clearing keywords:\n";
    std::cout << "Count: " << book.getKeywordsCount() << "\n";

    if (book.getKeywords() == nullptr) {
        std::cout << "Keywords is NULL (OK)\n";
    }

    return 0;
}