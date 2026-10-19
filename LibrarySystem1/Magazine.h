#pragma once

#include "LibraryResource.h"

class Magazine : public LibraryResource {
private:
    std::string editor;
    std::string issue;

public:
    Magazine(const std::string& id,
        const std::string& title,
        const std::string& editor,
        const std::string& issue,
        int totalCopies = 1);

    const std::string& getEditor() const;
    const std::string& getIssue() const;

    std::string getType() const override;
    std::string displayInfo() const override;
    std::string serialize() const override;
    void update(const std::string& title,
        const std::string& editor,
        const std::string& issue) override;
};
