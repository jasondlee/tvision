# CMakeLists.txt for capplication library
# C wrappers for TApplication

cmake_minimum_required(VERSION 3.5)

# Create the capplication library
add_library(capplication STATIC
    capplication.cpp
    capplication.h
        ckeys.h
)

# Link against tvision and the other C wrapper libraries
target_link_libraries(capplication PUBLIC tvision cmenuitem cstatusline)

# Include directories
target_include_directories(capplication PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../cmenuitem
    ${CMAKE_CURRENT_SOURCE_DIR}/../cstatusline
)

# Set C++ standard
target_compile_features(capplication PUBLIC cxx_std_14)

# Optional: Add an example/test program
add_executable(capplication_example example.c)
target_link_libraries(capplication_example capplication cmenuitem cstatusline tvision)

# Made with Bob