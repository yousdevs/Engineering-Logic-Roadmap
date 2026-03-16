#pragma once

#include <string>

#include "application/ports/IPasswordHasher.hpp"

class SimplePasswordHasher : public IPasswordHasher {

    public:

        std::string hash(const std::string& password) override;

        bool verify(const std::string& password, const std::string& passwordHash) override;
};