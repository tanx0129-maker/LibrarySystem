#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>

int main() {
    Book book(
        "978001",
        "C++程序设计",
        "刘畅",
        "高等教育出版社"
    );

    std::cout << "书名：" << book.getTitle() << std::endl;
    std::cout << "作者：" << book.getAuthor() << std::endl;
    std::cout << "是否可借："
              << (book.isAvailable() ? "是" : "否")
              << std::endl;

    return 0;
}