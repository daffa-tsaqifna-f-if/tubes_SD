#pragma once

#include <string>

namespace input {
    // Reads a full line (can be empty).
    std::string line(const std::string& prompt);

    // Reads an int with validation.
    int integer(const std::string& prompt);

    // Reads a double with validation.
    double number(const std::string& prompt);
}
