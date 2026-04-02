#pragma once

#include <string>

class IPasswordHasher {

    public:

        virtual ~IPasswordHasher() = default;

        virtual bool verify(const std::string& password, const std::string& hash) = 0;

        virtual std::string hash(const std::string& password) = 0;
};