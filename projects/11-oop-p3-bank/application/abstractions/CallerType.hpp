#pragma once

// Who is making the request and wich caller types a use case accepts.
// CallerType::ATM and CallerPolicy::ATMOnly exist now so future
// ATM integration requires zero changes to this enum.

enum class CallerType {
    WebClient,        // browser / mobile app - session or JWT auth
    ATM,              // physical terminsal - future integration
    InternalService,  // scheduler / background worker
    PublicApi,        // unauthenticated public endpoint
};

enum class CallerPolicy {
    AnyAuthenticated,  // requires Login, any CallerType
    PublicOnly,        // must be unauthenticated
    AnyCallerType,     // no restriction
    ATMOnly,           // future - reserverd for ATM use cases
};