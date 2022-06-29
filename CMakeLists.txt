# Initialize build with information

message("\n===== POKERHAND EVALUATOR AND VALIDATOR ====\n")

message("CURRENT BUILD DIRECTORY: ${CMAKE_CURRENT_SOURCE_DIR} \n")

#==========================================================================================================================================================

# =========== Global Configs ===========

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

# Use C++11 Standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output folder for program build

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#==========================================================================================================================================================

# =========== Project Configs ===========

# PROJECT NAME: DRIVER PROGRAM ------------------------------------------------------------------------------------------------------------------------------------

message("BUILDING DRIVER PROGRAM [CORE]...\n")

project(pokerEval LANGUAGES CXX)

# Project Configs

# Include required directories to search

include_directories(src)

# Set required source files for project build

set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/modules/main/main.cpp
                           ${PROJECT_SOURCE_DIR}/src/modules/pokerCore/pokerCore.cpp
						   ${PROJECT_SOURCE_DIR}/src/modules/pokerCore/util.cpp
						   ${PROJECT_SOURCE_DIR}/src/modules/readFile/readFile.cpp
						   ${PROJECT_SOURCE_DIR}/src/modules/writeFile/writeFile.cpp
)

# Add source to build

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
message("\nPATH COMPILE SOURCE: ${SOURCE_DIR}")
set(executableToBuild main.cpp)
message("EXECUTABLE: ${executableToBuild}\n")
add_subdirectory(src)

# Add executable for build

add_executable(pokerEval ${SRC_FILES})

message("BUILDING DRIVER PROGRAM [CORE] FINISHED!\n")

# PROJECT NAME: ADD FILES TO BUILD ---------------------------------------------------------------------------------------------------------------------------------

message("ADDING FILES TO BUILD...\n")

project(fileAddition)

# Project Configs

include_directories(testFiles)

# Add source to build

set(SOURCE_BASIC_TESTS_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/testFiles/basicTestFiles")
set(SOURCE_ADV_TESTS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/testFiles/basicTestFiles")
message("\nPATH ADDITION SOURCE: ${SOURCE_BASIC_TESTS_PATH} AND ${SOURCE_ADV_TESTS_PATH}")
add_subdirectory(testFiles)

message("ADDING FILES TO BUILD FINISHED!\n")

# PROJECT NAME: GOOGLE TESTS BUILD ------------------------------------------------------------------------------------------------------------------------------

message("BUILDING GOOGLETEST PROGRAM...\n")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/googleTests)

message("BUILDING GOOGLETEST PROGRAM FINISHED!\n")

# PROJECT NAME: CORE TESTS BUILD -----------------------------------------------------------------------------------------------------------------------------------

message("BUILDING CORE TESTS PROGRAM...\n")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/testModules)

message("BUILDING CORE TESTS PROGRAM FINISHED!\n")

message("\n=====BUILDING FOR ALL PROGRAMS COMPLETE====\n")

message("EXECUTABLES WILL BE BUILT IN " ${CMAKE_BINARY_DIR}/bin " ONCE COMPILED!\n")

message("TO COMPILE BUILD ALL USE: 'cmake --build build'.\n")