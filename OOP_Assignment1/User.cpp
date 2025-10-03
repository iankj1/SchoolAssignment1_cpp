#include "User.h"

User::User(int id, string name, int maxBorrow) : id(id), name(move(name)), maxBorrow(maxBorrow) {}

int User::getId() const { return id; }
const string& User::getName() const { return name; }
int User::getMaxBorrow() const { return maxBorrow; }
int User::borrowedCount() const { return static_cast<int>(borrowed.size()); }

bool User::canBorrow() const { return borrowedCount() < maxBorrow; }

bool User::borrowBook(int bookId) {
    if (!canBorrow()) return false;
    auto inserted = borrowed.insert(bookId);
    return inserted.second;
}

bool User::returnBook(int bookId) {
    return borrowed.erase(bookId) > 0;
}

vector<int> User::listBorrowed() const {
    vector<int> out;
    out.reserve(borrowed.size());
    for (int b : borrowed) out.push_back(b);
    return out;
}
