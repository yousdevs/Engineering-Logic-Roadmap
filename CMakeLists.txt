cmake_minimum_required(VERSION 3.15)

project(EngineeringLogicRoadmap VERSION 1.0 DESCRIPTION "Programming Advices Solutions" LANGUAGES CXX)

# Set the C++ standard globally (e.g., C++17 or C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Generate compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable folder grouping in IDEs (like Visual Studio)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ---------------------------------------------------------
# Include your sub-folders here
# ---------------------------------------------------------

# The folder with multiple separate .cpp problems
add_subdirectory(05-Algorithms-L2)
add_subdirectory(07-Algorithms-L3)
add_subdirectory(08-Algorithms-L4)

# Your standard standalone projects
#add_subdirectory(SomeStandaloneProject)

# Your projects inside the /projects/ folder
add_subdirectory(projects/05-l2-p1-rock-paper-scissors)
add_subdirectory(projects/05-l2-p2-math-quiz-game)
add_subdirectory(projects/07-l3-p1-bank1)
add_subdirectory(projects/08-l4-p2-atm-sys)
add_subdirectory(projects/10-oop-p1-string-library)
add_subdirectory(projects/10-oop-p2-date-library)
add_subdirectory(projects/11-oop-p1-utility-library)
add_subdirectory(projects/11-oop-p2-input-validation-library)
add_subdirectory(projects/11-oop-p3-bank)
add_subdirectory(projects/13-p1-linked-list)
add_subdirectory(projects/13-p2-queue)
#add_subdirectory(projects/ProjectB)