cmake_minimum_required (VERSION 2.8)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS)

project(drmtest)

find_package(PkgConfig)

aux_source_directory(. DIR_SRCS)

pkg_search_module(libdrm REQUIRED libdrm)

include_directories(${libdrm_INCLUDE_DIRS})

add_executable (drmtest ${DIR_SRCS})

target_link_libraries(drmtest ${libdrm_LIBRARIES})
