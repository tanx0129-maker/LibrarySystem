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

    return 0;
}