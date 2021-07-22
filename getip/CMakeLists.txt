cmake_minimum_required(VERSION 2.80)

project(getip)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)

add_compile_options(-Wall)

aux_source_directory(src/lib LIB_COMMON_SRCS)
aux_source_directory(src/app APP_SRCS)

add_library(common SHARED ${LIB_COMMON_SRCS})

add_executable(ifinfo ${APP_SRCS})

target_include_directories(ifinfo PRIVATE src/include)

target_link_libraries(ifinfo common)
