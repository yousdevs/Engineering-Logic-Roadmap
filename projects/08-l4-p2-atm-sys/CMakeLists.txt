project(AtmSystem)

# 1. Define the executable
add_executable(08-l4-p2-atm-sys
    main.cpp
    clients.txt   # Adding them here makes them show up in VS Solution Explorer
)

# 2. Tell CMake to copy the .txt files to the build directory
# This ensures your program can find them using just the filename
add_custom_command(
    TARGET 08-l4-p2-atm-sys POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/clients.txt"
        "$<TARGET_FILE_DIR:08-l4-p2-atm-sys>"
)

# 3. Optional: Organize in VS
# set_target_properties(08-l4-p2-atm-sys PROPERTIES FOLDER "Projects/atm)