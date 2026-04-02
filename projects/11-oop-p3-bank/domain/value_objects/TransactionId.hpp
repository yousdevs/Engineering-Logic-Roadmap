#pragma once

#include <stdexcept>
#include <string>

#include "domain/ports/IIdGenerator.hpp"

class TransactionId {

    private:

        std::string _value;

    public:

        static TransactionId generate(IIdGenerator& generator) {
            return TransactionId(generator.generate());
        }

        static TransactionId from(const std::string& value) {
            if (value.empty())
                throw std::invalid_argument("TransactionId cannot be empty");
            return TransactionId(value);
        }

        const std::string& value() const {
            return _value;
        }

    private:

        explicit TransactionId(std::string value) : _value(std::move(value)) {}
};