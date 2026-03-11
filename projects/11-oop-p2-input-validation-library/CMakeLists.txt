cmake_minimum_required(VERSION 3.15)
project(11-oop-p2-input-validation-library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(11-oop-p2-input-validation-library examples/main.cpp "include/InputValidationLib.h")

# Tell compiler where to find headers
target_include_directories(11-oop-p2-input-validation-library
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)