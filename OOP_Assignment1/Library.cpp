#include "Library.h"
#include <algorithm>
#include <iostream>
using namespace std;

bool Library::addBook(const Book& book) {
    auto res = books.emplace(book.getId(), book);
    if (!res.second) {
        cerr << "[addBook] Book ID " << book.getId() << " already exists.\n";
        return false;
    }
    return true;
}

bool Library::removeBook(int bookId) {
    auto it = books.find(bookId);
    if (it == books.end()) {
        cerr << "[removeBook] Book ID " << bookId << " does not exist.\n";
        return false;
    }
    if (!it->second.isAvailable()) {
        cerr << "[removeBook] Cannot remove Book ID " << bookId << " — currently borrowed.\n";
        return false;
    }
    books.erase(it);
    return true;
}

Book* Library::findBookById(int bookId) {
    auto it = books.find(bookId);
    if (it == books.end()) return nullptr;
    return &it->second;
}

vector<Book*> Library::searchByTitle(const string& term) {
    vector<Book*> out;
    for (auto &kv : books) {
        if (icontains(kv.second.getTitle(), term)) out.push_back(&kv.second);
    }
    return out;
}

vector<Book*> Library::searchByAuthor(const string& term) {
    vector<Book*> out;
    for (auto &kv : books) {
        if (icontains(kv.second.getAuthor(), term)) out.push_back(&kv.second);
    }
    return out;
}

Book* Library::searchByISBN(const string& isbn) {
    for (auto &kv : books) {
        if (kv.second.getISBN() == isbn) return &kv.second;
    }
    return nullptr;
}

bool Library::registerUser(const User& user) {
    auto res = users.emplace(user.getId(), user);
    if (!res.second) {
        cerr << "[registerUser] User ID " << user.getId() << " already exists.\n";
        return false;
    }
    return true;
}

User* Library::findUserById(int userId) {
    auto it = users.find(userId);
    if (it == users.end()) return nullptr;
    return &it->second;
}

bool Library::borrowBook(int userId, int bookId) {
    User* user = findUserById(userId);
    if (!user) {
        cerr << "[borrowBook] User ID " << userId << " not found.\n";
        return false;
    }
    Book* book = findBookById(bookId);
    if (!book) {
        cerr << "[borrowBook] Book ID " << bookId << " not found.\n";
        return false;
    }
    if (!book->isAvailable()) {
        cerr << "[borrowBook] Book ID " << bookId << " is already borrowed.\n";
        return false;
    }
    if (!user->canBorrow()) {
        cerr << "[borrowBook] User ID " << userId << " has reached borrow limit.\n";
        return false;
    }
    if (!user->borrowBook(bookId)) {
        cerr << "[borrowBook] User ID " << userId << " already has Book ID " << bookId << ".\n";
        return false;
    }
    book->setAvailable(false);
    return true;
}

bool Library::returnBook(int userId, int bookId) {
    User* user = findUserById(userId);
    if (!user) {
        cerr << "[returnBook] User ID " << userId << " not found.\n";
        return false;
    }
    Book* book = findBookById(bookId);
    if (!book) {
        cerr << "[returnBook] Book ID " << bookId << " not found.\n";
        return false;
    }
    if (!user->returnBook(bookId)) {
        cerr << "[returnBook] User ID " << userId << " did not borrow Book ID " << bookId << ".\n";
        return false;
    }
    book->setAvailable(true);
    return true;
}

vector<Book> Library::listAllBooks() const {
    vector<Book> out;
    out.reserve(books.size());
    for (const auto &kv : books) out.push_back(kv.second);
    return out;
}

vector<User> Library::listAllUsers() const {
    vector<User> out;
    out.reserve(users.size());
    for (const auto &kv : users) out.push_back(kv.second);
    return out;
}

bool Library::icontains(const string& text, const string& sub) {
    string a = text;
    string b = sub;
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a.find(b) != string::npos;
}
