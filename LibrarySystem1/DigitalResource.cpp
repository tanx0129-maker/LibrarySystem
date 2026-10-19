#define _CRT_SECURE_NO_WARNINGS

#include "DigitalResource.h"

#include <sstream>

DigitalResource::DigitalResource(const std::string& id,
    const std::string& title,
    const std::string& format,
    const std::string& url,
    int totalCopies)
    : LibraryResource(id, title, totalCopies),
    format(format),
    url(url) {
}

const std::string& DigitalResource::getFormat() const {
    return format;
}

const std::string& DigitalResource::getUrl() const {
    return url;
}

std::string DigitalResource::getType() const {
    return "Digital";
}

std::string DigitalResource::displayInfo() const {
    std::ostringstream output;
    output << "[电子资源] " << id << " | " << title
        << " | 格式: " << format
        << " | 地址: " << url
        << " | 可借 " << availableCopies << "/" << totalCopies;
    return output.str();
}

std::string DigitalResource::serialize() const {
    std::ostringstream output;
    output << getType() << "|" << id << "|" << title << "|"
        << format << "|" << url << "|"
        << totalCopies << "|" << availableCopies;
    return output.str();
}

void DigitalResource::update(const std::string& newTitle,
    const std::string& newFormat,
    const std::string& newUrl) {
    title = newTitle;
    format = newFormat;
    url = newUrl;
}
