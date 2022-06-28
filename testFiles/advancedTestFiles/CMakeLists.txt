add_library(advancedTestFiles INTERFACE)
target_sources(advancedTestFiles INTERFACE)
target_include_directories(advancedTestFiles INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/testFiles/advancedTestFiles"
)