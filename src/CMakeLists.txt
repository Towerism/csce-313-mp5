add_subdirectory(server)

set(src_sources
    semaphore.cpp
    client_task.cpp
    worker_task.cpp
)
add_library(src ${src_sources})

set(src_libs
    server
    pthread
)
target_link_libraries(src ${src_libs})

