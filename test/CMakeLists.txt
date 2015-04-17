set(test_sources
    test_main.cpp
    semaphoreTest.cpp
    semaphoreThreadTest.cpp
    boundedBufferTest.cpp
    histogramTest.cpp
    boundedBufferThreadTest.cpp
)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/googletest/include)

add_library(test_suite_lib ${test_sources})
add_executable(test_suite ${test_sources})

set(test_suite_libs 
    gtest
    src
    asciiengine
)
target_link_libraries(test_suite ${test_suite_libs})

add_test(TestingSuite test_suite)
