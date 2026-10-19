#pragma once

#include <string>

class LibraryResource {
protected:
    std::string id;
    std::string title;
    int totalCopies;
    int availableCopies;

    LibraryResource(const std::string& id,
        const std::string& title,
        int totalCopies = 1);

public:
    virtual ~LibraryResource() = default;

    const std::string& getId() const;
    const std::string& getIsbn() const;
    const std::string& getTitle() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;
    bool isAvailable() const;

    bool borrowCopy();
    bool returnCopy();
    void setAvailable(bool available);
    bool setQuantity(int quantity);
    void setAvailableCopies(int available);

    virtual std::string getType() const = 0;
    virtual std::string displayInfo() const = 0;
    virtual std::string serialize() const = 0;
    virtual void update(const std::string& title,
        const std::string& creator,
        const std::string& detail) = 0;
};
