#define _CRT_SECURE_NO_WARNINGS

#include "Teacher.h"

Teacher::Teacher(const std::string& id,
    const std::string& name,
    const std::string& department,
    int maxBorrowCount)
    : User(id, name, department, maxBorrowCount) {
}

std::string Teacher::getRole() const {
    return "Teacher";
}