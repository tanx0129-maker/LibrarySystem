#pragma once

#include <string>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string publisher;
    bool available;

public:
    Book(const std::string& isbn,
        const std::string& title,
        const std::string& author,
        const std::string& publisher);

    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;

    bool isAvailable() const;
    void setAvailable(bool available);
};
