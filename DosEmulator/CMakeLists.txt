cmake_minimum_required(VERSION 3.6)
project(DosEmulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "*.h" "*.c")
add_executable(DosEmulator ${SOURCE_FILES})