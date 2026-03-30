#include "infrastructure/persistence/Row.hpp"

void Row::set(const std::string& key, const std::string& value) {

    _fields[key] = value;
}

void Row::set(const std::string& key, int64_t value) {

    _fields[key] = std::to_string(value);
}

void Row::set(const std::string& key, int value) {

    _fields[key] = std::to_string(value);
}

void Row::set(const std::string& key, bool value) {

    _fields[key] = value ? "1" : "0";
}

void Row::setNull(const std::string& key) {

    _fields[key] = std::nullopt;
}

bool Row::has(const std::string& key) const {

    return _fields.count(key) > 0;
}

bool Row::isNull(const std::string& key) const {

    auto it = _fields.find(key);

    return it != _fields.end() && !it->second.has_value();
}