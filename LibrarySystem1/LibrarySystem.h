#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Book.h"
#include "User.h"
#include "BorrowRecord.h"

class LibrarySystem {
private:
    std::vector<Book> books;
    std::vector<std::shared_ptr<User>> users;
    std::vector<BorrowRecord> records;

    Book* findBook(const std::string& isbn);
    User* findUser(const std::string& id);

public:

    Book* searchBook(const std::string& isbn);

    bool updateBook(const std::string& isbn,
        const std::string& title,
        const std::string& author,
        const std::string& publisher);

    bool deleteBook(const std::string& isbn);

    bool saveRecords(const std::string& filename) const;
    bool loadRecords(const std::string& filename);

    bool saveUsers(const std::string& filename) const;
    bool loadUsers(const std::string& filename);

    bool saveBooks(const std::string& filename) const;
    bool loadBooks(const std::string& filename);
    bool addBook(const Book& book);
    bool addUser(const std::shared_ptr<User>& user);

    bool borrowBook(const std::string& userId,
        const std::string& isbn,
        const std::string& borrowDate);

    bool returnBook(const std::string& userId,
        const std::string& isbn,
        const std::string& returnDate);

    bool isOverdue(const std::string& userId,
        const std::string& isbn,
        const std::string& checkDate,
        int allowedDays = 30) const;

    double calculateFine(const std::string& userId,
        const std::string& isbn,
        const std::string& checkDate,
        int allowedDays = 30,
        double dailyFine = 0.5) const;

    const std::vector<Book>& getBooks() const;
};
