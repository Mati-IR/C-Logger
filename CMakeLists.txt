cmake_minimum_required(VERSION 3.21)
project(wrapper C)

set(CMAKE_C_STANDARD 23)

add_executable(wrapper main.c library.c timestamp.c timestamp.h)
