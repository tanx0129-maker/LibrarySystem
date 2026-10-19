#define _CRT_SECURE_NO_WARNINGS

#include "Magazine.h"

#include <sstream>

Magazine::Magazine(const std::string& id,
    const std::string& title,
    const std::string& editor,
    const std::string& issue,
    int totalCopies)
    : LibraryResource(id, title, totalCopies),
    editor(editor),
    issue(issue) {
}

const std::string& Magazine::getEditor() const {
    return editor;
}

const std::string& Magazine::getIssue() const {
    return issue;
}

std::string Magazine::getType() const {
    return "Magazine";
}

std::string Magazine::displayInfo() const {
    std::ostringstream output;
    output << "[杂志] " << id << " | " << title
        << " | 编辑: " << editor
        << " | 期号: " << issue
        << " | 可借 " << availableCopies << "/" << totalCopies;
    return output.str();
}

std::string Magazine::serialize() const {
    std::ostringstream output;
    output << getType() << "|" << id << "|" << title << "|"
        << editor << "|" << issue << "|"
        << totalCopies << "|" << availableCopies;
    return output.str();
}

void Magazine::update(const std::string& newTitle,
    const std::string& newEditor,
    const std::string& newIssue) {
    title = newTitle;
    editor = newEditor;
    issue = newIssue;
}
