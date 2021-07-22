cmake_minimum_required(VERSION 3.20)

project(dbus-test)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(PkgConfig REQUIRED)

pkg_search_module(dbus REQUIRED dbus-1)

add_executable(send send.c)
add_executable(recv recv.c)

include_directories(${dbus_INCLUDE_DIRS})
target_link_libraries(send ${dbus_LIBRARIES})
target_link_libraries(recv ${dbus_LIBRARIES})
