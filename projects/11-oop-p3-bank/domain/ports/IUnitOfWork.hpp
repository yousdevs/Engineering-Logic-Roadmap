#pragma once

// IUnitOfWork - domain port for transaction management.
// Abstracts the database transaction lifecycle.
// called by TransactionInterceptor - usecases don't touch transactions directly.
// scope:
// One IUnitOfWork instance per request
// Created by the composition root
// Injected into TransactionInterceptor
//
// What 'commit' means here:
// Flushes all repository changes made during this request
// - domain entities AND outbox entries - in one atomic
// database commit. This is the outbox guarantee:
// entities saved <-> events recorded, same commit.

class IUnitOfWork {

    public:

        virtual void begin() = 0;

        virtual void commit() = 0;

        virtual void rollback() = 0;

        virtual ~IUnitOfWork() = default;
};