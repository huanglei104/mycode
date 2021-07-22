cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS "on")
set(EXECUTABLE_OUTPUT_PATH ./out)
set(BINNAME "semaphore")

project(sem_test)

aux_source_directory(src DIR_SRCS)

add_executable (${BINNAME} ${DIR_SRCS})

target_link_libraries(${BINNAME} pthread)

add_custom_target(run ${BINNAME})
