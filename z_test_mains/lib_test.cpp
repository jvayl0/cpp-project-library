#include <iostream>
#include <cstring>

#include "Library/Library.hpp"

void printLibrary(const Library& lib) {

    std::cout << "\n===== LIBRARY =====\n";

    for (unsigned i = 0; i < lib.getSize(); i++) {

        const Book& b = lib.getBooks()[i];

        std::cout << "ID: " << b.getId()
                  << "\nTitle: " << b.getTitle()
                  << "\nAuthor: " << b.getAuthor()
                  << "\nYear: " << b.getYear()
                  << "\nRating: " << b.getRating()
                  << "\n-----------------\n";
    }

    std::cout << "===================\n";
}

int main() {

    // ===================== CREATE LIBRARY =====================

    Library lib;

    std::cout << "Initial library:\n";
    printLibrary(lib);

    // ===================== ADD BOOKS =====================

    Book b1(1, "George Orwell", "1984", "Dystopia",
            "Classic dystopian novel", 1949, 4.9,
            nullptr, 0);

    Book b2(2, "J.R.R Tolkien", "The Hobbit", "Fantasy",
            "Adventure in Middle-earth", 1937, 4.8,
            nullptr, 0);

    Book b3(3, "Frank Herbert", "Dune", "Sci-Fi",
            "Desert planet politics", 1965, 4.7,
            nullptr, 0);
    Book b4(4, "Frank Herbert", "Dune", "Sci-Fi",
            "Desert planet politics", 1965, 4.7,
            nullptr, 0);

    Book b5(5, "Frank Herbert", "Dune", "Sci-Fi",
            "Desert planet politics", 1965, 4.7,
            nullptr, 0);

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addBook(b3);
    lib.addBook(b4);
    lib.addBook(b5);
    

    std::cout << "\nAfter adding books:\n";
    printLibrary(lib);

    // ===================== GET BY ID =====================

    std::cout << "\nTesting getBookById:\n";

    Book* found = lib.getBookById(2);

    if (found) {
        std::cout << "Found: " << found->getTitle() << "\n";
    }

    // ===================== REMOVE BOOK =====================

    std::cout << "\nRemoving book with ID 1\n";

    lib.removeBook(1);

    printLibrary(lib);

    // ===================== COPY TEST =====================

    std::cout << "\n===== COPY TEST =====\n";

    Library copyLib = lib;

    printLibrary(copyLib);

    // ===================== ASSIGNMENT TEST =====================

    std::cout << "\n===== ASSIGNMENT TEST =====\n";

    Library assignedLib;

    assignedLib = lib;

    printLibrary(assignedLib);

    // ===================== MODIFICATION TEST =====================

    std::cout << "\nModifying original library...\n";

    lib.removeBook(2);

    printLibrary(lib);

    std::cout << "\nCopied library (should NOT change):\n";
    printLibrary(copyLib);

    return 0;
}