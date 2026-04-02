#include "infrastructure/services/InMemoryCurrencyRateService.hpp"

std::optional<CurrencyRate> InMemoryCurrencyRateService::getRate(const std::string& from,
                                                                 const std::string& to) {

    std::lock_guard<std::mutex> lock(_mutex);
    const std::string           key = from + ":" + to;
    auto                        it  = _rates.find(key);
    if (it == _rates.end())
        return std::nullopt;

    return it->second;
}

void InMemoryCurrencyRateService::updateRate(const CurrencyRate& rate) {

    std::lock_guard<std::mutex> lock(_mutex);
    _rates[rate.from + ":" + rate.to] = rate;
}