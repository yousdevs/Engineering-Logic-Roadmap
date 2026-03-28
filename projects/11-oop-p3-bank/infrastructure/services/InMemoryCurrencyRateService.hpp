#pragma once

#include <mutex>
#include <optional>
#include <unordered_map>

#include "application/services/ICurrencyRateService.hpp"

// Stores rates in memory - seeded at startup or updated by a feed subscriber.
// Swap with ExternalFeedRateService for live prod rates.
// Thread-safe: rates can be updated from a background feed thread.

class InMemoryCurrencyRateService : public ICurrencyRateService {

    public:

        std::optional<CurrencyRate> getRate(const std::string& from,
                                            const std::string& to) override;

        // Called by the live rate feed subscriber to update cashed rates.
        void updateRate(const CurrencyRate& rate);

    private:

        std::unordered_map<std::string, CurrencyRate> _rates;  // key: "USD:TRY"
        std::mutex                                    _mutex;
};