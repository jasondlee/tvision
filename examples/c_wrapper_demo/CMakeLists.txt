# C Wrapper Demo Examples

# Simple hello example
add_executable(hello_c hello_c.c)
target_link_libraries(hello_c tvision_c)
set_property(TARGET hello_c PROPERTY C_STANDARD 99)
tv_set_output_dir(hello_c)

# Advanced demo with lists, editors, and helpers
#add_executable(advanced_demo advanced_demo.c)
#target_link_libraries(advanced_demo tvision_c)
#set_property(TARGET advanced_demo PROPERTY C_STANDARD 99)
#tv_set_output_dir(advanced_demo)