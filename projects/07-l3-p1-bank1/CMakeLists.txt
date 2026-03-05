# 1. Define the executable
add_executable(07-l3-p1-bank1
    07-l3-p1-bank1.cpp
    clients.txt   # Adding them here makes them show up in VS Solution Explorer
    users.txt
)

# 2. Tell CMake to copy the .txt files to the build directory
# This ensures your program can find them using just the filename
add_custom_command(
    TARGET 07-l3-p1-bank1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/clients.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/users.txt"
        "$<TARGET_FILE_DIR:07-l3-p1-bank1>"
)

# 3. Optional: Organize in VS
# set_target_properties(07-l3-p1-bank1 PROPERTIES FOLDER "Projects/Bank")