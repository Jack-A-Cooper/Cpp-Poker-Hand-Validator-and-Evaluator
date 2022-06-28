add_subdirectory(googleTests)
add_subdirectory(testModules)
add_library(tests INTERFACE)
target_include_directories(tests INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/tests"
)
target_link_libraries(tests INTERFACE googleTests
								      testModules)