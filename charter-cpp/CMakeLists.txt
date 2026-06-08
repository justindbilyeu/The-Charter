cmake_minimum_required(VERSION 3.16)
project(charter_machine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Treat warnings as errors in CI; relax locally if needed
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Charter library
add_library(charter
    src/types.cpp
    src/fsm.cpp
    src/gates.cpp
    src/coherence_controller.cpp
    src/session_continuity.cpp
    src/llm_interface.cpp
)
target_include_directories(charter PUBLIC include)

# Demo executable
add_executable(charter_demo main.cpp)
target_link_libraries(charter_demo PRIVATE charter)

# Build instructions:
#   mkdir build && cd build
#   cmake ..
#   cmake --build .
#   ./charter_demo
