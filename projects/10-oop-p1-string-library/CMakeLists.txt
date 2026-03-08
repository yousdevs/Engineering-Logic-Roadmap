cmake_minimum_required(VERSION 3.15)
project(10-oop-p1-string-library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(10-oop-p1-string-library examples/main.cpp "include/StringLib.h")

# Tell compiler where to find headers
target_include_directories(10-oop-p1-string-library
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)