cmake_minimum_required(VERSION 3.10)
project(PongGame)

# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Set the source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
include_directories("src/entities" "src/constants")

# Link SFML libraries to the target
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Add a custom target for running the executable
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running game"
)
