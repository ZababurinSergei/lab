cmake_minimum_required(VERSION 3.29)
project(lab_06 C)

set(CMAKE_C_STANDARD 17)

add_executable(lab_06 main.c)

# Подключаем математическую библиотеку (нужна для sqrt, sin, cos и т.д.)
target_link_libraries(lab_06 m)