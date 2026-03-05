cmake_minimum_required(VERSION 3.15)
project(AlgorithmsL3)

# 1. Find all .cpp files in this folder
file(GLOB ALL_FILES CONFIGURE_DEPENDS "*.cpp")

# 2. Loop through each file individually
foreach(FILE_PATH ${ALL_FILES})
    
    # Get just the filename without the extension (e.g., "01-random-matrix")
    get_filename_component(FILE_NAME ${FILE_PATH} NAME_WE)

    # 3. Create a UNIQUE executable for every single file
    # This keeps 'main' functions separate!
    add_executable(${FILE_NAME} ${FILE_PATH} )
    
    # Optional: Organize them in a folder in VS Solution Explorer
    set_target_properties(${FILE_NAME} PROPERTIES FOLDER "Algorithms-L3")

endforeach()