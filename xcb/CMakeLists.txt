cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(xcb_test)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(xcb REQUIRED xcb)

include_directories(${xcb_INCLUDE_DIRS})

add_executable (test ${DIR_SRCS})

target_link_libraries(test ${xcb_LIBRARIES})
