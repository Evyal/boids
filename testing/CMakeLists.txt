# Specify the minimum version and project for testing (optional if already set in the top-level file)
cmake_minimum_required(VERSION 3.16)
project(EvyalBoids_tests)

# Include the testing framework header directory.
# This ensures that the test files can find doctest's headers.
# Adjust the path if your doctest directory is in a different location.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/doctest)

# Create the test executable for testBoid.cpp
add_executable(testBoid testBoid.cpp)
# Link the shared project library
target_link_libraries(testBoid PRIVATE EvyalBoids_lib)

# Create the test executable for testFlock.cpp
add_executable(testFlock testFlock.cpp)
target_link_libraries(testFlock PRIVATE EvyalBoids_lib)

# Register the tests with CTest so they can be run using the `ctest` command.
add_test(NAME TestBoid COMMAND testBoid)
add_test(NAME TestFlock COMMAND testFlock)
