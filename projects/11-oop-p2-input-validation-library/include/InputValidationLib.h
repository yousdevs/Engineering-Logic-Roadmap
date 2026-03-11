#pragma once

#include <iostream>
#include <string>
#include <limits>

class InputValidationLib {

public:

    // Numeric Validation

    template<typename T>
    static bool isNumberInRange(T value, T min, T max);


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