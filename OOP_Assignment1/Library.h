#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Library {
public:
    Library() = default;

    bool addBook(const Book& book);
    bool removeBook(int bookId);
    Book* findBookById(int bookId);
    vector<Book*> searchByTitle(const string& term);
    vector<Book*> searchByAuthor(const string& term);
    Book* searchByISBN(const string& isbn);

    bool registerUser(const User& user);
    User* findUserById(int userId);

    bool borrowBook(int userId, int bookId);
    bool returnBook(int userId, int bookId);

    vector<Book> listAllBooks() const;
    vector<User> listAllUsers() const;

private:
    unordered_map<int, Book> books;
    unordered_map<int, User> users;

    static bool icontains(const string& text, const string& sub);
};

#endif // LIBRARY_H
