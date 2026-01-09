# Turbo Vision C Wrapper Library

# Source files for the C wrapper
set(TVISION_C_SOURCES
    tv_types.cpp
    tv_events.cpp
    tv_view.cpp
    tv_window.cpp
    tv_widgets.cpp
    tv_lists.cpp
    tv_editors.cpp
    tv_app.cpp
    tv_helpers.cpp
)

# Create the C wrapper library
add_library(tvision_c ${TVISION_C_SOURCES})

# Link against the main tvision library
target_link_libraries(tvision_c PUBLIC tvision)

# Include directories
target_include_directories(tvision_c PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set C++ standard
target_compile_features(tvision_c PUBLIC cxx_std_14)

# Apply project settings
tv_set_output_dir(tvision_c)
tv_add_private_includes(tvision_c)
tv_set_warnings(tvision_c)

# Installation rules
install(TARGETS tvision_c
    EXPORT tvision_c-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/tvision_c
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# Export configuration
install(EXPORT tvision_c-config
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tvision_c
    NAMESPACE tvision::
)