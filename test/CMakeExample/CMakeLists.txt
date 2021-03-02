cmake_minimum_required(VERSION 3.1.0)

project(IncBinExample LANGUAGES C CXX)

include("../../IncBinMacro.cmake")

add_executable(example example.cpp)

# Read CMake output of this.
move_incbin_to_destination(
    "${CMAKE_CURRENT_SOURCE_DIR}" # Folder with CMakeLists.txt.
    "${CMAKE_CURRENT_BINARY_DIR}" # Build folder.
    RECURSE
    )

message("Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")

