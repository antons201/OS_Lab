cmake_minimum_required(VERSION 3.16)
project(Lab6 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab6_1 src/check-xor.c)
add_executable(Lab6_2 src/check-fletcher.c)
add_executable(Lab6_3 src/crc.c)
add_executable(Lab6_5_1 src/create-csum.c src/crc8.h)
add_executable(Lab6_5_2 src/check-csum.c src/crc8.h)