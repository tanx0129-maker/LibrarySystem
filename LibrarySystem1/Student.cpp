#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"

Student::Student(const std::string& id,
    const std::string& name,
    const std::string& department,
    int maxBorrowCount)
    : User(id, name, department, maxBorrowCount) {
}

std::string Student::getRole() const {
    return "Student";
}