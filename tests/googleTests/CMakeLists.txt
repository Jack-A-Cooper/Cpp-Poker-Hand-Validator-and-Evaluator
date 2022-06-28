# =========== Build Configs ===========
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

# =========== Project Config ===========

# |****| Project: googleTest Module |****|

message("\nBUILDING GOOGLETEST MODULE...\n")

project(${GTEST} NONE)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  DOWNLOAD_EXTRACT_TIMESTAMP(true)
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Fetch GoogleTest Content
FetchContent_MakeAvailable(googleTest)

# Extra configs

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

# Directories required for build

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/headers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests/googleTests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}}/testFiles)

# Provide libraries to current build

add_subdirectory(headers)
add_subdirectory(testModules)
add_subdirectory(testFiles)

# Set

set(gTestLib
  googleTests.cpp
)

# Add library

add_library(gTestLib ${gTestLib})

# Enable Testing

enable_testing()

# Add executable for build

add_executable(${GTEST}
	util.h
	pokerCore.h
	readFile.h
	util.cpp
	pokerCore.cpp
	readFile.cpp
	googleTests.cpp
	testFiles
)

# Link libraries

target_link_libraries(${GTEST}
  headers
  readFile
  pokerCore
  testFiles
  gTestLib
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(gTestLib)

message("\GOOGLETEST MODULE BUILDING FINISHED...\n")