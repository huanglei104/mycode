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
include CMakeFiles/static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/static.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/static.dir/flags.make

CMakeFiles/static.dir/static_lib.c.o: CMakeFiles/static.dir/flags.make
CMakeFiles/static.dir/static_lib.c.o: static_lib.c
CMakeFiles/static.dir/static_lib.c.o: CMakeFiles/static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slim/Code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/static.dir/static_lib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/static.dir/static_lib.c.o -MF CMakeFiles/static.dir/static_lib.c.o.d -o CMakeFiles/static.dir/static_lib.c.o -c /home/slim/Code/cmake/static_lib.c

CMakeFiles/static.dir/static_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/static.dir/static_lib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/slim/Code/cmake/static_lib.c > CMakeFiles/static.dir/static_lib.c.i

CMakeFiles/static.dir/static_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/static.dir/static_lib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/slim/Code/cmake/static_lib.c -o CMakeFiles/static.dir/static_lib.c.s

# Object files for target static
static_OBJECTS = \
"CMakeFiles/static.dir/static_lib.c.o"

# External object files for target static
static_EXTERNAL_OBJECTS = \
"/home/slim/Code/cmake/CMakeFiles/main.dir/main.c.o"

libstatic.a: CMakeFiles/static.dir/static_lib.c.o
libstatic.a: CMakeFiles/main.dir/main.c.o
libstatic.a: CMakeFiles/static.dir/build.make
libstatic.a: CMakeFiles/static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slim/Code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libstatic.a"
	$(CMAKE_COMMAND) -P CMakeFiles/static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/static.dir/build: libstatic.a
.PHONY : CMakeFiles/static.dir/build

CMakeFiles/static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/static.dir/clean

CMakeFiles/static.dir/depend:
	cd /home/slim/Code/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slim/Code/cmake /home/slim/Code/cmake /home/slim/Code/cmake /home/slim/Code/cmake /home/slim/Code/cmake/CMakeFiles/static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/static.dir/depend
