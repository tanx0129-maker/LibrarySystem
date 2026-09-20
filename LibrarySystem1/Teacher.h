#pragma once

#include "User.h"

class Teacher : public User {
public:
    Teacher(const std::string& id,
        const std::string& name,
        const std::string& department,
        int maxBorrowCount);

    std::string getRole() const override;
};