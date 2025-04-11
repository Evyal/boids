# Enable testing support
enable_testing()

# Add doctest header directory
include_directories(${CMAKE_SOURCE_DIR}/testing/doctest)

# Collect only the source files needed for testing
file(GLOB TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/source/boid.cpp
    ${CMAKE_SOURCE_DIR}/source/flock.cpp
    ${CMAKE_SOURCE_DIR}/source/statistics.cpp
)

# Add testboid executable
add_executable(testboid testboid.cpp ${TEST_SOURCES})
target_link_libraries(testboid PRIVATE sfml-graphics)
add_test(NAME TestBoid COMMAND testboid)

# Add testflock executable
add_executable(testflock testflock.cpp ${TEST_SOURCES})
target_link_libraries(testflock PRIVATE sfml-graphics)
add_test(NAME TestFlock COMMAND testflock)

# Add testrandom executable
add_executable(testrandom testrandom.cpp ${TEST_SOURCES})
target_link_libraries(testrandom PRIVATE sfml-graphics)
add_test(NAME TestRandom COMMAND testrandom)

# Add teststatistics executable
add_executable(teststatistics teststatistics.cpp ${TEST_SOURCES})
target_link_libraries(teststatistics PRIVATE sfml-graphics)
add_test(NAME TestStatistics COMMAND teststatistics)
