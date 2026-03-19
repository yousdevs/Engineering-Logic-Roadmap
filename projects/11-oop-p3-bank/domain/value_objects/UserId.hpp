#pragma once

#include <stdexcept>
#include <string>

#include "domain/ports/IIdGenerator.hpp"

class UserId {

    private:

        std::string _value;

    public:

        static UserId generate(IIdGenerator& generator) {
            return UserId(generator.generate());
        }

        static UserId from(const std::string& value) {
            if (value.empty())
                throw std::invalid_argument("UserId cannot be empty");
            return UserId(value);
        }

        const std::string& value() const {
            return _value;
        }

    private:

        explicit UserId(std::string value) : _value(std::move(value)) {}
};