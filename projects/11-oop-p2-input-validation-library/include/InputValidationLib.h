#pragma once

#include <iostream>
#include <string>
#include <limits>

class InputValidationLib {

public:

    // Numeric Validation

    template<typename T>
    static bool isNumberInRange(T value, T min, T max);

    static bool isInteger(const std::string& str);

    static bool isDouble(const std::string& str);

    // Numeric Input

    static int readInt(
        const std::string& errorMessage = "Invalid number, try again.\n"
    );

    static int readIntInRange(
        int min,
        int max,
        const std::string& errorMessage = "Number out of range.\n"
    );

    static double readDouble(
        const std::string& errorMessage = "Invalid number, try again.\n"
    );

    static double readDoubleInRange(
        double min,
        double max,
        const std::string& errorMessage = "Number out of range.\n"
    );


    // Text Input

    static std::string readLine();


    // Yes / No Input

    static bool readYesNo(
        const std::string& message = "Enter y/n: "
    );
};

// Implementation section

// Text Input

inline std::string InputValidationLib::readLine() {
    
    std::string input;
    std::getline(std::cin >> std::ws, input);
    return input;
}

// Yes / No Input

inline bool InputValidationLib::readYesNo(const std::string& message) {

    char c;

    while (true) {

        std::cout << message;
        std::string input = InputValidationLib::readLine();
        if (!input.empty())
            c = input[0];

        c = std::tolower(c);

        if (c == 'y') return true;
        if (c == 'n') return false;

        std::cout << "Invalid input.\n";
    }
}


// Numeric Validation

template<typename T>
inline bool InputValidationLib::isNumberInRange(T value, T min, T max) {
    return value >= min && value <= max;
}

inline bool InputValidationLib::isInteger(const std::string& str) {
    
    if (str.empty()) return false;

    try {
        size_t pos;
        std::stoi(str, &pos);

        // ensure the whole string was parsed
        return pos == str.length();
    }
    catch (...) {
        return false;
    }
}

inline bool InputValidationLib::isDouble(const std::string& str) {
    
    if (str.empty()) return false;

    try {
        size_t pos;
        std::stod(str, &pos);

        return pos == str.length();
    }
    catch (...) {
        return false;
    }
}

