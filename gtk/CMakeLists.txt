cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")
set(BINNAME "gtk_test")

project(gtk_test)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(gtk REQUIRED "gtk+-3.0")

include_directories(${gtk_INCLUDE_DIRS})

add_executable (test ${DIR_SRCS})

target_link_libraries(test ${gtk_LIBRARIES})

add_custom_target(run ${BINNAME})
