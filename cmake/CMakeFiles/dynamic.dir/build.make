# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/slim/Code/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/slim/Code/cmake

# Include any dependencies generated for this target.
include CMakeFiles/dynamic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dynamic.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dynamic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dynamic.dir/flags.make

CMakeFiles/dynamic.dir/dynamic_lib.c.o: CMakeFiles/dynamic.dir/flags.make
CMakeFiles/dynamic.dir/dynamic_lib.c.o: dynamic_lib.c
CMakeFiles/dynamic.dir/dynamic_lib.c.o: CMakeFiles/dynamic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slim/Code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dynamic.dir/dynamic_lib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dynamic.dir/dynamic_lib.c.o -MF CMakeFiles/dynamic.dir/dynamic_lib.c.o.d -o CMakeFiles/dynamic.dir/dynamic_lib.c.o -c /home/slim/Code/cmake/dynamic_lib.c

CMakeFiles/dynamic.dir/dynamic_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dynamic.dir/dynamic_lib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/slim/Code/cmake/dynamic_lib.c > CMakeFiles/dynamic.dir/dynamic_lib.c.i

CMakeFiles/dynamic.dir/dynamic_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dynamic.dir/dynamic_lib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/slim/Code/cmake/dynamic_lib.c -o CMakeFiles/dynamic.dir/dynamic_lib.c.s

# Object files for target dynamic
dynamic_OBJECTS = \
"CMakeFiles/dynamic.dir/dynamic_lib.c.o"

# External object files for target dynamic
dynamic_EXTERNAL_OBJECTS =

libdynamic.so: CMakeFiles/dynamic.dir/dynamic_lib.c.o
libdynamic.so: CMakeFiles/dynamic.dir/build.make
libdynamic.so: CMakeFiles/dynamic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slim/Code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libdynamic.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dynamic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dynamic.dir/build: libdynamic.so
.PHONY : CMakeFiles/dynamic.dir/build

CMakeFiles/dynamic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dynamic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dynamic.dir/clean

CMakeFiles/dynamic.dir/depend:
	cd /home/slim/Code/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slim/Code/cmake /home/slim/Code/cmake /home/slim/Code/cmake /home/slim/Code/cmake /home/slim/Code/cmake/CMakeFiles/dynamic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dynamic.dir/depend

