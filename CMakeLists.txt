# Alert

message("\n===== POKERHAND EVALUATOR AND VALIDATOR ====\n")

message("CURRENT BUILD DIRECTORY: ${CMAKE_CURRENT_SOURCE_DIR} \n")

# =========== Global Configs ===========

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# set (CMAKE_CXX_FLAGS "-g3 -Wall -O0") 

# Use C++11 Standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output folder for program build

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =========== Project Configs ===========

# |****| Project: DRIVER PROGRAM |****|

message("COMPILING AND LINKING SOURCE FOR DRIVER PROGRAM [CORE]...\n")

project(pokerEval LANGUAGES CXX)

# Project Configs

include_directories(src 
                    src/headers
					src/modules
					src/modules/main
					src/modules/pokerCore
					src/modules/readFile
					src/modules/writeFile
					testFiles/advancedTestFiles
					testFiles/basicTestFiles
)
set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/modules/main/main.cpp
              ${PROJECT_SOURCE_DIR}/src/modules/pokerCore/pokerCore.cpp
			  ${PROJECT_SOURCE_DIR}/src/modules/pokerCore/util.cpp
			  ${PROJECT_SOURCE_DIR}/src/modules/readFile/readFile.cpp
			  ${PROJECT_SOURCE_DIR}/src/modules/writeFile/writeFile.cpp
)

# Add Test Files

file(GLOB BASICTESTFILES ${PROJECT_SOURCE_DIR}/testFiles/advancedTestFiles/*.txt)
file(GLOB ADVANCEDTESTFILES ${PROJECT_SOURCE_DIR}/testFiles/basicTestFiles/*.txt)

# Add libraries to build

set(sourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src")
message("\nPATH COMPILE SOURCE: ${sourceDir}")
set(executableToBuild main.cpp)
message("EXECUTABLE: ${executableToBuild}\n")
add_subdirectory(src)
set(testFilesDir "${CMAKE_CURRENT_SOURCE_DIR}/testFiles")
message("\nTEST FILES DIRECTORY: ${testFilesDir}\n")
add_subdirectory(testFiles)

# Add executable for build

add_executable(pokerEval ${SRC_FILES} ${BASICTESTFILES} ${ADVANCEDTESTFILES})

# Link libraries

target_link_libraries(pokerEval
  testFiles
)

message("COMPILING AND LINKING FOR DRIVER PROGRAM [CORE] FINISHED!")

message("\n=====COMPILING AND LINKING FOR ALL PROGRAMS COMPLETE====\n")

message("EXECUTABLES WILL BE BUILT IN " ${CMAKE_BINARY_DIR}/bin "\n")

message("TO BUILD ALL USE: 'cmake --build build'.\n")