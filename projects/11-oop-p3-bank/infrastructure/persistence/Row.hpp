#pragma once

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

// Datatbase raw abstraction - the bridge between mappers and DB drivers.
// Mappers write/read Row. The concrete repository translates Row <-> SQLite.
// Swapping DB drivers means changing only the repository - mappers are untouched.
//
// Migration safety:
//    get<T>()    -- throws if field missing (required fields)
//    getOr<T>()  -- returns default if field missing (optional / new columns)

class Row {

    public:

        void set(const std::string& key, const std::string& value);

        void set(const std::string& key, int64_t value);

        void set(const std::string& key, int value);

        void set(const std::string& key, bool value);

        void setNull(const std::string& key);

        bool has(const std::string& key) const;

        bool isNull(const std::string& key) const;

        const std::unordered_map<std::string, std::optional<std::string>>& fields() const {
            return _fields;
        }

        template<typename T>
        T get(const std::string& key) const;

        template<typename T>
        T getOr(const std::string& key, const T& def) const;

    private:

        std::unordered_map<std::string, std::optional<std::string>> _fields;

        const std::string& require(const std::string& key) const {

            auto it = _fields.find(key);

            if (it == _fields.end() || !it->second.has_value())
                throw std::runtime_error("Row: required field missing: '" + key + "'");

            return it->second.value();
        }
};

// Template specialisattions (header - templates must be visible at use site)

template<>
inline std::string Row::get<std::string>(const std::string& k) const {
    return require(k);
}

template<>
inline int64_t Row::get<int64_t>(const std::string& k) const {
    return std::stoll(require(k));
}

template<>
inline std::optional<int64_t> Row::get<std::optional<int64_t>>(const std::string& k) const {
    auto it = _fields.find(k);

    if (it == _fields.end() || !it->second.has_value()) {
        return std::nullopt;
    }

    return static_cast<int64_t>(std::stoll(it->second.value()));
}

template<>
inline int Row::get<int>(const std::string& k) const {
    return std::stoi(require(k));
}

template<>
inline bool Row::get<bool>(const std::string& k) const {
    return require(k) == "1";
}

template<typename T>
T Row::getOr(const std::string& key, const T& def) const {

    if (!has(key) || isNull(key))
        return def;

    return get<T>(key);
}