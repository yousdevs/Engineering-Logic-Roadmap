#pragma once

#include "domain/ports/IPasswordHasher.hpp"

// Test-only hasher - stores passwords as-is for readable test assertions

class PlainTextHasher : public IPasswordHasher {

    public:

        std::string hash(const std::string& plainText) override {
            return plainText;
        }

        bool verify(const std::string& plainText, const std::string& storedHash) override {
            return plainText == storedHash;
        }
};