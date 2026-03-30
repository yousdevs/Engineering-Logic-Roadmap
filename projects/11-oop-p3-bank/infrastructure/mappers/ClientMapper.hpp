#pragma once
#include <cstdint>

#include "domain/entities/Client.hpp"

#include "infrastructure/persistence/Row.hpp"

// Translates Client <-> Row.
// Column names are string literals here and Only here.
// Migration: new required field -> get<T>(); new optional field -> getOr<T>().

class ClientMapper {

    public:

        static Client toDomain(const Row& row);

        static Row toPersistence(const Client& client);
};