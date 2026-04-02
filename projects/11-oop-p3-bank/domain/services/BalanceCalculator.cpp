#include "domain/services/BalanceCalculator.hpp"

Money BalanceCalculator::calculate(const AccountId&                accountId,
                                   const std::vector<Transaction>& transactions) const {

    if (transactions.empty())
        throw std::invalid_argument(
            "BalanceCalculator::calculate — "
            "transaction list is empty for account ["
            + accountId.value() + "]. "
            "Use Money(0) directly for accounts with no history."
        );

    for (const auto& tx : transactions) {

        if (tx.accountId().value() != accountId.value())
            throw std::invalid_argument(
                "BalanceCalculator::calculate - "
                "transaction [" + tx.id().value() + "] "
                "belongs to account [" + tx.accountId().value() + "], "
                "not to account [" + accountId.value() + "]. "
                "Mixed account transactions produce a meaningless balance."
            );
    }

    long long total = 0;

    for (const auto& tx : transactions) {
        if (tx.isCredit())
            total += static_cast<long long>(tx.amount().value());
        else
            total -= static_cast<long long>(tx.amount().value());
    }

    if (total < 0)
        throw std::logic_error(
            "BalanceCalculator::calculate - "
            "derived balance for account [" + accountId.value() + "] "
            "is negative (" + std::to_string(total) + "). "
            "This indicates a data integrity violation: a debit was "
            "recorded without sufficient funds. Investigate upstream."
        );

    return Money(static_cast<unsigned long long>(total));
}