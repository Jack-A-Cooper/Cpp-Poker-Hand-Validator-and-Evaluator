# =========== Build Configs ===========
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

# =========== Project Config ===========

message("BUILDING SIMPLE CORE TEST MODULE...\n")

project(${CORETEST} NONE)

# Add source to build

set(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/testModules")
message("\nPATH COMPILE SOURCE: ${TEST_SOURCE_DIR}")

# Set current library for build

set(simpleCoreTestLib
  simpleCoreTest.cpp
)

# Add library

add_library(simpleCoreTestLib ${simpleCoreTestLib})

# Include required directories to search

include_directories(src)
include_directories(tests)

# Set required source files for project build

set(SRC_FILES simpleCoreTest.cpp
                           ${CMAKE_SOURCE_DIR}/src/headers/pokerCore.h
						   ${CMAKE_SOURCE_DIR}/src/headers/util.h
						   ${CMAKE_SOURCE_DIR}/src/headers/readFile.h
                           ${CMAKE_SOURCE_DIR}/src/modules/pokerCore/pokerCore.cpp
						   ${CMAKE_SOURCE_DIR}/src/modules/pokerCore/util.cpp
						   ${CMAKE_SOURCE_DIR}/src/modules/readFile/readFile.cpp
)

# Add test files to bin for use

file(GLOB BASIC_TEST_FILES  "${CMAKE_SOURCE_DIR}/testFiles/basicTestFiles/*.txt")
file(GLOB ADVANCED_TEST_FILES  "${CMAKE_SOURCE_DIR}/testFiles/advancedTestFiles/*.txt")
file(COPY ${BASIC_TEST_FILES} ${ADVANCED_TEST_FILES}  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add executable for build

add_executable(coreTest ${SRC_FILES})

message("\nSIMPLE CORE TEST MODULE BUILDING FINISHED...\n")