// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

namespace utl {
    std::string timestring(long long timestamp);
    std::vector<std::pair<std::string, long long>> get_image_paths(const std::string& file_path_string);
}

#endif // UTILS_H