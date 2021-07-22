cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(getss)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(glib REQUIRED glib-2.0)
pkg_search_module(ssl REQUIRED openssl)
pkg_search_module(gumbo REQUIRED gumbo)

include_directories(${gumbo_INCLUDE_DIRS})
include_directories(${glib_INCLUDE_DIRS})
include_directories(${ssl_INCLUDE_DIRS})

add_executable (getss ${DIR_SRCS})

target_link_libraries(getss ${gumbo_LIBRARIES})
target_link_libraries(getss ${glib_LIBRARIES})
target_link_libraries(getss ${ssl_LIBRARIES})
target_link_libraries(getss http_parser)

add_custom_target(run ${PROJECT_NAME})
