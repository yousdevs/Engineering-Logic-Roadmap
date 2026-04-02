#pragma once

#include <stdexcept>
#include <string>

#include "domain/ports/IIdGenerator.hpp"

class AccountId {

    private:

        std::string _value;

    public:

        static AccountId generate(IIdGenerator& generator) {
            return AccountId(generator.generate());
        }

        static AccountId from(const std::string& value) {
            if (value.empty())
                throw std::invalid_argument("AccountId cannot be empty");
            return AccountId(value);
        }

        const std::string& value() const {
            return _value;
        }

    private:

        explicit AccountId(std::string value) : _value(std::move(value)) {}
};