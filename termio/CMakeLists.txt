cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(termio_demo)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

add_executable (${PROJECT_NAME} ${DIR_SRCS})

add_custom_target(run ${PROJECT_NAME})
