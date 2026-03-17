#pragma once

#include <string>

#include "domain/ports/IIdGenerator.hpp"

class SequentialIdGenerator : public IIdGenerator {

    private:

        int _counter = 0;

    public:

        std::string generate() override {

            return "test-id-" + std::to_string(++_counter);
        }
};