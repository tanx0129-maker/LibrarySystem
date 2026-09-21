#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>

#include "LibrarySystem.h"
#include "Student.h"

int main() {
    LibrarySystem library;

    Book book(
        "978001",
        "C++程序设计",
        "刘畅",
        "高等教育出版社"
    );

    auto student = std::make_shared<Student>(
        "S001",
        "StudentA",
        "Computer",
        5
    );

    library.addBook(book);
    library.addUser(student);

    bool borrowResult =
        library.borrowBook("S001", "978001", "2026-09-21");

    std::cout << "Borrow result: "
        << (borrowResult ? "success" : "failed")
        << std::endl;

    bool returnResult =
        library.returnBook("S001", "978001", "2026-09-25");

    std::cout << "Return result: "
        << (returnResult ? "success" : "failed")
        << std::endl;

    if (library.saveBooks("books.txt")) {
        std::cout << "Books saved successfully." << std::endl;
    }
    if (library.saveUsers("users.txt")) {
        std::cout << "Users saved successfully." << std::endl;
    }
    if (library.saveRecords("records.txt")) {
        std::cout << "Records saved successfully." << std::endl;
    }

    LibrarySystem newLibrary;

    if (newLibrary.loadBooks("books.txt")) {
        std::cout << "Books loaded successfully." << std::endl;
    }
    if (newLibrary.loadUsers("users.txt")) {
        std::cout << "Users loaded successfully." << std::endl;
    }
    if (newLibrary.loadRecords("records.txt")) {
        std::cout << "Records loaded successfully." << std::endl;
    }

    Book* foundBook = library.searchBook("978001");

    if (foundBook != nullptr) {
        std::cout << "Found book: "
            << foundBook->getTitle()
            << std::endl;
    }

    if (library.updateBook(
        "978001",
        "C++高级程序设计",
        "刘畅",
        "高等教育出版社")) {
        std::cout << "Book updated successfully." << std::endl;
    }

    library.borrowBook("S001", "978001", "2026-01-01");

    std::cout << library.isOverdue(
        "S001", "978001", "2026-02-10") << std::endl;

    std::cout << library.calculateFine(
        "S001", "978001", "2026-02-10");

    return 0;
}