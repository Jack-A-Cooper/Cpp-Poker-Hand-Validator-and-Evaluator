add_subdirectory(advancedTestFiles)
add_subdirectory(basicTestFiles)
add_library(testFiles INTERFACE)
target_include_directories(testFiles INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/testFiles"
)
target_link_libraries(testFiles INTERFACE advancedTestFiles
								          basicTestFiles)