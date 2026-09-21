#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"

Book::Book(const std::string& isbn,
    const std::string& title,
    const std::string& author,
    const std::string& publisher)
    : isbn(isbn),
    title(title),
    author(author),
    publisher(publisher),
    available(true) {
}

std::string Book::getIsbn() const {
    return isbn;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getPublisher() const {
    return publisher;
}

bool Book::isAvailable() const {
    return available;
}

void Book::setAvailable(bool available) {
    this->available = available;
}

void Book::setTitle(const std::string& title) {
    this->title = title;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setPublisher(const std::string& publisher) {
    this->publisher = publisher;
}