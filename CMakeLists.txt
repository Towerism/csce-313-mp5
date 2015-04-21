cmake_minimum_required (VERSION 2.5)
project (client CXX)

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
  endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
  message(FATAL_ERROR "Your C++ compiler, ${CMAKE_CXX_COMPILER_ID}, does not support C++11.\nPossible solution: export CXX=g++")
endif ()

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
