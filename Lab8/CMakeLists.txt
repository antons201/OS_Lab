cmake_minimum_required(VERSION 3.16)
project(Lab8 C)

set(CMAKE_C_STANDARD 99)

add_executable(Server src/server.c)
add_executable(Client src/client.c)