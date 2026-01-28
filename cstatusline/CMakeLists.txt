# CMakeLists.txt for cstatusline library
# C wrappers for TStatusLine, TStatusDef, and TStatusItem

cmake_minimum_required(VERSION 3.5)

# Create the cstatusline library
add_library(cstatusline STATIC
    cstatusline.cpp
    cstatusline.h
)

# Link against tvision
target_link_libraries(cstatusline PUBLIC tvision)

# Include directories
target_include_directories(cstatusline PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set C++ standard
target_compile_features(cstatusline PUBLIC cxx_std_14)

# Optional: Add an example/test program
add_executable(cstatusline_example example.c)
target_link_libraries(cstatusline_example cstatusline tvision)