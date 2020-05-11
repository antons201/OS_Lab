cmake_minimum_required(VERSION 3.16)
project(Lab9 C)

set(CMAKE_C_STANDARD 99)

find_package (Threads)

add_executable(Lab9_2 src/main-race.c src/mythreads.h)
add_executable(Lab9_3 src/main-deadlock.c src/mythreads.h)
add_executable(Lab9_5 src/main-deadlock-global.c src/mythreads.h)
add_executable(Lab9_6 src/main-signal.c src/mythreads.h)
add_executable(Lab9_8 src/main-signal-cv.c src/mythreads.h)

target_link_libraries (Lab9_2 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab9_3 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab9_5 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab9_6 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Lab9_8 ${CMAKE_THREAD_LIBS_INIT})