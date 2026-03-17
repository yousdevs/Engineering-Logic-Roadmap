#pragma once

#include <stdexcept>

class Money {

    private:

        long long _amount;  // smallest currency unit

    public:

        explicit Money(long long amount) {

            if (amount < 0)
                throw std::invalid_argument("Money amount cannot be negative");
            _amount = amount;
        }

        long long value() const {
            return _amount;
        }

        Money operator+(const Money& other) const {
            return Money(_amount + other._amount);
        }

        bool operator>=(const Money& other) const {
            return _amount >= other._amount;
        }

        bool operator==(const Money& other) const {
            return _amount == other._amount;
        }
};