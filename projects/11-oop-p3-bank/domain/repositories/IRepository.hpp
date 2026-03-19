#pragma once

#include <optional>

//  IRepository<T, TId> — generic repository base.
//
//  Captures operations shared by ALL entity repositories.
//  Each entity repository inherits this and adds only the
//  queries genuinely required by its use cases.
//
//  Intentional absences:
//    - No findAll()  — unbounded queries are a reporting
//                      concern, not a domain concern.
//                      Use a dedicated query/read service.
//    - No update()   — save() handles both insert and upsert.
//                      Having both creates ambiguity.
//
//  Soft delete:
//    - remove() performs a SOFT delete on entities that
//      require audit trail (Client, User).
//    - For Transaction, remove() is = delete (compile-time).
//    - For Account, status transitions replace deletion.
//

template<typename T, typename TId>
class IRepository {

    public:

        // Inser or update (upsert)
        virtual void save(const T& entity) = 0;

        // Returns the entity if found, std::nullopt if not.
        // Does Not return soft-deleted records by default.
        virtual std::optional<T> findById(const TId& id) = 0;

        // Returns true if a non-deleted record exists.
        virtual bool exists(const TId id) = 0;

        // Soft delete for entities that support it.
        virtual void remove(const TId& id) = 0;

        virtual ~IRepository() = default;
};