#pragma once

#include <string>

class IIdGenerator {

    public:

        virtual std::string generate() = 0;
        virtual ~IIdGenerator()        = default;
};