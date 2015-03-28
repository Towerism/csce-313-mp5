cmake_minimum_required (VERSION 2.5)
project (mp4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

add_definitions(-std=c++11)

include_directories(include)

add_subdirectory(src)
add_subdirectory(bin)
add_subdirectory(test)
