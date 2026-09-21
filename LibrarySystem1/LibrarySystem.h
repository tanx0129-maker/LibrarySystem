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
    bool addBook(const Book& book);
    bool addUser(const std::shared_ptr<User>& user);

    bool borrowBook(const std::string& userId,
        const std::string& isbn,
        const std::string& borrowDate);

    bool returnBook(const std::string& userId,
        const std::string& isbn,
        const std::string& returnDate);

    const std::vector<Book>& getBooks() const;
};
