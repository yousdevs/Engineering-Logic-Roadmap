#include "infrastructure/services/UuidGenerator.hpp"

#include <iomanip>
#include <random>
#include <sstream>

std::string UuidGenerator::generate() {

    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::uniform_int_distribution<> dis2(8, 11);  // variant bits

    std::ostringstream ss;
    ss << std::hex;

    for (int i = 0; i < 8; ++i)
        ss << dis(gen);

    ss << '-';

    for (int i = 0; i < 4; ++i)
        ss << dis(gen);

    ss << "-4";  // version 4

    for (int i = 0; i < 3; ++i)
        ss << dis(gen);

    ss << '-' << dis2(gen);

    for (int i = 0; i < 3; ++i)
        ss << dis(gen);

    ss << '-';

    for (int i = 0; i < 12; ++i)
        ss << dis(gen);

    return ss.str();
}