add_library(basicTestFiles INTERFACE)
target_sources(basicTestFiles INTERFACE)
target_include_directories(basicTestFiles INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/testFiles/basicTestFiles"
)