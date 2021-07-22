cmake_minimum_required (VERSION 3.0)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(jsonctest)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(json REQUIRED json-glib-1.0)

include_directories(${json_INCLUDE_DIRS})

add_executable (test ${DIR_SRCS})

target_link_libraries(test ${json_LIBRARIES})
