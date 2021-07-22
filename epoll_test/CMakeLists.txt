cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(epoll_test)

find_package(PkgConfig)

pkg_search_module(glib REQUIRED glib-2.0)

aux_source_directory(. DIR_SRCS)

include_directories(${glib_INCLUDE_DIRS})

link_libraries(iniparser)
link_libraries(http_parser)

add_executable (epoll_test ${DIR_SRCS})

target_link_libraries(epoll_test ${glib_LIBRARIES})
