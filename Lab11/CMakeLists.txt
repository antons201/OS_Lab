cmake_minimum_required(VERSION 3.16)
project(Lab11 C)

set(CMAKE_C_STANDARD 99)

find_package (Threads)

add_executable(Lab11_1 src/vector-deadlock.c)
add_executable(Lab11_2 src/vector-global-order.c)
add_executable(Lab11_3 src/vector-try-wait.c)
add_executable(Lab11_4 src/vector-avoid-hold-and-wait.c)
add_executable(Lab11_5 src/vector-nolock.c)

target_link_libraries (Lab11_1 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab11_2 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab11_3 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab11_4 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab11_5 ${CMAKE_THREAD_LIBS_INIT})