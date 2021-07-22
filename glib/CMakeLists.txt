cmake_minimum_required (VERSION 2.8)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(glib-study)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(glib REQUIRED glib-2.0)

include_directories(${glib_INCLUDE_DIRS})

add_executable (study ${DIR_SRCS})

target_link_libraries(study ${glib_LIBRARIES})
