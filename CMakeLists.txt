cmake_minimum_required(VERSION 3.0)
project(SFML_App)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Set the source files
set(SOURCES main.cpp)

# Add an executable target
add_executable(sfml-app ${SOURCES})

# Link SFML libraries to the target
target_link_libraries(sfml-app sfml-graphics sfml-window sfml-system)
