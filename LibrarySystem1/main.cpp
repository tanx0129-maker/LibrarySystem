#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "CollectionUtils.h"
#include "DigitalResource.h"
#include "LibrarySystem.h"
#include "Magazine.h"
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
        const std::string text = inputLine(prompt);

        try {
            size_t position = 0;
            const int value = std::stoi(text, &position);
            if (position == text.size()) {
                return value;
            }
        }
        catch (...) {
        }

        std::cout << "请输入有效整数。\n";
    }
}

void listResources(const LibrarySystem& library) {
    const auto& resources = library.getResources();

    std::cout << "资源总数：" << countItems(resources) << "\n";
    if (resources.empty()) {
        std::cout << "当前没有资源。\n";
        return;
    }

    for (const auto& resource : resources) {
        if (resource != nullptr) {
            // 基类指针调用虚函数，体现运行时多态。
            std::cout << resource->displayInfo() << '\n';
        }
    }
}

void listUsers(const LibrarySystem& library) {
    const auto& users = library.getUsers();
    std::cout << "用户总数：" << countItems(users) << "\n";

    for (const auto& user : users) {
        if (user != nullptr) {
            std::cout << user->getRole() << " | "
                << user->getId() << " | "
                << user->getName() << " | "
                << user->getDepartment() << " | 最大借阅："
                << user->getMaxBorrowCount() << '\n';
        }
    }
}

void saveAll(const LibrarySystem& library) {
    const bool resourcesSaved = library.saveBooks("books.txt");
    const bool usersSaved = library.saveUsers("users.txt");
    const bool recordsSaved = library.saveRecords("records.txt");

    if (resourcesSaved && usersSaved && recordsSaved) {
        std::cout << "资源、用户和借阅记录保存成功。\n";
    }
    else {
        std::cout << "保存失败，请检查文件路径和权限。\n";
    }
}

std::shared_ptr<LibraryResource> createResourceFromInput() {
    const int type = inputInt("资源类型（1-图书，2-杂志，3-电子资源）：");
    const std::string id = inputLine("资源编号/ISBN：");
    const std::string title = inputLine("标题：");
    const int quantity = inputInt("资源数量：");

    if (type == 1) {
        const std::string author = inputLine("作者：");
        const std::string publisher = inputLine("出版社：");
        return std::make_shared<Book>(
            id, title, author, publisher, quantity);
    }

    if (type == 2) {
        const std::string editor = inputLine("编辑：");
        const std::string issue = inputLine("期号：");
        return std::make_shared<Magazine>(
            id, title, editor, issue, quantity);
    }

    if (type == 3) {
        const std::string format = inputLine("文件格式：");
        const std::string url = inputLine("访问地址：");
        return std::make_shared<DigitalResource>(
            id, title, format, url, quantity);
    }

    std::cout << "资源类型不存在。\n";
    return nullptr;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    LibrarySystem library;
    library.loadBooks("books.txt");
    library.loadUsers("users.txt");
    library.loadRecords("records.txt");

    while (true) {
        std::cout << "\n===== 图书馆借阅管理系统 =====\n"
            << "1. 查看所有资源\n"
            << "2. 添加资源\n"
            << "3. 查询资源\n"
            << "4. 修改资源\n"
            << "5. 删除资源\n"
            << "6. 添加用户\n"
            << "7. 查看用户\n"
            << "8. 借阅资源\n"
            << "9. 归还资源\n"
            << "10. 查询逾期和罚款\n"
            << "11. 保存数据\n"
            << "12. 修改资源数量\n"
            << "13. 修改用户信息\n"
            << "0. 保存并退出\n";

        const int choice = inputInt("请选择操作：");

        if (choice == 0) {
            saveAll(library);
            break;
        }

        switch (choice) {
        case 1:
            listResources(library);
            break;

        case 2: {
            auto resource = createResourceFromInput();
            std::cout << (library.addResource(resource)
                ? "资源添加成功。\n"
                : "资源添加失败，编号可能已存在。\n");
            break;
        }

        case 3: {
            const std::string id = inputLine("请输入资源编号/ISBN：");
            const LibraryResource* resource = library.searchResource(id);
            std::cout << (resource == nullptr
                ? "未找到资源。\n"
                : resource->displayInfo() + "\n");
            break;
        }

        case 4: {
            const std::string id = inputLine("请输入资源编号/ISBN：");
            LibraryResource* resource = library.searchResource(id);
            if (resource == nullptr) {
                std::cout << "未找到资源。\n";
                break;
            }

            const std::string title = inputLine("新标题：");
            std::string creator;
            std::string detail;
            if (resource->getType() == "Book") {
                creator = inputLine("新作者：");
                detail = inputLine("新出版社：");
            }
            else if (resource->getType() == "Magazine") {
                creator = inputLine("新编辑：");
                detail = inputLine("新期号：");
            }
            else {
                creator = inputLine("新文件格式：");
                detail = inputLine("新访问地址：");
            }

            std::cout << (library.updateResource(id, title, creator, detail)
                ? "资源修改成功。\n"
                : "资源修改失败。\n");
            break;
        }

        case 5: {
            const std::string id = inputLine("请输入资源编号/ISBN：");
            std::cout << (library.deleteResource(id)
                ? "资源删除成功。\n"
                : "资源删除失败，资源不存在或仍有借阅。\n");
            break;
        }

        case 6: {
            const int type = inputInt("用户类型（1-学生，2-教师）：");
            const std::string id = inputLine("用户编号：");
            const std::string name = inputLine("姓名：");
            const std::string department = inputLine("院系：");
            const int maxBorrowCount = inputInt("最大借阅数量：");

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
                std::cout << "用户类型不存在。\n";
                break;
            }

            std::cout << (library.addUser(user)
                ? "用户添加成功。\n"
                : "用户添加失败，编号可能已存在。\n");
            break;
        }

        case 7:
            listUsers(library);
            break;

        case 8: {
            const std::string userId = inputLine("用户编号：");
            const std::string resourceId = inputLine("资源编号/ISBN：");
            const std::string date = inputLine("借阅日期（YYYY-MM-DD）：");
            std::cout << (library.borrowBook(userId, resourceId, date)
                ? "借阅成功。\n" : "借阅失败，请检查用户、资源状态或借阅上限。\n");
            break;
        }

        case 9: {
            const std::string userId = inputLine("用户编号：");
            const std::string resourceId = inputLine("资源编号/ISBN：");
            const std::string date = inputLine("归还日期（YYYY-MM-DD）：");
            std::cout << (library.returnBook(userId, resourceId, date)
                ? "归还成功。\n" : "归还失败，请检查借阅记录。\n");
            break;
        }

        case 10: {
            const std::string userId = inputLine("用户编号：");
            const std::string resourceId = inputLine("资源编号/ISBN：");
            const std::string date = inputLine("查询日期（YYYY-MM-DD）：");
            const bool overdue = library.isOverdue(
                userId, resourceId, date);
            const double fine = library.calculateFine(
                userId, resourceId, date);
            std::cout << "是否逾期：" << (overdue ? "是" : "否") << '\n'
                << "罚款金额：" << fine << " 元\n";
            break;
        }

        case 11:
            saveAll(library);
            break;

        case 12: {
            const std::string id = inputLine("请输入资源编号/ISBN：");
            const int quantity = inputInt("请输入新的资源总数量：");
            std::cout << (library.changeResourceQuantity(id, quantity)
                ? "资源数量修改成功。\n"
                : "资源数量修改失败，数量不能小于当前借出数量。\n");
            break;
        }

        case 13: {
            const std::string id = inputLine("用户编号：");
            const std::string name = inputLine("新姓名：");
            const std::string department = inputLine("新院系：");
            const int maxBorrowCount = inputInt("新的最大借阅数量：");
            std::cout << (library.updateUser(
                id, name, department, maxBorrowCount)
                ? "用户信息修改成功。\n"
                : "用户信息修改失败。\n");
            break;
        }

        default:
            std::cout << "无效选项。\n";
        }
    }

    return 0;
}
