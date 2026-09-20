#pragma once

#include "User.h"

class Student : public User {
public:
    Student(const std::string& id,
        const std::string& name,
        const std::string& department,
        int maxBorrowCount);

    std::string getRole() const override;
};
