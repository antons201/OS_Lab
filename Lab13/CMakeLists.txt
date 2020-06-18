cmake_minimum_required(VERSION 3.16)
project(Lab13 C)

set(CMAKE_C_STANDARD 99)

find_package (Threads)

add_executable(Lab13_queue src/queue.c src/utils.c)
add_executable(Lab13_queue_mutex src/queue_mutex.c src/utils.c)
add_executable(Lab13_queue_cond src/queue_cond.c src/utils.c)

target_link_libraries (Lab13_queue ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab13_queue_mutex ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab13_queue_cond ${CMAKE_THREAD_LIBS_INIT})