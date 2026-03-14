#pragma once

#include <string>
#include <vector>
#include <optional>

#include "../../domain/repositories/IClientRepository.hpp"



class FileClientRepository : public IClientRepository {

	private:
         std::string _filePath;
		 
		 std::vector<Client> _loadAll() const;

		 void _saveAll(const std::vector<Client>& clients);

		 Client _deserialize(const std::string& line) const;

		 std::string _serialize(const Client& client) const;

	public:

		explicit FileClientRepository(const std::string& filePath);

		std::vector<Client> findAll() const override;

		std::optional<Client> findById(
                    const std::string& accountId) const override;

		void save(const Client& client) override;

		void remove(const std::string& accountId) override;
	
};