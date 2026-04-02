#pragma once

#include <ctime>
#include <optional>
#include <string>

struct CurrencyRate {

        std::string from;
        std::string to;
        double      value;
        std::time_t timestamp;  // when this rate was fetched/cashed
};

// Currency rate query port.
// Returns cashed rates - the live feed subscription that updates
// the cashe is managed separately (IRealtimePublisher subscriber).
// Implementations: ExternalFeedRateService, InMemoryCasheRateService (dev).

// TODO: thread-safety, currency type safety, cache freshness, and timestamp precision

class ICurrencyRateService {

    public:

        virtual std::optional<CurrencyRate> getRate(const std::string& from,
                                                    const std::string& to) = 0;

        virtual ~ICurrencyRateService() = default;
};