cmake_minimum_required(VERSION 3.26)
project(socketsClient C)

set(CMAKE_C_STANDARD 11)

add_executable(socketsClient main.c)

target_link_libraries(socketsClient PRIVATE ws2_32)