#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class User {
public:
    User() = default;
    User(int id, string name, int maxBorrow = 3);

    int getId() const;
    const string& getName() const;
    int getMaxBorrow() const;
    int borrowedCount() const;

    bool canBorrow() const;
    bool borrowBook(int bookId);
    bool returnBook(int bookId);
    vector<int> listBorrowed() const;

private:
    int id{0};
    string name;
    int maxBorrow{3};
    unordered_set<int> borrowed;
};

#endif // USER_H
