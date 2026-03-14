cmake_minimum_required(VERSION 3.20)

project(BankSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    bank-system
    app/main.cpp
 "domain/entities/Client.cpp" "domain/entities/User.cpp" "domain/entities/Transaction.cpp" "infrastructure/persistence/FileClientRepository.cpp" "infrastructure/persistence/FileUserRepository.cpp")

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