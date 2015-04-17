add_subdirectory(server)

set(src_sources
    semaphore.cpp
    histo_world.cpp
    histo_chart.cpp
    client_task.cpp
    worker_task.cpp
)
add_library(src ${src_sources})

set(src_libs
    server
    pthread
)
target_link_libraries(src ${src_libs})

