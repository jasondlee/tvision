# CMakeLists.txt for cmenuitem library
# C wrappers for TMenuItem and TSubMenu

cmake_minimum_required(VERSION 3.5)

# Create the cmenuitem library
add_library(cmenuitem STATIC
    cmenuitem.cpp
    cmenuitem.h
)

# Link against tvision
target_link_libraries(cmenuitem PUBLIC tvision)

# Include directories
target_include_directories(cmenuitem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set C++ standard
target_compile_features(cmenuitem PUBLIC cxx_std_14)

# Optional: Add an example/test program
add_executable(cmenuitem_example example.c)
target_link_libraries(cmenuitem_example cmenuitem tvision)