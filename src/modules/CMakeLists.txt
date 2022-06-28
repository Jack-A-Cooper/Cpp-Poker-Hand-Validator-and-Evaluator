message("ADDING [MODULES] FROM [SOURCE]...")
add_subdirectory(main)
add_subdirectory(pokerCore)
add_subdirectory(readFile)
add_subdirectory(writeFile)
add_library(poker_src_modules INTERFACE)
target_include_directories(poker_src_modules INTERFACE 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/modules/"
)
target_link_libraries(poker_src_modules INTERFACE main pokerCore readFile)
message("ADDING [MODULES] FROM [SOURCE] FINISHED!")