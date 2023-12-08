#!/bin/bash

# Install dependencies
sudo apt-get -y install cmake libsfml-dev

# Create a build directory if it doesn't exist
mkdir -p build
cd build || exit

# Run CMake to generate the build files
cmake ..

# Build the project using Make (or other build tool specified by CMake)
make
