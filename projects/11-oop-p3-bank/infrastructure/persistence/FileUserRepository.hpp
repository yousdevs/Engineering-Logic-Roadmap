#pragma once

#include <optional>
#include <string>

#include "domain/entities/User.hpp"
#include "domain/repositories/IUserRepository.hpp"

class FileUserRepository : public IUserRepository {

    private:

        std::string _filePath;

        std::vector<User> _loadAll() const;

        void _saveAll(const std::vector<User>& users);

        User _deserialize(const std::string& line) const;

        std::string _serialize(const User& user) const;

    public:

        explicit FileUserRepository(const std::string& filePath);

        std::vector<User> findAll() const override;

        std::optional<User> findByUsername(const std::string& username) const override;

        void save(const User& user) override;

        void remove(const std::string& username) override;
};