#define _CRT_SECURE_NO_WARNINGS
#include "BorrowRecord.h"

BorrowRecord::BorrowRecord(const std::string& userId,
    const std::string& isbn,
    const std::string& borrowDate)
    : userId(userId),
    isbn(isbn),
    borrowDate(borrowDate),
    returnDate(""),
    returned(false) {
}

void BorrowRecord::markReturned(const std::string& returnDate) {
    this->returnDate = returnDate;
    this->returned = true;
}

const std::string& BorrowRecord::getUserId() const {
    return userId;
}

const std::string& BorrowRecord::getIsbn() const {
    return isbn;
}

const std::string& BorrowRecord::getBorrowDate() const {
    return borrowDate;
}

const std::string& BorrowRecord::getReturnDate() const {
    return returnDate;
}

bool BorrowRecord::isReturned() const {
    return returned;
}