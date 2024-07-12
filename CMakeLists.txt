cmake_minimum_required(VERSION 3.20)
project(OptionPricer)
set(CMAKE_CXX_STANDARD 20) # Use C++17 or your preferred standard
# Add include directories
include_directories(/usr/local/opt/boost/include)
# Define the source files
set(SOURCES
european_option.cpp
american_option.cpp
asian_option.cpp
pricing_methods.cpp
console_interface.cpp
hardcoded_interface.cpp
file_interface.cpp
matrix_interface.cpp
main.cpp
)
# Set the output directory for the executable to be the same as CMakeLists.txt
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Create the executable
add_executable(OptionPricer ${SOURCES})