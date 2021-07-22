cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(leetcode)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(glib REQUIRED glib-2.0)

include_directories(${glib_INCLUDE_DIRS})

add_executable (test ${DIR_SRCS})

target_link_libraries(test ${glib_LIBRARIES})
