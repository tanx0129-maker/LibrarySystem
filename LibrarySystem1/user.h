#pragma once

#include <string>

class User {
protected:
    std::string id;
    std::string name;
    std::string department;
    int maxBorrowCount;

public:
    User(const std::string& id,
        const std::string& name,
        const std::string& department,
        int maxBorrowCount);

    virtual ~User() = default;

    virtual std::string getRole() const;

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getDepartment() const;
    int getMaxBorrowCount() const;
};