project(hello)

add_library(static STATIC static_lib.c)
add_library(obj OBJECT obj.c)
add_library(main OBJECT main.c)
add_library(dynamic SHARED dynamic_lib.c)

add_executable(hello)

target_link_libraries(static PUBLIC main)
target_link_libraries(hello static obj dynamic)
