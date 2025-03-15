# Include the testing framework header directory.
# This ensures that the test files can find doctest's headers.
# Adjust the path if your doctest directory is in a different location.
include_directories(/doctest)

# Create the test executable for testBoid.cpp
add_executable(testboid testboid.cpp ../random.cpp ../boid.cpp)
target_link_libraries(testboid PRIVATE sfml-graphics)

# Create the test executable for testFlock.cpp
add_executable(testflock testflock.cpp ../random.cpp ../boid.cpp ../flock.cpp)
target_link_libraries(testflock PRIVATE sfml-graphics)

# Create the test executable for testRandom.cpp
add_executable(testrandom testrandom.cpp ../random.cpp ../boid.cpp)
target_link_libraries(testrandom PRIVATE sfml-graphics)

# Create the test executable for teststatistics.cpp
add_executable(teststatistics teststatistics.cpp ../statistics.cpp ../random.cpp ../boid.cpp)
target_link_libraries(teststatistics PRIVATE sfml-graphics)

# Register the tests with CTest so they can be run using the `ctest` command.
add_test(NAME TestBoid COMMAND testBoid)
add_test(NAME TestFlock COMMAND testFlock)
