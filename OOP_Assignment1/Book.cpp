#include "Book.h"

Book::Book(int id, string title, string author, string isbn)
    : id(id), title(move(title)), author(move(author)), isbn(move(isbn)), available(true) {}

int Book::getId() const { return id; }
const string& Book::getTitle() const { return title; }
const string& Book::getAuthor() const { return author; }
const string& Book::getISBN() const { return isbn; }
bool Book::isAvailable() const { return available; }
void Book::setAvailable(bool val) { available = val; }
