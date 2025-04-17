cmake_minimum_required(VERSION 3.16)
project(boids VERSION 1.0.0)

# Enable testing support
include(CTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ standard settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warning flags
string(APPEND CMAKE_CXX_FLAGS
      " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion"
      " -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast")

# Enable debug assertions and sanitizers
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -D_GLIBCXX_ASSERTIONS -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# Find SFML and TGUI
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(TGUI 1 REQUIRED)

# Source files
file(GLOB SOURCES "source/*.cpp")

# Executable
add_executable(boids ${SOURCES})

# Link SFML and TGUI
target_link_libraries(boids sfml-graphics sfml-window sfml-system TGUI::TGUI)

# Link INCLUDE
target_include_directories(boids PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Optionally enable tests
option(BUILD_TESTS "Build the tests executable" ON)
if(BUILD_TESTS)
    add_subdirectory(testing)
endif()