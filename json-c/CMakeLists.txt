cmake_minimum_required (VERSION 3.0)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

project(jsonctest)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(jsonc REQUIRED json-c)

include_directories(${jsonc_INCLUDE_DIRS})

add_executable (jsonc ${DIR_SRCS})

target_link_libraries(jsonc ${jsonc_LIBRARIES})
