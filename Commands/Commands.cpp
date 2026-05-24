#include "Commands.hpp"

#include "../FileParsers/FileParser.hpp"
#include "../FileParsers/UserFileParser.hpp"
#include "../Library/Library.hpp"
#include "../User/UserCollection.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

//FOR PASSWORD READER
#include <termios.h>
#include <unistd.h>


// CASE IGNORE HELPERS
namespace {
    char toLowerChar(char c) {
        if(c >= 'A' && c <= 'Z'){
            return c + ('a' - 'A');
        }
        return c;
    }

    bool contains(const char* text, const char* search) {
        if(!search){
            return true;
        }

        for(size_t i = 0; text[i] != '\0'; i++){
            size_t j = 0;

            while(search[j] && text[i + j] == search[j]){
                j++;
            }

            if(!search[j]){
                return true;
            }
        }
        return true;
    }

    bool ignoreCase(const char* text, const char* search) {
        char lowerText[1024];
        char lowerSearch[1024];

        size_t i = 0;

        while(text[i]){
            lowerText[i] = toLowerChar(text[i]);
            i++;
        }

        lowerText[i] = '\0';

        i = 0;

        while(search[i]){
            lowerSearch[i] = toLowerChar(search[i]);
            i++;
        }

        lowerSearch[i] = '\0';

        return contains(lowerText, lowerSearch);
    }
}


Commands::Commands() {
    currentUser = nullptr;

    isRunning = true;
    isFileOpen = false;
    isClosed = false;

    currentFile[0] = '\0';
}

// HELPERS
bool Commands::isAdmin() const {
    return currentUser && currentUser->isAdmin();
}

// RUN

void Commands::run() {
    char line[1024];
    std::cout << "System started!\n";

    while(isRunning) {
        std::cout << "> ";

        std::cin.getline(line, 1024);
        executeCommand(line);
    }
}

// PASSWORD READER ONLY WORKING ON MAC/LINUX

void Commands::readPassword(char* password, int maxLen) {

    termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // disable canonical mode + echo
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int i = 0;
    while (true) {
        char ch = getchar();
        if (ch == '\n' || ch == '\r') {
            break;
        }
        // backspace
        if (ch == 127 || ch == 8) {
            if (i > 0) {
                i--;
                std::cout << "\b \b";
                std::cout.flush();
            }
        }
        else if (i < maxLen - 1) {
            password[i++] = ch;
            std::cout << '*';
            std::cout.flush();
        }
    }
    password[i] = '\0';

    // restore terminal 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";
}

// FILE COMMANDS

void Commands::open(const char* file) {
    if(isFileOpen){
        std::cout << "File already opened\n";
        return;
    }

    std::ifstream test(file);

    if(!test.is_open()) {
        library = Library();
        users = UserCollection();

        strcpy(currentFile, file);
        isFileOpen = true;

        std::cout << "File not found. Creating new empty file: " << file << std::endl;
        return;
    }
    test.close();

    bool ok = FileParser::loadFromFile(file, library);

    if(!ok) {
        std::cout << "Error loading file\n";
        exit();
    }

    UserFileParser::loadFromFile("users.txt", users);

    strcpy(currentFile, file);
    isFileOpen = true;

    std::cout << "Successfully opened " << file << std::endl;
}

void Commands::close() {
    if(!isFileOpen) {
        std::cout << "No file opened!\n";
        return;
    }

    library = Library();
    users = UserCollection();

    currentUser = nullptr;
    currentFile[0] = '\0';

    isFileOpen = false;
    isClosed = true;

    std::cout << "Successfully closed!\n";
}

void Commands::save() {
    if(!isFileOpen) {
        std::cout << "No file opened\n";
        return;
    }

    if(currentFile[0] == '\0') {
        std::cout << "No file selected!\n";
        return;
    }

    bool ok = FileParser::saveToFile(currentFile, library);

    if(!ok) {
        std::cout << "Error saving data\n";
        return;
    }

    UserFileParser::saveToFile("users.txt", users);

    std::cout << "Saved" << currentFile << std::endl;
}

void Commands::saveAs(const char* file) {
    if(!isFileOpen) {
        std::cout << "No file opened!\n";
        return;
    }

    if(!file || file[0] == '\0') {
        std::cout << "Invalid file name\n";
        return;
    }

    bool ok = FileParser::saveToFile(file, library);

    if(!ok) {
        std::cout << "Error saving file\n";
        return;
    }

    UserFileParser::saveToFile("users.txt", users);

    std::cout << "Saved as " << file << std::endl;
}

void Commands::help() {
    std::cout << "The following commands are supported:\n\n"

        << "FILE OPERATIONS:\n"
        << "open <file>     - opens a file\n"
        << "close           - closes current file\n"
        << "save            - saves current file\n"
        << "saveas <file>   - saves as new file\n\n"

        << "AUTH:\n"
        << "login           - logs into system\n"
        << "logout          - logs out user\n\n"

        << "BOOKS (CLIENT):\n"
        << "books all       - lists all books\n"
        << "books info <id> - shows book details\n"
        << "books find ...  - searches books\n"
        << "books sort ...  - sorts books\n\n"

        << "BOOKS (ADMIN ONLY):\n"
        << "books add       - adds new book\n"
        << "books remove    - removes book\n\n"

        << "USERS (ADMIN ONLY):\n"
        << "users add       - adds new user\n"
        << "users remove    - removes user\n\n"

        << "SYSTEM:\n"
        << "help            - shows this help\n"
        << "exit            - exits program\n";
}

void Commands::exit() {
    isRunning = false;

    std::cout << "Exiting the program\n";
}

// LOGIN AND LOGOUT - AUTH

void Commands::login() {
    if(currentUser) {
        std::cout << "Already logged in\n";
        return;
    }

    char username[50];
    char password[50];

    std::cout << "Username: ";
    std::cin.getline(username, 50);

    std::cout << "Password: ";
    readPassword(password, 50);

    currentUser = users.login(username, password);

    if(currentUser){
        std::cout << "Welcome, " << currentUser->getUsername() << std::endl;
    }else {
        std::cout << "Wrong username or password!\n";
    }
}

void Commands::logout() {
    if(!currentUser){
        std::cout << "No user is logged in\n";
        return;
    }

    std::cout << "Goodbye, " << currentUser->getUsername() << std::endl;

    currentUser = nullptr;
}

//                      BOOKS

void Commands::booksAll() const {
    const Book* books = library.getBooks();
    unsigned size = library.getSize();

    if(size == 0){
        std::cout << "No books available\n";
        return;
    }

    for(size_t i = 0; i < size; i++){
        std::cout 
        << "Title: " << books[i].getTitle() << " | "
        << "Author: " << books[i].getAuthor() << " | "
        << "Genre: " << books[i].getGenre() << " | "
        << "ID: " << books[i].getId() << std::endl;
    }
}

void Commands::booksAdd() {
    if(!isAdmin()) {
        std::cout << "Admin only!\n";
        return;
    }

    unsigned id, year;
    double rating;

    char author[128];
    char title[128];
    char genre[128];
    char description[128];

    int keywordsCount;

    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Author: ";
    std::cin.getline(author, 128);

    std::cout << "Title: ";
    std::cin.getline(title, 128);

    std::cout << "Genre: ";
    std::cin.getline(genre, 128);

    std::cout << "Description: ";
    std::cin.getline(description, 256);

    std::cout << "Year: ";
    std::cin >> year;

    std::cout << "Rating: ";
    std::cin >> rating;

    std::cout << "Keywords count: ";
    std::cin >> keywordsCount;
    std::cin.ignore();

    char** keywords = nullptr;

    if(keywordsCount > 0) {
        keywords = new char*[keywordsCount];

        for(size_t i = 0; i < keywordsCount; i++){
            char buffer[128];

            std::cout << "Keyword " << i + 1  << ": ";
            std::cin.getline(buffer, 128);

            keywords[i] = new char[strlen(buffer) + 1];
            strcpy(keywords[i], buffer);
        }
    }

    Book book (id, author, title, genre, description, year, rating, keywords, keywordsCount);

    library.addBook(book);

    for(size_t i = 0; i < keywordsCount; i++){
        delete[] keywords[i];
    }
    delete[] keywords;

    std::cout << "Book added!\n";
}

void Commands::booksRemove() {
    if(!isAdmin()){
        std::cout << "Admin only!\n";
        return;
    }

    unsigned id;

    std::cout << "Enter book ID: ";
    std::cin >> id;
    std::cin.ignore();

    Book* book = library.getBookById(id);

    if(!book){
        std::cout << "Book not found!\n";
        return;
    }

    library.removeBook(id);

    std::cout << "Book removed!\n";
}

void Commands::booksInfo(unsigned id) {
    Book* book = library.getBookById(id);

    if(!book){
        std::cout << "Book not found!\n";
        return;
    }

    std::cout << "ID: " << book->getId() << std::endl;
    std::cout << "Title: " << book->getTitle() << std::endl;
    std::cout << "Author: " << book->getAuthor() << std::endl;
    std::cout << "Genre: " << book->getGenre() << std::endl;
    std::cout << "Description: " << book->getDescription() << std::endl;
    std::cout << "Year: " << book->getYear() << std::endl;
    std::cout << "Rating: " << book->getRating() << std::endl;
    std::cout << "Keywords: ";

    const char* const* keywords = book->getKeywords();

    for(size_t i = 0; i < book->getKeywordsCount(); i++){
        std::cout << keywords[i] << " ";
    }
    std::cout << std::endl;
}

void Commands::booksFind(const char* option, const char* str) {
    const Book* books = library.getBooks();
    size_t size = library.getSize();

    bool found = false;

    for(size_t i = 0; i < size; i++){
        bool match = false;
        if(strcmp(option, "title") == 0){
            match = ignoreCase(books[i].getTitle(), str);
        }
        else if(strcmp(option, "author") == 0){
            match = ignoreCase(books[i].getAuthor(), str);
        }
        else if(strcmp(option, "tag") == 0){
            const char* const* keywords = books[i].getKeywords();

            for(size_t j = 0; j < books[i].getKeywordsCount(); j++){
                if(ignoreCase(keywords[j], str)){
                    match = true;
                    break;
                }
            }
        }

        if(match){
            found = true;
            std::cout << books[i].getId() << "|" << books[i].getTitle() << "|"
                      << books[i].getAuthor() << "|" << books[i].getGenre() << std::endl;
        }
    }

    if(!found){
        std::cout << "No matching books!\n";
    }
}

// EXECUTE COMMAND

void Commands::executeCommand(char* line) {

    bool isSystemCommand =
        strncmp(line, "open ", 5) == 0 ||
        strcmp(line, "exit") == 0 ||
        strcmp(line, "help") == 0 ||
        strcmp(line, "login") == 0 ||
        strcmp(line, "logout") == 0;

    if (isClosed && !isSystemCommand) {
        std::cout << "File is closed. Only open/login/logout/help/exit are allowed.\n";
        return;
    }

    if(strncmp(line, "open ", 5) == 0) {
        open(line + 5);
        isClosed = false;
        return;
    }
    else if(strcmp(line, "close") == 0) {
        close();
        isClosed = true;
        return;
    }
    else if(strcmp(line, "save") == 0) {
        save();
    }
    else if(strncmp(line, "saveas ", 7) == 0) {
        saveAs(line + 7);
    }
    else if(strcmp(line, "login") == 0) {
        login();
    }
    else if(strcmp(line, "logout") == 0) {
        logout();
    }
    else if(strcmp(line, "books all") == 0) {
        booksAll();
    }
    else if(strncmp(line, "books info ", 11) == 0) {
        unsigned id = atoi(line + 11);
        booksInfo(id);
    }
    else if(strncmp(line, "books find ", 11) == 0) {
        char* ptr = line + 11;
        char* option = strtok(ptr, " ");
        char* str = strtok(nullptr, "");

        if(option && str) {
            while(*str == ' '){
                str++;
            }
            booksFind(option, str);
        }
    }
    else if(strncmp(line, "books sort ", 11) == 0) {
        char* ptr = line + 11;
        char* option = strtok(ptr, " ");
        char* order = strtok(nullptr, " ");
        
        if(!order){
            order = (char*)"asc";
        }

        if(option){
            booksSort(option, order);
        }
    }
    else if(strcmp(line, "books add") == 0) {
        booksAdd();
    }
    else if(strcmp(line, "books remove") == 0) {
        booksRemove();
    }
    else if(strcmp(line, "user add") == 0) {
        userAdd();
    }
    else if(strcmp(line, "user remove") == 0) {
        userRemove();
    }
    else if(strcmp(line, "help") == 0) {
        help();
    }
    else if(strcmp(line, "exit") == 0){
        exit();
        return;
    }
    else {
        std::cout << "Unknown command!\n";
    }
}