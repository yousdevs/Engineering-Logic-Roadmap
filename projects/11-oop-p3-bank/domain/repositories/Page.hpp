#pragma once

#include <stdexcept>
#include <vector>

// ─────────────────────────────────────────────────────────────
//  Pagination types — shared across all paginated queries.
//
//  Page        — the request: how many, starting where.
//  PagedResult — the response: items + total count for UI.
//
//  Why pagination is built in from the start:
//    Adding it later forces every caller to change.
//    An unbounded findAll() on a large table is a
//    performance disaster waiting to happen.
//    Bounded by design — not as an afterthought.
//
//  Location: domain/repositories/
//    Pagination is a query concern, not a UI concern.
//    The domain defines how its data is accessed.
// ─────────────────────────────────────────────────────────────

struct Page {

        int offset;  // number of records to skip (0-based)
        int limit;   // maximum number of records to return

        Page(int offset, int limit) : offset(offset), limit(limit) {

            if (offset < 0)
                throw std::invalid_argument("Page: offset cannot be negative.");

            if (limit <= 0)
                throw std::invalid_argument("Page: limit must be greater than zero.");

            if (limit > 500)
                throw std::invalid_argument(
                    "Page: limit cannot exceed 500."
                    "Request smaller pages to protect performance.");
        }
        // first page with given size.
        static Page first(int limit) {
            return Page(0, limit);
        }
};

template<typename T>
struct PagedResult {

        std::vector<T> items;   // the records for this page
        int            total;   // total matching records
        int            offset;  // echoed from the request
        int            limit;   // echoed from the request

        bool hasMore() const {
            return offset + static_cast<int>(items.size()) < total;
        }
};