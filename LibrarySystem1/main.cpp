#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"
#include "Student.h"
#include "Teacher.h"
#include "BorrowRecord.h"

int main() {
    Book book(
        "978001",
        "C++程序设计",
        "刘畅",
        "高等教育出版社"
    );

    Student student("S001", "StudentA", "Computer", 5);
    Teacher teacher("T001", "TeacherA", "Computer", 10);

    BorrowRecord record("S001", "978001", "2026-09-20");

    std::cout << "借阅人：" << record.getUserId() << std::endl;
    std::cout << "图书 ISBN：" << record.getIsbn() << std::endl;
    std::cout << "是否归还："
        << (record.isReturned() ? "是" : "否")
        << std::endl;

    record.markReturned("2026-09-25");

    std::cout << "归还后状态："
        << (record.isReturned() ? "已归还" : "未归还")
        << std::endl;

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