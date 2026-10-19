#pragma once

#include <cstddef>
#include <vector>

template <typename T>
std::size_t countItems(const std::vector<T>& items) {
    return items.size();
}
