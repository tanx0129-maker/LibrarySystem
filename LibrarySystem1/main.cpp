#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "LibrarySystem.h"
#include "Student.h"
#include "Teacher.h"

std::string inputLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int inputInt(const std::string& prompt) {
    while (true) {
        std::string text = inputLine(prompt);

        try {
            size_t position = 0;
            int value = std::stoi(text, &position);

            if (position == text.size()) {
                return value;
            }
        }
        catch (...) {
        }

        std::cout << "请输入有效数字。\n";
    }
}

void listBooks(const LibrarySystem& library) {
    const auto& books = library.getBooks();

    if (books.empty()) {
        std::cout << "暂无图书。\n";
        return;
    }

    for (const auto& book : books) {
        std::cout << book.getIsbn() << " | "
            << book.getTitle() << " | "
            << book.getAuthor() << " | "
            << book.getPublisher() << " | "
            << (book.isAvailable() ? "可借" : "已借出")
            << '\n';
    }
}

void saveAll(LibrarySystem& library) {
    library.saveBooks("books.txt");
    library.saveUsers("users.txt");
    library.saveRecords("records.txt");
    std::cout << "数据保存完成。\n";
}

int main() {
    LibrarySystem library;

    library.loadBooks("books.txt");
    library.loadUsers("users.txt");
    library.loadRecords("records.txt");

    while (true) {
        std::cout << "\n===== 图书管理系统 =====\n";
        std::cout << "1. 查看图书\n";
        std::cout << "2. 添加图书\n";
        std::cout << "3. 查询图书\n";
        std::cout << "4. 修改图书\n";
        std::cout << "5. 删除图书\n";
        std::cout << "6. 添加用户\n";
        std::cout << "7. 借书\n";
        std::cout << "8. 还书\n";
        std::cout << "9. 查询逾期和罚款\n";
        std::cout << "10. 保存数据\n";
        std::cout << "0. 保存并退出\n";

        int choice = inputInt("请选择操作：");

        if (choice == 0) {
            saveAll(library);
            break;
        }

        switch (choice) {
        case 1:
            listBooks(library);
            break;

        case 2: {
            std::string isbn = inputLine("ISBN：");
            std::string title = inputLine("书名：");
            std::string author = inputLine("作者：");
            std::string publisher = inputLine("出版社：");

            if (library.addBook(Book(isbn, title, author, publisher))) {
                std::cout << "添加成功。\n";
            }
            else {
                std::cout << "添加失败，ISBN可能已存在。\n";
            }
            break;
        }

        case 3: {
            std::string isbn = inputLine("请输入ISBN：");
            Book* book = library.searchBook(isbn);

            if (book == nullptr) {
                std::cout << "未找到图书。\n";
            }
            else {
                std::cout << book->getTitle() << " | "
                    << book->getAuthor() << " | "
                    << (book->isAvailable() ? "可借" : "已借出")
                    << '\n';
            }
            break;
        }

        case 4: {
            std::string isbn = inputLine("ISBN：");
            std::string title = inputLine("新书名：");
            std::string author = inputLine("新作者：");
            std::string publisher = inputLine("新出版社：");

            std::cout << (library.updateBook(
                isbn, title, author, publisher)
                ? "修改成功。\n" : "修改失败。\n");
            break;
        }

        case 5: {
            std::string isbn = inputLine("请输入ISBN：");

            std::cout << (library.deleteBook(isbn)
                ? "删除成功。\n"
                : "删除失败，图书不存在或正在借出。\n");
            break;
        }

        case 6: {
            int type = inputInt("1-学生，2-教师：");
            std::string id = inputLine("用户编号：");
            std::string name = inputLine("姓名：");
            std::string department = inputLine("院系：");
            int maxBorrowCount = inputInt("最大借阅数量：");

            std::shared_ptr<User> user;

            if (type == 1) {
                user = std::make_shared<Student>(
                    id, name, department, maxBorrowCount);
            }
            else if (type == 2) {
                user = std::make_shared<Teacher>(
                    id, name, department, maxBorrowCount);
            }
            else {
                std::cout << "用户类型错误。\n";
                break;
            }

            std::cout << (library.addUser(user)
                ? "用户添加成功。\n"
                : "用户添加失败。\n");
            break;
        }

        case 7: {
            std::string userId = inputLine("用户编号：");
            std::string isbn = inputLine("ISBN：");
            std::string date = inputLine("借书日期（YYYY-MM-DD）：");

            std::cout << (library.borrowBook(userId, isbn, date)
                ? "借书成功。\n" : "借书失败。\n");
            break;
        }

        case 8: {
            std::string userId = inputLine("用户编号：");
            std::string isbn = inputLine("ISBN：");
            std::string date = inputLine("还书日期（YYYY-MM-DD）：");

            std::cout << (library.returnBook(userId, isbn, date)
                ? "还书成功。\n" : "还书失败。\n");
            break;
        }

        case 9: {
            std::string userId = inputLine("用户编号：");
            std::string isbn = inputLine("ISBN：");
            std::string date = inputLine("查询日期（YYYY-MM-DD）：");

            bool overdue =
                library.isOverdue(userId, isbn, date);

            double fine =
                library.calculateFine(userId, isbn, date);

            std::cout << "是否逾期："
                << (overdue ? "是" : "否") << '\n';
            std::cout << "罚款金额：" << fine << " 元\n";
            break;
        }

        case 10:
            saveAll(library);
            break;

        default:
            std::cout << "无效选项。\n";
        }
    }

    return 0;
}