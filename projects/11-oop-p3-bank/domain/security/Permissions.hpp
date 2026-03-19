#pragma once

//  Adding a new permission:
//    1. Add a new constexpr here (next available bit).
//    2. Assign it to the relevant Role(s) in Role.hpp.
//    3. Update permissionFromRole / roleFromPermissions
//       if the role's bitmask changes.
// ───────────────────────────────────────────────────────────

namespace Permission {

constexpr int ListClients = 1 << 0;

constexpr int AddClient = 1 << 1;

constexpr int UpdateClient = 1 << 2;

constexpr int DeleteClient = 1 << 3;

constexpr int Deposit = 1 << 4;

constexpr int Withdraw = 1 << 5;

constexpr int Transfer = 1 << 6;

constexpr int ViewLogs = 1 << 7;

constexpr int ManageUsers = 1 << 8;

}  // namespace Permission