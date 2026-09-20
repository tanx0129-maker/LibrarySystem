#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"
#include "Student.h"
#include "Teacher.h"

int main() {
    Book book(
        "978001",
        "C++程序设计",
        "刘畅",
        "高等教育出版社"
    );

    Student student("S001", "StudentA", "Computer", 5);
    Teacher teacher("T001", "TeacherA", "Computer", 10);

    std::cout << student.getRole() << ": "
        << student.getName() << std::endl;

    std::cout << teacher.getRole() << ": "
        << teacher.getName() << std::endl;

    std::cout << "书名：" << book.getTitle() << std::endl;
    std::cout << "作者：" << book.getAuthor() << std::endl;
    std::cout << "是否可借："
              << (book.isAvailable() ? "是" : "否")
              << std::endl;

    return 0;
}