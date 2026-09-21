#define _CRT_SECURE_NO_WARNINGS
#include "LibrarySystem.h"
#include "Student.h"
#include "Teacher.h"
#include <fstream>
#include <sstream>
#include <algorithm>

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

bool LibrarySystem::isOverdue(
    const std::string& userId,
    const std::string& isbn,
    const std::string& checkDate,
    int allowedDays) const {

    for (auto record = records.rbegin();
        record != records.rend();
        ++record) {

        if (record->getUserId() == userId &&
            record->getIsbn() == isbn) {
            return record->isOverdue(
                checkDate, allowedDays);
        }
    }

    return false;
}

double LibrarySystem::calculateFine(
    const std::string& userId,
    const std::string& isbn,
    const std::string& checkDate,
    int allowedDays,
    double dailyFine) const {

    for (auto record = records.rbegin();
        record != records.rend();
        ++record) {

        if (record->getUserId() == userId &&
            record->getIsbn() == isbn) {
            return record->calculateFine(
                checkDate,
                allowedDays,
                dailyFine);
        }
    }

    return 0.0;
}

const std::vector<Book>& LibrarySystem::getBooks() const {
    return books;
}

bool LibrarySystem::saveBooks(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& book : books) {
        file << book.getIsbn() << "|"
             << book.getTitle() << "|"
             << book.getAuthor() << "|"
             << book.getPublisher() << "|"
             << (book.isAvailable() ? "1" : "0")
             << '\n';
    }

    return true;
}

bool LibrarySystem::loadBooks(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::vector<Book> loadedBooks;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream stream(line);

        std::string isbn;
        std::string title;
        std::string author;
        std::string publisher;
        std::string available;

        if (!std::getline(stream, isbn, '|') ||
            !std::getline(stream, title, '|') ||
            !std::getline(stream, author, '|') ||
            !std::getline(stream, publisher, '|') ||
            !std::getline(stream, available)) {
            return false;
        }

        Book book(isbn, title, author, publisher);
        book.setAvailable(available == "1");
        loadedBooks.push_back(book);
    }

    books = loadedBooks;
    return true;
}

bool LibrarySystem::saveUsers(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& user : users) {
        file << user->getRole() << "|"
            << user->getId() << "|"
            << user->getName() << "|"
            << user->getDepartment() << "|"
            << user->getMaxBorrowCount()
            << '\n';
    }

    return true;
}

bool LibrarySystem::loadUsers(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::vector<std::shared_ptr<User>> loadedUsers;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream stream(line);

        std::string role;
        std::string id;
        std::string name;
        std::string department;
        std::string maxBorrowText;

        if (!std::getline(stream, role, '|') ||
            !std::getline(stream, id, '|') ||
            !std::getline(stream, name, '|') ||
            !std::getline(stream, department, '|') ||
            !std::getline(stream, maxBorrowText)) {
            return false;
        }

        int maxBorrowCount = std::stoi(maxBorrowText);

        if (role == "Student") {
            loadedUsers.push_back(
                std::make_shared<Student>(
                    id, name, department, maxBorrowCount
                )
            );
        }
        else if (role == "Teacher") {
            loadedUsers.push_back(
                std::make_shared<Teacher>(
                    id, name, department, maxBorrowCount
                )
            );
        }
        else {
            return false;
        }
    }

    users = loadedUsers;
    return true;
}

bool LibrarySystem::saveRecords(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& record : records) {
        file << record.getUserId() << "|"
            << record.getIsbn() << "|"
            << record.getBorrowDate() << "|"
            << record.getReturnDate() << "|"
            << (record.isReturned() ? "1" : "0")
            << '\n';
    }

    return true;
}

bool LibrarySystem::loadRecords(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::vector<BorrowRecord> loadedRecords;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream stream(line);

        std::string userId;
        std::string isbn;
        std::string borrowDate;
        std::string returnDate;
        std::string returned;

        if (!std::getline(stream, userId, '|') ||
            !std::getline(stream, isbn, '|') ||
            !std::getline(stream, borrowDate, '|') ||
            !std::getline(stream, returnDate, '|') ||
            !std::getline(stream, returned)) {
            return false;
        }

        BorrowRecord record(userId, isbn, borrowDate);

        if (returned == "1") {
            record.markReturned(returnDate);
        }

        loadedRecords.push_back(record);
    }

    records = loadedRecords;
    return true;
}

Book* LibrarySystem::searchBook(const std::string& isbn) {
    return findBook(isbn);
}

bool LibrarySystem::updateBook(const std::string& isbn,
    const std::string& title,
    const std::string& author,
    const std::string& publisher) {
    Book* book = findBook(isbn);

    if (book == nullptr) {
        return false;
    }

    book->setTitle(title);
    book->setAuthor(author);
    book->setPublisher(publisher);

    return true;
}

bool LibrarySystem::deleteBook(const std::string& isbn) {
    Book* book = findBook(isbn);

    if (book == nullptr || !book->isAvailable()) {
        return false;
    }

    auto position = std::remove_if(
        books.begin(),
        books.end(),
        [&](const Book& item) {
            return item.getIsbn() == isbn;
        }
    );

    if (position == books.end()) {
        return false;
    }

    books.erase(position, books.end());
    return true;
}