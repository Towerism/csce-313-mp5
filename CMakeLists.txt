cmake_minimum_required (VERSION 2.5)
project (client)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

option(TestSuite "TestSuite" OFF)

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -ggdb")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

add_definitions(-std=c++11)

include_directories(include)
include_directories(lib)
include_directories("lib/ascii-engine")
include_directories("lib/ascii-engine/include")

add_subdirectory(lib/ascii-engine)
add_subdirectory(src)

if (TestSuite)
  add_subdirectory(lib/googletest)
  add_subdirectory(test)
endif()

set(executable_sources
  main.cpp
  )
add_executable(${CMAKE_PROJECT_NAME} ${executable_sources})

set(executable_libs
  asciiengine
  src
  server
  pthread
  )
target_link_libraries(${CMAKE_PROJECT_NAME} ${executable_libs})
