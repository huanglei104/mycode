cmake_minimum_required (VERSION 2.8)

set(CMAKE_C_FLAGS "-Wall -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(sockopt)

aux_source_directory(. DIR_SRCS)

add_executable (sockopt ${DIR_SRCS})

