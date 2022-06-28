message("ADDING [HEADERS] FROM [SOURCE]...")
add_library(headers INTERFACE)
target_sources(headers INTERFACE)
target_include_directories(headers INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/headers/"
)
message("ADDING [HEADERS] FROM [SOURCE] FINISHED!")