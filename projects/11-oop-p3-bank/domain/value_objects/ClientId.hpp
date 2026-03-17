#pragma once

#include <stdexcept>
#include <string>

#include "domain/ports/IIdGenerator.hpp"

class ClientId {

    private:

        std::string _value;

    public:

        static ClientId generate(IIdGenerator& generator) {
            return ClientId(generator.generate());
        }

        static ClientId from(const std::string& value) {
            if (value.empty())
                throw std::invalid_argument("ClientId cannot be empty");
            return ClientId(value);
        }

        const std::string& value() const {
            return _value;
        }

    private:

        explicit ClientId(std::string value) : _value(std::move(value)) {}
};