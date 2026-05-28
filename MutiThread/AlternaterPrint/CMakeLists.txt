cmake_minimum_required(VERSION 3.16)

project(AlternaterPrint)

file(GLOB PRINT_SRCS *.cpp)
file(GLOB PRINT_HDRS *.h)

add_executable(${PROJECT_NAME} ${PRINT_SRCS} ${PRINT_HDRS})