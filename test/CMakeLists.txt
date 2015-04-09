set(test_sources
    test_main.cpp
    semaphoreTest.cpp
    semaphoreThreadTest.cpp
    boundedBufferTest.cpp
)

enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_suite ${test_sources})

set(test_suite_libs 
    ${GTEST_BOTH_LIBRARIES}
    src
    pthread
)
target_link_libraries(test_suite ${test_suite_libs})

add_test(TestingSuite test_suite)
