#pragma once

#include "domain/value_objects/PinCode.hpp"

class IPinCodeGenerator {

    public:

        // PinCode::from already enforce all invariants
        virtual PinCode generate() = 0;

        virtual ~IPinCodeGenerator() = default;
};