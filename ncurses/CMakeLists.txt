cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(ncruses_demo)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(ncurses REQUIRED ncurses)

include_directories(${ncurses_INCLUDE_DIRS})

add_executable (${PROJECT_NAME} ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} ${ncurses_LIBRARIES})

add_custom_target(run ${PROJECT_NAME})
