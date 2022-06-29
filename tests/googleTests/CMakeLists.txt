# =========== Build Configs ===========
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

# =========== Project Config ===========

message("BUILDING GOOGLETEST MODULE...\n")

project(googleTests LANGUAGES CXX)

# Fetch googletest for use

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing for googletest

enable_testing()


# Add source to build

set(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/googleTests")
message("\nPATH COMPILE SOURCE: ${TEST_SOURCE_DIR}")

# Include required directories to search

include_directories(src)
include_directories(tests)

# Set required source files for project build

set(SRC_FILES googleTests.cpp
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

add_executable(googleTests ${SRC_FILES})

# Link libraries for build

target_link_libraries(googleTests gtest_main)

# Include GoogleTest

include(GoogleTest)

# Discover tests in build

gtest_discover_tests(googleTests)

message("\nGOOGLETEST MODULE BUILDING FINISHED...\n")