#include "Library.h"
#include <iostream>
using namespace std;

void printBook(Book* b) {
    if (!b) { cout << "NULL book\n"; return; }
    cout << "Book[" << b->getId() << "] '" << b->getTitle() << "' by " << b->getAuthor()
         << " ISBN:" << b->getISBN() << " Available:" << (b->isAvailable() ? "Yes":"No") << "\n";
}

int main() {
    Library lib;

    lib.addBook(Book(1, "The C++ Programming Language", "Bjarne Stroustrup", "9780321563842"));
    lib.addBook(Book(2, "Clean Code", "Robert C. Martin", "9780132350884"));
    lib.addBook(Book(3, "Design Patterns", "Gamma, Helm, Johnson, Vlissides", "9780201633610"));

    cout << "Adding duplicate book id 1: " << (lib.addBook(Book(1, "X","Y","Z")) ? "OK":"FAIL") << "\n";

    lib.registerUser(User(100, "Alice", 2));
    lib.registerUser(User(101, "Bob", 3));

    cout << "Alice borrows book 1: " << (lib.borrowBook(100, 1) ? "OK":"FAIL") << "\n";
    printBook(lib.findBookById(1));

    cout << "Bob tries to borrow book 1: " << (lib.borrowBook(101, 1) ? "OK":"FAIL") << "\n";
    cout << "Alice borrows book 2: " << (lib.borrowBook(100, 2) ? "OK":"FAIL") << "\n";
    cout << "Alice borrows book 3 (should fail limit): " << (lib.borrowBook(100, 3) ? "OK":"FAIL") << "\n";
    cout << "Bob borrows book 3: " << (lib.borrowBook(101, 3) ? "OK":"FAIL") << "\n";
    cout << "Attempt remove book 3 while borrowed (should fail): " << (lib.removeBook(3) ? "OK":"FAIL") << "\n";
    cout << "Bob returns book 3: " << (lib.returnBook(101, 3) ? "OK":"FAIL") << "\n";
    cout << "Now remove book 3: " << (lib.removeBook(3) ? "OK":"FAIL") << "\n";

    auto res = lib.searchByTitle("clean");
    cout << "Search 'clean' found " << res.size() << " book(s):\n";
    for (auto b : res) printBook(b);

    cout << "Alice returns book 3 (she never borrowed) expected FAIL: " << (lib.returnBook(100, 3) ? "OK":"FAIL") << "\n";
    cout << "Non-existent user borrow (id 999): " << (lib.borrowBook(999, 2) ? "OK":"FAIL") << "\n";
    cout << "Non-existent book borrow (id 999): " << (lib.borrowBook(101, 999) ? "OK":"FAIL") << "\n";

    cout << "\nFinal book list:\n";
    for (auto b : lib.listAllBooks()) {
        cout << b.getId() << " - " << b.getTitle() << " (Available: " << (b.isAvailable() ? "Y":"N") << ")\n";
    }
    return 0;
}
