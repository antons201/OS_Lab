cmake_minimum_required(VERSION 3.15)
project(OS_Lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(OS_Lab5_1 1.c)
add_executable(OS_Lab5_2 2.c)
add_executable(mytail tail.c)
add_executable(mystat stat.c)
add_executable(myls ls.c)
add_executable(task6 6.c)