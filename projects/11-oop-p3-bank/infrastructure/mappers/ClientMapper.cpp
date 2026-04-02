#include "infrastructure/mappers/ClientMapper.hpp"

Client ClientMapper::toDomain(const Row& row) {

    return Client::reconstitute(ClientId::from(row.get<std::string>("id")),
                                row.get<std::string>("first_name"),
                                row.get<std::string>("last_name"),
                                row.get<std::string>("phone"),
                                PinCode::from(row.get<std::string>("pin_code")),
                                row.get<int64_t>("created_at"),
                                row.get<std::optional<int64_t>>("deleted_at"));
}

Row ClientMapper::toPersistence(const Client& c) {

    Row row;

    row.set("id", c.id().value());
    row.set("first_name", c.firstName());
    row.set("last_name", c.lastName());
    row.set("phone", c.phone());
    row.set("pin_code", c.pinCode().value());
    row.set("created_at", c.createdAt());

    c.deletedAt().has_value() ? row.set("deleted_at", c.deletedAt().value())
                              : row.setNull("deleted_at");

    return row;
}