#pragma once

#include <string>
#include <vector>

struct ClientSummaryDTO {

        std::string id;
        std::string name;
        long long   balance;
};

struct ListClientsResponse {

        std::vector<ClientSummaryDTO> clients;
};