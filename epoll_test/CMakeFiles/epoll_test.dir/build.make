# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/huanglei/Code/epoll_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huanglei/Code/epoll_test

# Include any dependencies generated for this target.
include CMakeFiles/epoll_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/epoll_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/epoll_test.dir/flags.make

CMakeFiles/epoll_test.dir/main.c.o: CMakeFiles/epoll_test.dir/flags.make
CMakeFiles/epoll_test.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huanglei/Code/epoll_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/epoll_test.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/epoll_test.dir/main.c.o -c /home/huanglei/Code/epoll_test/main.c

CMakeFiles/epoll_test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/epoll_test.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/huanglei/Code/epoll_test/main.c > CMakeFiles/epoll_test.dir/main.c.i

CMakeFiles/epoll_test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/epoll_test.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/huanglei/Code/epoll_test/main.c -o CMakeFiles/epoll_test.dir/main.c.s

# Object files for target epoll_test
epoll_test_OBJECTS = \
"CMakeFiles/epoll_test.dir/main.c.o"

# External object files for target epoll_test
epoll_test_EXTERNAL_OBJECTS =

epoll_test: CMakeFiles/epoll_test.dir/main.c.o
epoll_test: CMakeFiles/epoll_test.dir/build.make
epoll_test: CMakeFiles/epoll_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/huanglei/Code/epoll_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable epoll_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/epoll_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/epoll_test.dir/build: epoll_test

.PHONY : CMakeFiles/epoll_test.dir/build

CMakeFiles/epoll_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/epoll_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/epoll_test.dir/clean

CMakeFiles/epoll_test.dir/depend:
	cd /home/huanglei/Code/epoll_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huanglei/Code/epoll_test /home/huanglei/Code/epoll_test /home/huanglei/Code/epoll_test /home/huanglei/Code/epoll_test /home/huanglei/Code/epoll_test/CMakeFiles/epoll_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/epoll_test.dir/depend

