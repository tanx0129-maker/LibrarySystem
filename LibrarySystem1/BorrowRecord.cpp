#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iomanip>
#include <sstream>
#include "BorrowRecord.h"

namespace {
    bool parseDate(const std::string& text, std::tm& date) {
        date = {};
        date.tm_isdst = -1;

        std::istringstream input(text);
        input >> std::get_time(&date, "%Y-%m-%d");

        if (input.fail()) {
            return false;
        }

        date.tm_hour = 12;
        return std::mktime(&date) != static_cast<std::time_t>(-1);
    }

    int daysBetween(const std::string& start,
        const std::string& end) {
        std::tm startDate{};
        std::tm endDate{};

        if (!parseDate(start, startDate) ||
            !parseDate(end, endDate)) {
            return -1;
        }

        return static_cast<int>(
            std::difftime(
                std::mktime(&endDate),
                std::mktime(&startDate)
            ) / (24 * 60 * 60)
            );
    }
}

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

bool BorrowRecord::isOverdue(const std::string& checkDate,
    int allowedDays) const {
    const std::string& endDate =
        returned ? returnDate : checkDate;

    int days = daysBetween(borrowDate, endDate);

    return days >= 0 && days > allowedDays;
}

double BorrowRecord::calculateFine(const std::string& checkDate,
    int allowedDays,
    double dailyFine) const {
    const std::string& endDate =
        returned ? returnDate : checkDate;

    int days = daysBetween(borrowDate, endDate);

    if (days <= allowedDays || dailyFine <= 0) {
        return 0.0;
    }

    return (days - allowedDays) * dailyFine;
}