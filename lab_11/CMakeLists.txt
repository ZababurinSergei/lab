cmake_minimum_required(VERSION 3.29)
project(lab_11 C)

set(CMAKE_C_STANDARD 17)

add_executable(lab_11 main.c)

# Подключаем математическую библиотеку (нужна для sqrt, sin, cos и т.д.)
target_link_libraries(lab_11 m)