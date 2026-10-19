#pragma once

#include "LibraryResource.h"

class DigitalResource : public LibraryResource {
private:
    std::string format;
    std::string url;

public:
    DigitalResource(const std::string& id,
        const std::string& title,
        const std::string& format,
        const std::string& url,
        int totalCopies = 1);

    const std::string& getFormat() const;
    const std::string& getUrl() const;

    std::string getType() const override;
    std::string displayInfo() const override;
    std::string serialize() const override;
    void update(const std::string& title,
        const std::string& format,
        const std::string& url) override;
};
