cmake_minimum_required(VERSION 3.20)
project(Queue VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(queue INTERFACE)

file(GLOB_RECURSE DLL_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

target_sources(queue INTERFACE ${DLL_HEADERS})

target_include_directories(queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


option(BUILD_TESTS "build unit tests" ON)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()