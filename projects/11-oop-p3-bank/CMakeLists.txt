cmake_minimum_required(VERSION 3.20)

project(BankSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    bank-system
    app/main.cpp
 "domain/entities/Client.cpp")