cmake_minimum_required(VERSION 3.20)

project(BankSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[
set(SOURCES
    app/main.cpp
    domain/entities/Client.cpp
    domain/entities/User.cpp
    domain/entities/Transaction.cpp
    infrastructure/persistence/FileClientRepository.cpp
    infrastructure/persistence/FileUserRepository.cpp
)
set(HEADERS
    application/usecases/LoginUseCase.hpp
    libs/StringLib.h
    
)

add_executable(
    bank-system
   ${SOURCES} ${HEADERS}
 )
]]

file(GLOB_RECURSE ALL_SOURCES 
    "app/*.cpp"
    "application/*.cpp" "application/*.hpp"
    "domain/*.cpp" "domain/*.hpp"
    "infrastructure/*.cpp" "infrastructure/*.hpp"
    "libs/*.h" "libs/*.hpp" "libs/*.cpp"
)

add_executable(bank-system ${ALL_SOURCES})

 target_include_directories(bank-system PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/application
    ${CMAKE_CURRENT_SOURCE_DIR}/domain
    ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure
)

add_custom_command(
    TARGET bank-system POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/data"
            "$<TARGET_FILE_DIR:bank-system>/data"
)
# This creates a C++ macro called DATA_PATH
target_compile_definitions(bank-system PRIVATE 
    DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/"
)
