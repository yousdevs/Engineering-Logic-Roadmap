include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)


# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(array_tests
    test_array.cpp
)

target_link_libraries(array_tests
    PRIVATE
        array
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(array_tests)