cmake_minimum_required(VERSION 3.16)
project(BankingSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── SQLite ─────────────────────────────────────────────────────
find_package(SQLite3 REQUIRED)

# ── Source files ───────────────────────────────────────────────
file(GLOB_RECURSE DOMAIN_SRC       "domain/*.cpp" "domain/*.hpp")
file(GLOB_RECURSE APPLICATION_SRC  "application/*.cpp" "application/*.hpp")
file(GLOB_RECURSE INFRA_SRC        "infrastructure/*.cpp" "infrastructure/*.hpp")

add_executable(banking_system
    main.cpp
    ${DOMAIN_SRC}
    ${APPLICATION_SRC}
    ${INFRA_SRC}
)

target_include_directories(banking_system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(banking_system PRIVATE
    ${SQLite3_LIBRARIES}
    #[[pthread]]
)
#[[
# ── Compiler warnings ──────────────────────────────────────────
target_compile_options(banking_system PRIVATE
    -Wall -Wextra -Wpedantic -Wno-unused-parameter
)
]]
# ── Build types ────────────────────────────────────────────────
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "SQLite3:    ${SQLite3_VERSION}")
