cmake_minimum_required(VERSION 3.29)
project(lab_14 C)

set(CMAKE_C_STANDARD 17)

add_executable(lab_14 main.c)

# Подключаем математическую библиотеку (нужна для sqrt, sin, cos и т.д.)
target_link_libraries(lab_14 m)