# CMakeLists.txt for capplication library
# C builder API for TApplication

cmake_minimum_required(VERSION 3.5)

# Create the capplication library
add_library(capplication STATIC
    capplication.cpp
    capplication.h
)

# Link against tvision and our other C wrapper libraries
target_link_libraries(capplication PUBLIC 
    tvision
    cmenuitem
    cstatusline
)

# Include directories
target_include_directories(capplication PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../cmenuitem
    ${CMAKE_CURRENT_SOURCE_DIR}/../cstatusline
)

# Set C++ standard (need C++11 for std::map)
target_compile_features(capplication PUBLIC cxx_std_11)

# Optional: Add an example/test program
add_executable(capplication_example example.c)
target_link_libraries(capplication_example 
    capplication
    cmenuitem
    cstatusline
    tvision
)