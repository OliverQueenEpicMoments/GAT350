#include "Utilities.h"
#include <algorithm>

namespace Ethrl {
    std::string ToLower(const std::string& str) {
        std::string Lower = str;
        std::transform(Lower.begin(), Lower.end(), Lower.begin(), ::tolower);

        return Lower;
    }

    std::string ToUpper(const std::string& str) {
        std::string Upper = str;
        std::transform(Upper.begin(), Upper.end(), Upper.begin(), ::toupper);

        return Upper;
    }

    bool CompareIgnoreCase(const std::string& str1, const std::string& str2) {
        return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](char c1, char c2) {
            return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
            }));
    }
}