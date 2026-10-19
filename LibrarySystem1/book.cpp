#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"

#include <sstream>

Book::Book(const std::string& isbn,
    const std::string& title,
    const std::string& author,
    const std::string& publisher,
    int totalCopies)
    : LibraryResource(isbn, title, totalCopies),
    author(author),
    publisher(publisher) {
}

const std::string& Book::getAuthor() const {
    return author;
}

const std::string& Book::getPublisher() const {
    return publisher;
}

void Book::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Book::setAuthor(const std::string& newAuthor) {
    author = newAuthor;
}

void Book::setPublisher(const std::string& newPublisher) {
    publisher = newPublisher;
}

std::string Book::getType() const {
    return "Book";
}

std::string Book::displayInfo() const {
    std::ostringstream output;
    output << "[图书] " << id << " | " << title
        << " | 作者: " << author
        << " | 出版社: " << publisher
        << " | 可借 " << availableCopies << "/" << totalCopies;
    return output.str();
}

std::string Book::serialize() const {
    std::ostringstream output;
    output << getType() << "|" << id << "|" << title << "|"
        << author << "|" << publisher << "|"
        << totalCopies << "|" << availableCopies;
    return output.str();
}

void Book::update(const std::string& newTitle,
    const std::string& newAuthor,
    const std::string& newPublisher) {
    setTitle(newTitle);
    setAuthor(newAuthor);
    setPublisher(newPublisher);
}
