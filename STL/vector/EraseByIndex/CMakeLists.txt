cmake_minimum_required(VERSION 3.16)

project(vectorEraseByIdx)

file(GLOB VEBI_SRCS *.cpp)
file(GLOB VEBI_HDRS *.h)

add_executable(${PROJECT_NAME} ${VEBI_SRCS} ${VEBI_HDRS})