set(executable_sources
    main.cpp
)
add_executable(${CMAKE_PROJECT_NAME} ${executable_sources})

set(executable_libs
    src
    server
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${executable_libs})
