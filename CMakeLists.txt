cmake_minimum_required (VERSION 2.5)
project (mp4)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

add_definitions(-std=c++11)

include_directories(include)
include_directories(lib)
include_directories("lib/ascii-engine") # for ascii-engine
include_directories("lib/ascii-engine/include") # for ascii-engine

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/ascii-engine)
add_subdirectory(googletest)

set(executable_sources
  main.cpp
  )
add_executable(${CMAKE_PROJECT_NAME} ${executable_sources})

set(executable_libs
  asciiengine
  test_suite_lib
  src
  server
  pthread
  )
target_link_libraries(${CMAKE_PROJECT_NAME} ${executable_libs})
