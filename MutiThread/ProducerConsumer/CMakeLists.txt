cmake_minimum_required(VERSION 3.16)

project(ProducerConsumer)

file(GLOB PROCON_SRCS *.cpp)
file(GLOB PROCON_HDRS *.h *.hpp)

add_executable(${PROJECT_NAME} ${PROCON_SRCS} ${PROCON_HDRS})