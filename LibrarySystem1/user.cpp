#define _CRT_SECURE_NO_WARNINGS
#include "User.h"

User::User(const std::string& id,
    const std::string& name,
    const std::string& department,
    int maxBorrowCount)
    : id(id),
    name(name),
    department(department),
    maxBorrowCount(maxBorrowCount) {
}

std::string User::getRole() const {
    return "User";
}

const std::string& User::getId() const {
    return id;
}

const std::string& User::getName() const {
    return name;
}

const std::string& User::getDepartment() const {
    return department;
}

int User::getMaxBorrowCount() const {
    return maxBorrowCount;
}