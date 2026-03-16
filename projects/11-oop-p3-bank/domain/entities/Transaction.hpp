#pragma once

#include <ctime>
#include <optional>
#include <string>

class Transaction {

    public:

        enum class Type { Deposit, Withdraw, Transfer };

    private:

        std::string                _transactionId;
        std::optional<std::string> _sourceAccount;
        std::optional<std::string> _destinationAccount;

        long long   _amount;
        Type        _type;
        std::time_t _timestamp;

    private:

        Transaction(const std::string&         transactionId,
                    std::optional<std::string> sourceAccount,
                    std::optional<std::string> destinationAccount,
                    long long                  amount,
                    Type                       type,
                    std::time_t                timestamp);

    public:

        static Transaction createDeposit(

            const std::string& transactionId,
            const std::string& destinationAccount,
            long long          amount);

        static Transaction createWithdraw(

            const std::string& transactionId, const std::string& sourceAccount, long long amount);

        static Transaction createTransfer(

            const std::string& transactionId,
            const std::string& sourceAccount,
            const std::string& destinationAccount,
            long long          amount);

        static Transaction rehydrate(

            const std::string&         transactionId,
            std::optional<std::string> sourceAccount,
            std::optional<std::string> destinationAccount,
            long long                  amount,
            Type                       type,
            std::time_t                timestamp);

        const std::optional<std::string>& getSourceAccount() const;

        const std::optional<std::string>& getDestinationAccount() const;

        long long getAmount() const;

        Type getType() const;

        std::time_t getTimestamp() const;

        const std::string& getTransactionId() const;
};