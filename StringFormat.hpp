#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

inline std::wstring formatFloat(float value, int precision = 1, const std::wstring& unit = L"") {
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    if (!unit.empty()) ss << L" " << unit;
    return ss.str();
}

inline std::wstring formatInt(int value, const std::wstring& unit = L"") {
    std::wstringstream ss;
    ss << value;
    if (!unit.empty()) ss << L" " << unit;
    return ss.str();
}

inline std::wstring formatRoundedInt(float value, const std::wstring& unit = L"") {
    std::wstringstream ss;
    ss << static_cast<int>(std::round(value));
    if (!unit.empty()) ss << L" " << unit;
    return ss.str();
}
