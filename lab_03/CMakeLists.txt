cmake_minimum_required(VERSION 3.9)
project(lab_03 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab_03 main.c)

target_link_libraries(lab_03 m)