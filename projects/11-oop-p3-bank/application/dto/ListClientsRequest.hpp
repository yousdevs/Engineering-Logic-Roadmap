#pragma once

#include <string>

struct ListClientsRequest {

        int page     = 1;
        int pageSize = 20;

        std::string nameFilter;
        std::string sortBy = "username";
};