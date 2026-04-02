#pragma once

#include <memory>
#include <string>

#include "application/abstractions/IUseCase.hpp"
#include "application/services/ICurrencyRateService.hpp"

struct GetCurrencyRateRequest : UseCaseRequest {

        std::string fromCurrency;
        std::string toCurrency;

        std::vector<ValidationError> validate() const override {

            std::vector<ValidationError> errors;

            if (fromCurrency.empty())
                errors.push_back({"fromCurrency", "Required."});

            if (toCurrency.empty())
                errors.push_back({"toCurrency", "Required."});

            return errors;
        }
};

struct GetCurrencyRateResponse : UseCaseResponse {

        std::string from;
        std::string to;
        double      rate;
        std::time_t rateTimestamp;

        GetCurrencyRateResponse(std::string from,
                                std::string to,
                                double      rate,
                                std::time_t rateTimestamp)
            : from(std::move(from)), to(std::move(to)), rate(rate), rateTimestamp(rateTimestamp) {}
};

// Public, read-only, rate-limited, no audit (high-frequency query).
// Returns cached rates - live updates are pushed via IRealtimePublisher
// by a separate feed subscriber, not by this use case.

class GetCurrencyRateUseCase : public IUseCase<GetCurrencyRateRequest, GetCurrencyRateResponse> {

    public:

        explicit GetCurrencyRateUseCase(std::shared_ptr<ICurrencyRateService> rateService)
            : _rateService(std::move(rateService)) {}

        UseCaseMetadata metadata() const override {

            return UseCaseMetadata::create("GetCurrencyRate")
                .asPublic()
                .readOnly()
                .withoutAudit()
                .withRateLimit();
        }

        UseCaseResult<GetCurrencyRateResponse> execute(
            const ExecutionContext& ctx, const GetCurrencyRateRequest& request) override {

            auto rate = _rateService->getRate(request.fromCurrency, request.toCurrency);

            if (!rate.has_value())
                return UseCaseResult<GetCurrencyRateResponse>::fail(AppError::notFound(
                    "No rate available for " + request.fromCurrency + "->" + request.toCurrency));

            return UseCaseResult<GetCurrencyRateResponse>::ok(
                {rate->from, rate->to, rate->value, rate->timestamp});
        }

    private:

        std::shared_ptr<ICurrencyRateService> _rateService;
};