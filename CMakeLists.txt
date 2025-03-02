cmake_minimum_required(VERSION 3.16)
project(EvyalBoids VERSION 1.0.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS
      " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion"
      " -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast")

# abilita asserzioni di debug (in gcc), l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -D_GLIBCXX_ASSERTIONS -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(TGUI 1 REQUIRED)

# Create a library with all source files except main.cpp.
set(SRC_FILES
    egui.cpp
    statistics.cpp
    graphics.cpp
    random.cpp
    boid.cpp
    flock.cpp
)
add_library(EvyalBoids_lib ${SRC_FILES})
target_link_libraries(EvyalBoids_lib PUBLIC sfml-graphics TGUI::TGUI)
target_include_directories(EvyalBoids_lib PUBLIC ${CMAKE_SOURCE_DIR})

# Build the main executable using the library and main.cpp.
add_executable(boids main.cpp)
target_link_libraries(boids PRIVATE EvyalBoids_lib)

# Include the testing subdirectory.
add_subdirectory(testing)