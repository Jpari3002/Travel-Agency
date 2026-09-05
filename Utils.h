#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>

namespace Utils {

// Splits "a|b|c" into {"a","b","c"} on the given delimiter.
inline std::vector<std::string> split(const std::string& line, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

// Joins a vector of ints back into "1,2,3" for saving to disk.
inline std::string joinIds(const std::vector<int>& ids) {
    std::stringstream ss;
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i > 0) ss << ",";
        ss << ids[i];
    }
    return ss.str();
}

// Reverses joinIds().
inline std::vector<int> splitIds(const std::string& csv) {
    std::vector<int> ids;
    if (csv.empty()) return ids;
    std::stringstream ss(csv);
    std::string item;
    while (std::getline(ss, item, ',')) {
        if (!item.empty()) ids.push_back(std::stoi(item));
    }
    return ids;
}

} // namespace Utils

#endif
