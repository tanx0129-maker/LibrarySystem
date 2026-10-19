#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Book.h"
#include "BorrowRecord.h"
#include "LibraryResource.h"
#include "User.h"

class LibrarySystem {
private:
    // 组合关系：图书馆统一管理不同派生类型的资源对象。
    std::vector<std::shared_ptr<LibraryResource>> resources;
    std::vector<std::shared_ptr<User>> users;
    std::vector<BorrowRecord> records;

    LibraryResource* findResource(const std::string& id);
    const LibraryResource* findResource(const std::string& id) const;
    User* findUser(const std::string& id);

public:
    LibraryResource* searchResource(const std::string& id);
    const LibraryResource* searchResource(const std::string& id) const;

    bool addResource(const std::shared_ptr<LibraryResource>& resource);
    bool updateResource(const std::string& id,
        const std::string& title,
        const std::string& creator,
        const std::string& detail);
    bool changeResourceQuantity(const std::string& id, int quantity);
    bool deleteResource(const std::string& id);

    // 保留图书接口，便于兼容实验一、二中的调用方式。
    Book* searchBook(const std::string& isbn);
    bool addBook(const Book& book);
    bool updateBook(const std::string& isbn,
        const std::string& title,
        const std::string& author,
        const std::string& publisher);
    bool deleteBook(const std::string& isbn);

    bool addUser(const std::shared_ptr<User>& user);
    bool updateUser(const std::string& id,
        const std::string& name,
        const std::string& department,
        int maxBorrowCount);

    bool borrowBook(const std::string& userId,
        const std::string& resourceId,
        const std::string& borrowDate);

    bool returnBook(const std::string& userId,
        const std::string& resourceId,
        const std::string& returnDate);

    bool isOverdue(const std::string& userId,
        const std::string& resourceId,
        const std::string& checkDate,
        int allowedDays = 30) const;

    double calculateFine(const std::string& userId,
        const std::string& resourceId,
        const std::string& checkDate,
        int allowedDays = 30,
        double dailyFine = 0.5) const;

    const std::vector<std::shared_ptr<LibraryResource>>& getResources() const;
    const std::vector<std::shared_ptr<User>>& getUsers() const;
    const std::vector<BorrowRecord>& getRecords() const;

    bool saveBooks(const std::string& filename) const;
    bool loadBooks(const std::string& filename);
    bool saveUsers(const std::string& filename) const;
    bool loadUsers(const std::string& filename);
    bool saveRecords(const std::string& filename) const;
    bool loadRecords(const std::string& filename);
};
