#pragma once

#include <optional>
#include <string>
#include <utility>

template<typename T>
class UseCaseResult {

    private:

        bool             _success;
        std::string      _message;
        std::optional<T> _data;

    public:

        static UseCaseResult success(T data) {
            return UseCaseResult(true, "", std::move(data));
        }

        static UseCaseResult failure(std::string message) {
            return UseCaseResult(false, std::move(message), std::nullopt);
        }

        bool isSuccess() const {
            return _success;
        }

        const std::string& message() const {
            return _message;
        }

        const std::optional<T>& data() const {
            return _data;
        }

    private:

        UseCaseResult(bool success, std::string message, std::optional<T> data)
            : _success(success), _message(std::move(message)), _data(std::move(data)) {}
};

template<>
class UseCaseResult<void> {

    private:

        bool        _success;
        std::string _message;

    public:

        static UseCaseResult success() {
            return UseCaseResult(true, "");
        }

        static UseCaseResult failure(std::string message) {
            return UseCaseResult(false, std::move(message));
        }

        bool isSuccess() const {
            return _success;
        }

        const std::string& message() const {
            return _message;
        }

    private:

        UseCaseResult(bool success, std::string message)
            : _success(success), _message(std::move(message)) {}
};