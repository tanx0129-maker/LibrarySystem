#pragma once

#include <string>

class BorrowRecord {
private:
    std::string userId;
    std::string isbn;
    std::string borrowDate;
    std::string returnDate;
    bool returned;

public:
    BorrowRecord(const std::string& userId,
        const std::string& isbn,
        const std::string& borrowDate);

    void markReturned(const std::string& returnDate);

    const std::string& getUserId() const;
    const std::string& getIsbn() const;
    const std::string& getBorrowDate() const;
    const std::string& getReturnDate() const;

    bool isReturned() const;
};