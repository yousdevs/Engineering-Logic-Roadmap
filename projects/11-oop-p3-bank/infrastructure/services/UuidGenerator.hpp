#pragma once

#include <string>

#include "domain/ports/IIdGenerator.hpp"

// Generates RFC-4122 UUID v4 strings.
// Swap with SnowflakeIdGenerator for sortable IDs in high-throughput systems.

class UuidGenerator : public IIdGenerator {

    public:

        std::string generate() override;
};