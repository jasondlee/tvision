# CMakeLists.txt for cvision library
# C wrappers for TApplication

cmake_minimum_required(VERSION 3.5)

# Create the cvision library
add_library(cvision STATIC
        cvision.cpp
        cvision.h
        ckeys.h
        ccommands.h
)

# Link against tvision and the other C wrapper libraries
target_link_libraries(cvision PUBLIC tvision)

# Include directories
target_include_directories(cvision PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set C++ standard
target_compile_features(cvision PUBLIC cxx_std_14)

# Optional: Add an example/test program
add_executable(cvision_example cvision_example.c)
target_link_libraries(cvision_example cvision tvision)

# Made with Bob