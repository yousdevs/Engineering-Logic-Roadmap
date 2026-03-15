#pragma once

namespace Permission {

	constexpr int ListClients  = 1 << 0;

    constexpr int AddClient    = 1 << 1;

	constexpr int UpdateClient = 1 << 2;

	constexpr int DeleteClient = 1 << 3;

	constexpr int Deposit      = 1 << 4;
        
	constexpr int Withdraw     = 1 << 5;

	constexpr int Transfer     = 1 << 6;

	constexpr int ViewLogs     = 1 << 7;

	constexpr int ManageUsers  = 1 << 8;
        
}