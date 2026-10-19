#define _CRT_SECURE_NO_WARNINGS

#include "LibrarySystem.h"

#include "DigitalResource.h"
#include "Magazine.h"
#include "Student.h"
#include "Teacher.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

namespace {
    std::vector<std::string> split(const std::string& line) {
        std::vector<std::string> result;
        std::stringstream stream(line);
        std::string value;

        while (std::getline(stream, value, '|')) {
            result.push_back(value);
        }

        return result;
    }

    bool parseInteger(const std::string& text, int& value) {
        try {
            size_t position = 0;
            value = std::stoi(text, &position);
            return position == text.size();
        }
        catch (...) {
            return false;
        }
    }
}

LibraryResource* LibrarySystem::findResource(const std::string& id) {
    for (const auto& resource : resources) {
        if (resource != nullptr && resource->getId() == id) {
            return resource.get();
        }
    }

    return nullptr;
}

const LibraryResource* LibrarySystem::findResource(
    const std::string& id) const {
    for (const auto& resource : resources) {
        if (resource != nullptr && resource->getId() == id) {
            return resource.get();
        }
    }

    return nullptr;
}

User* LibrarySystem::findUser(const std::string& id) {
    for (const auto& user : users) {
        if (user != nullptr && user->getId() == id) {
            return user.get();
        }
    }

    return nullptr;
}

LibraryResource* LibrarySystem::searchResource(const std::string& id) {
    return findResource(id);
}

const LibraryResource* LibrarySystem::searchResource(
    const std::string& id) const {
    return findResource(id);
}

bool LibrarySystem::addResource(
    const std::shared_ptr<LibraryResource>& resource) {
    if (resource == nullptr || findResource(resource->getId()) != nullptr) {
        return false;
    }

    resources.push_back(resource);
    return true;
}

bool LibrarySystem::updateResource(const std::string& id,
    const std::string& title,
    const std::string& creator,
    const std::string& detail) {
    LibraryResource* resource = findResource(id);

    if (resource == nullptr) {
        return false;
    }

    resource->update(title, creator, detail);
    return true;
}

bool LibrarySystem::changeResourceQuantity(const std::string& id,
    int quantity) {
    LibraryResource* resource = findResource(id);
    return resource != nullptr && resource->setQuantity(quantity);
}

bool LibrarySystem::deleteResource(const std::string& id) {
    LibraryResource* resource = findResource(id);

    if (resource == nullptr ||
        resource->getAvailableCopies() != resource->getTotalCopies()) {
        return false;
    }

    auto position = std::remove_if(
        resources.begin(),
        resources.end(),
        [&](const std::shared_ptr<LibraryResource>& item) {
            return item != nullptr && item->getId() == id;
        }
    );

    if (position == resources.end()) {
        return false;
    }

    resources.erase(position, resources.end());
    return true;
}

Book* LibrarySystem::searchBook(const std::string& isbn) {
    return dynamic_cast<Book*>(findResource(isbn));
}

bool LibrarySystem::addBook(const Book& book) {
    return addResource(std::make_shared<Book>(book));
}

bool LibrarySystem::updateBook(const std::string& isbn,
    const std::string& title,
    const std::string& author,
    const std::string& publisher) {
    Book* book = searchBook(isbn);

    if (book == nullptr) {
        return false;
    }

    book->update(title, author, publisher);
    return true;
}

bool LibrarySystem::deleteBook(const std::string& isbn) {
    if (searchBook(isbn) == nullptr) {
        return false;
    }

    return deleteResource(isbn);
}

bool LibrarySystem::addUser(const std::shared_ptr<User>& user) {
    if (user == nullptr || findUser(user->getId()) != nullptr) {
        return false;
    }

    users.push_back(user);
    return true;
}

bool LibrarySystem::updateUser(const std::string& id,
    const std::string& name,
    const std::string& department,
    int maxBorrowCount) {
    User* user = findUser(id);
    if (user == nullptr || maxBorrowCount <= 0) {
        return false;
    }

    user->setName(name);
    user->setDepartment(department);
    user->setMaxBorrowCount(maxBorrowCount);
    return true;
}

bool LibrarySystem::borrowBook(const std::string& userId,
    const std::string& resourceId,
    const std::string& borrowDate) {
    LibraryResource* resource = findResource(resourceId);
    User* user = findUser(userId);

    if (resource == nullptr || user == nullptr || !resource->isAvailable()) {
        return false;
    }

    int activeBorrowCount = 0;
    for (const auto& record : records) {
        if (record.getUserId() == userId && !record.isReturned()) {
            ++activeBorrowCount;
        }
    }

    if (activeBorrowCount >= user->getMaxBorrowCount() ||
        !resource->borrowCopy()) {
        return false;
    }

    records.emplace_back(userId, resourceId, borrowDate);
    return true;
}

bool LibrarySystem::returnBook(const std::string& userId,
    const std::string& resourceId,
    const std::string& returnDate) {
    LibraryResource* resource = findResource(resourceId);

    if (resource == nullptr) {
        return false;
    }

    for (auto& record : records) {
        if (record.getUserId() == userId &&
            record.getIsbn() == resourceId &&
            !record.isReturned()) {
            record.markReturned(returnDate);
            resource->returnCopy();
            return true;
        }
    }

    return false;
}

bool LibrarySystem::isOverdue(const std::string& userId,
    const std::string& resourceId,
    const std::string& checkDate,
    int allowedDays) const {
    for (auto record = records.rbegin();
        record != records.rend();
        ++record) {
        if (record->getUserId() == userId &&
            record->getIsbn() == resourceId) {
            return record->isOverdue(checkDate, allowedDays);
        }
    }

    return false;
}

double LibrarySystem::calculateFine(const std::string& userId,
    const std::string& resourceId,
    const std::string& checkDate,
    int allowedDays,
    double dailyFine) const {
    for (auto record = records.rbegin();
        record != records.rend();
        ++record) {
        if (record->getUserId() == userId &&
            record->getIsbn() == resourceId) {
            return record->calculateFine(
                checkDate, allowedDays, dailyFine);
        }
    }

    return 0.0;
}

const std::vector<std::shared_ptr<LibraryResource>>&
LibrarySystem::getResources() const {
    return resources;
}

const std::vector<std::shared_ptr<User>>& LibrarySystem::getUsers() const {
    return users;
}

const std::vector<BorrowRecord>& LibrarySystem::getRecords() const {
    return records;
}

bool LibrarySystem::saveBooks(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& resource : resources) {
        if (resource != nullptr) {
            file << resource->serialize() << '\n';
        }
    }

    return true;
}

bool LibrarySystem::loadBooks(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::vector<std::shared_ptr<LibraryResource>> loadedResources;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        const auto parts = split(line);
        std::shared_ptr<LibraryResource> resource;

        try {
            if (parts.size() == 5) {
                // 兼容实验二旧格式：isbn|title|author|publisher|available。
                auto book = std::make_shared<Book>(
                    parts[0], parts[1], parts[2], parts[3]);
                book->setAvailable(parts[4] == "1");
                resource = book;
            }
            else if (parts.size() == 7 && parts[0] == "Book") {
                auto book = std::make_shared<Book>(
                    parts[1], parts[2], parts[3], parts[4],
                    std::stoi(parts[5]));
                book->setAvailableCopies(std::stoi(parts[6]));
                resource = book;
            }
            else if (parts.size() == 7 && parts[0] == "Magazine") {
                auto magazine = std::make_shared<Magazine>(
                    parts[1], parts[2], parts[3], parts[4],
                    std::stoi(parts[5]));
                magazine->setAvailableCopies(std::stoi(parts[6]));
                resource = magazine;
            }
            else if (parts.size() == 7 && parts[0] == "Digital") {
                auto digital = std::make_shared<DigitalResource>(
                    parts[1], parts[2], parts[3], parts[4],
                    std::stoi(parts[5]));
                digital->setAvailableCopies(std::stoi(parts[6]));
                resource = digital;
            }
            else {
                return false;
            }
        }
        catch (...) {
            return false;
        }

        loadedResources.push_back(resource);
    }

    resources = std::move(loadedResources);
    return true;
}

bool LibrarySystem::saveUsers(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& user : users) {
        if (user != nullptr) {
            file << user->getRole() << "|"
                << user->getId() << "|"
                << user->getName() << "|"
                << user->getDepartment() << "|"
                << user->getMaxBorrowCount() << '\n';
        }
    }

    return true;
}

bool LibrarySystem::loadUsers(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::vector<std::shared_ptr<User>> loadedUsers;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        const auto parts = split(line);
        int maxBorrowCount = 0;

        if (parts.size() != 5 || !parseInteger(parts[4], maxBorrowCount)) {
            return false;
        }

        if (parts[0] == "Student") {
            loadedUsers.push_back(std::make_shared<Student>(
                parts[1], parts[2], parts[3], maxBorrowCount));
        }
        else if (parts[0] == "Teacher") {
            loadedUsers.push_back(std::make_shared<Teacher>(
                parts[1], parts[2], parts[3], maxBorrowCount));
        }
        else {
            return false;
        }
    }

    users = std::move(loadedUsers);
    return true;
}

bool LibrarySystem::saveRecords(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& record : records) {
        file << record.getUserId() << "|"
            << record.getIsbn() << "|"
            << record.getBorrowDate() << "|"
            << record.getReturnDate() << "|"
            << (record.isReturned() ? "1" : "0") << '\n';
    }

    return true;
}

bool LibrarySystem::loadRecords(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::vector<BorrowRecord> loadedRecords;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        const auto parts = split(line);
        if (parts.size() != 5) {
            return false;
        }

        BorrowRecord record(parts[0], parts[1], parts[2]);
        if (parts[4] == "1") {
            record.markReturned(parts[3]);
        }
        else if (parts[4] != "0") {
            return false;
        }

        loadedRecords.push_back(record);
    }

    records = std::move(loadedRecords);
    return true;
}
