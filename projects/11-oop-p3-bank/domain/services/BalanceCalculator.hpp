#pragma once

#include <stdexcept>
#include <vector>

#include "domain/entities/Transaction.hpp"
#include "domain/value_objects/AccountId.hpp"
#include "domain/value_objects/Money.hpp"

//  BalanceCalculator — a stateless domain service that derives
//                      the current balance of an account from
//                      its full transaction history.
//  Invariants:
//    - All transactions must belong to the same accountId.
//      Mixed accounts produce a meaningless number.
//    - Derived balance cannot be negative — if it is,
//      a debit was permitted without sufficient funds upstream.

class BalanceCalculator {

    public:

        // Derives balance from the full transaction history
        // of a single account.
        //
        // Throws std::invalid_argument if transactions is empty.
        // Throws std::invalid_argument if any transaction does
        //   not belong to the given accountId.
        // Throws std::logic_error if derived balance is negative
        //   (upstream data integrity violation).
        Money calculate(const AccountId&                accountId,
                        const std::vector<Transaction>& transactions) const;
};