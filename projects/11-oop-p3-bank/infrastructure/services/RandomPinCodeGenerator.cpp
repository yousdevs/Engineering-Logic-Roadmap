#include "infrastructure/services/RandomPinCodeGenerator.hpp"

#include <iomanip>
#include <random>
#include <sstream>
#include <stdexcept>

PinCode RandomPinCodeGenerator::generate() {

    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(1, 9999);  // 0 = "0000" always forbidden

    // Retry until a valid pin is produced - forbidden values are rare (<2%).
    for (int attempts = 0; attempts < 100; ++attempts) {

        std::ostringstream ss;
        ss << std::setw(4) << std::setfill('0') << dis(gen);

        try {
            return PinCode::from(ss.str());  // PinCode enforces all invariants
        } catch (const std::invalid_argument&) {
            continue;                        // forbidden value - retry
        }
    }

    throw std::runtime_error(
        "RandomPinCodeGenerator: failed to generate valid PinCode after 100 attempts.");
}