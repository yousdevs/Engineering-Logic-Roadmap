include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)


# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(dll_tests
    test_doubly_linked_list.cpp
)

target_link_libraries(dll_tests
    PRIVATE
        doubly_linked_list
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dll_tests)