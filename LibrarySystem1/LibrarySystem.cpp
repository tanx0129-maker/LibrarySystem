#define _CRT_SECURE_NO_WARNINGS
#include "LibrarySystem.h"

Book* LibrarySystem::findBook(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

User* LibrarySystem::findUser(const std::string& id) {
    for (auto& user : users) {
        if (user->getId() == id) {
            return user.get();
        }
    }
    return nullptr;
}

bool LibrarySystem::addBook(const Book& book) {
    if (findBook(book.getIsbn()) != nullptr) {
        return false;
    }

    books.push_back(book);
    return true;
}

bool LibrarySystem::addUser(const std::shared_ptr<User>& user) {
    if (findUser(user->getId()) != nullptr) {
        return false;
    }

    users.push_back(user);
    return true;
}

bool LibrarySystem::borrowBook(const std::string& userId,
    const std::string& isbn,
    const std::string& borrowDate) {
    Book* book = findBook(isbn);
    User* user = findUser(userId);

    if (book == nullptr || user == nullptr || !book->isAvailable()) {
        return false;
    }

    int activeBorrowCount = 0;

    for (const auto& record : records) {
        if (record.getUserId() == userId &&
            !record.isReturned()) {
            activeBorrowCount++;
        }
    }

    if (activeBorrowCount >= user->getMaxBorrowCount()) {
        return false;
    }

    records.emplace_back(userId, isbn, borrowDate);
    book->setAvailable(false);

    return true;
}

bool LibrarySystem::returnBook(const std::string& userId,
    const std::string& isbn,
    const std::string& returnDate) {
    Book* book = findBook(isbn);

    if (book == nullptr || book->isAvailable()) {
        return false;
    }

    for (auto& record : records) {
        if (record.getUserId() == userId &&
            record.getIsbn() == isbn &&
            !record.isReturned()) {

            record.markReturned(returnDate);
            book->setAvailable(true);
            return true;
        }
    }

    return false;
}

const std::vector<Book>& LibrarySystem::getBooks() const {
    return books;
}