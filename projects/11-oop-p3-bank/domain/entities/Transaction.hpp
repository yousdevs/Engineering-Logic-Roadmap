#pragma once

#include <ctime>
#include <stdexcept>
#include <string>

#include "domain/value_objects/AccountId.hpp"
#include "domain/value_objects/Money.hpp"
#include "domain/value_objects/TransactionId.hpp"

enum class TransactionType { CREDIT, DEBIT };

class Transaction {

    public:

        // throws invalid_argument if description is empty
        static Transaction credit(TransactionId      id,
                                  const AccountId&   accountId,
                                  const Money&       amount,
                                  const std::string& description);

        // throws invalid_argument if description is empty
        static Transaction debit(TransactionId      id,
                                 const AccountId&   accountId,
                                 const Money&       amount,
                                 const std::string& description);

        // restores a Transaction from a stored state.
        static Transaction reconstitute(TransactionId   id,
                                        AccountId       accountId,
                                        Money           amount,
                                        TransactionType type,
                                        std::string     description,
                                        std::time_t     createdAt);

        const TransactionId& id() const;
        const AccountId&     accountId() const;
        const Money&         amount() const;
        TransactionType      type() const;
        const std::string&   description() const;
        std::time_t          createdAt() const;

        bool isCredit() const;
        bool isDebit() const;

    private:

        Transaction(TransactionId   id,
                    AccountId       accountId,
                    Money           amount,
                    TransactionType type,
                    std::string     description,
                    std::time_t     createdAt);

        const TransactionId   _id;
        const AccountId       _accountId;
        const Money           _amount;
        const TransactionType _type;
        const std::string     _description;
        const std::time_t     _createdAt;
};