cmake_minimum_required(VERSION 3.26)
project(socketsServer C)

set(CMAKE_C_STANDARD 11)

add_executable(socketsServer main.c)

target_link_libraries(socketsServer PRIVATE ws2_32)