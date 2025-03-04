# Include the testing framework header directory.
# This ensures that the test files can find doctest's headers.
# Adjust the path if your doctest directory is in a different location.
include_directories(/doctest)

# Create the test executable for testBoid.cpp
add_executable(testBoid testBoid.cpp ../random.cpp ../boid.cpp)
target_link_libraries(testBoid PRIVATE sfml-graphics)

# Create the test executable for testFlock.cpp
add_executable(testFlock testFlock.cpp ../random.cpp ../boid.cpp ../flock.cpp)
target_link_libraries(testFlock PRIVATE sfml-graphics)

# Register the tests with CTest so they can be run using the `ctest` command.
add_test(NAME TestBoid COMMAND testBoid)
add_test(NAME TestFlock COMMAND testFlock)
