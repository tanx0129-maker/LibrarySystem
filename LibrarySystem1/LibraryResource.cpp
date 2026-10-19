#define _CRT_SECURE_NO_WARNINGS

#include "LibraryResource.h"

#include <algorithm>

LibraryResource::LibraryResource(const std::string& id,
    const std::string& title,
    int totalCopies)
    : id(id),
    title(title),
    totalCopies(std::max(1, totalCopies)),
    availableCopies(std::max(1, totalCopies)) {
}

const std::string& LibraryResource::getId() const {
    return id;
}

const std::string& LibraryResource::getIsbn() const {
    return id;
}

const std::string& LibraryResource::getTitle() const {
    return title;
}

int LibraryResource::getTotalCopies() const {
    return totalCopies;
}

int LibraryResource::getAvailableCopies() const {
    return availableCopies;
}

bool LibraryResource::isAvailable() const {
    return availableCopies > 0;
}

bool LibraryResource::borrowCopy() {
    if (availableCopies <= 0) {
        return false;
    }

    --availableCopies;
    return true;
}

bool LibraryResource::returnCopy() {
    if (availableCopies >= totalCopies) {
        return false;
    }

    ++availableCopies;
    return true;
}

void LibraryResource::setAvailable(bool available) {
    availableCopies = available ? totalCopies : 0;
}

bool LibraryResource::setQuantity(int quantity) {
    const int borrowedCopies = totalCopies - availableCopies;
    if (quantity < 1 || quantity < borrowedCopies) {
        return false;
    }

    totalCopies = quantity;
    availableCopies = totalCopies - borrowedCopies;
    return true;
}

void LibraryResource::setAvailableCopies(int available) {
    availableCopies = std::max(0, std::min(available, totalCopies));
}
