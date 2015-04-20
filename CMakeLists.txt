cmake_minimum_required (VERSION 2.5)
project (client)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

option(TestSuite "TestSuite" OFF)

set (CXX_STD_FLAG "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STD_FLAG}")

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
