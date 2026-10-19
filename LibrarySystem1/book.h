#pragma once

#include "LibraryResource.h"

class Book : public LibraryResource {
private:
    std::string author;
    std::string publisher;

public:
    Book(const std::string& isbn,
        const std::string& title,
        const std::string& author,
        const std::string& publisher,
        int totalCopies = 1);

    const std::string& getAuthor() const;
    const std::string& getPublisher() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setPublisher(const std::string& publisher);

    std::string getType() const override;
    std::string displayInfo() const override;
    std::string serialize() const override;
    void update(const std::string& title,
        const std::string& author,
        const std::string& publisher) override;
};
