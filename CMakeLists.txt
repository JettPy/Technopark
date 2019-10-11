cmake_minimum_required (VERSION 3.5)

project (My_idz)

set(CMAKE_C_STANDARD 11)

add_executable (first_CMake "main.c" "invoice.h" "invoice.c")

#file(GLOB CS "*.c")

#add_executable (${PROJECT_NAME} ${CS})
