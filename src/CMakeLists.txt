message("COMPILING AND LINKING [SOURCE]...")
add_subdirectory(headers)
add_subdirectory(modules)
add_library(poker_src INTERFACE)
target_include_directories(poker_src INTERFACE 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
target_link_libraries(poker_src INTERFACE headers modules)
message("[SOURCE] COMPILING AND LINKING FINISHED!")