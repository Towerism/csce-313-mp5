add_subdirectory(server)

set(src_sources
    semaphore.cpp
)
add_library(src ${src_sources})

set(src_libs
    server
)
target_link_libraries(server)

