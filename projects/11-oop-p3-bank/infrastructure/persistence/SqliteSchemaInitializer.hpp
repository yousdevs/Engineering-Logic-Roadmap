#pragma once

#include <memory>

#include "infrastructure/persistence/SqliteConnection.hpp"

// Runs CREATE TABLE IF NOT EXISTS for every table on startup.
// Idempotent - safe to call on every launch.
// Schema changes require a migration script - this only handles initial creation.

class SqliteSchemaInitializer {

    public:

        static void initialize(SqliteConnection& conn);
};