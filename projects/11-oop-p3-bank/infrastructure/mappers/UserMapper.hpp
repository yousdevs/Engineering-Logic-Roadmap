#pragma once

#include "domain/entities/User.hpp"

#include "infrastructure/persistence/Row.hpp"

class UserMapper {

    public:

        static User toDomain(const Row& row);

        static Row toPersistence(const User& user);
};
