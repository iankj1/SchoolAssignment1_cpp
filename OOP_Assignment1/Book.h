#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
public:
    Book() = default;
    Book(int id, string title, string author, string isbn);

    int getId() const;
    const string& getTitle() const;
    const string& getAuthor() const;
    const string& getISBN() const;
    bool isAvailable() const;

    void setAvailable(bool val);

private:
    int id{0};
    string title;
    string author;
    string isbn;
    bool available{true};
};

#endif // BOOK_H
