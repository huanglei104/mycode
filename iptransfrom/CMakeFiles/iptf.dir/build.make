# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/huanglei/Code/iptransfrom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huanglei/Code/iptransfrom

# Include any dependencies generated for this target.
include CMakeFiles/iptf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/iptf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/iptf.dir/flags.make

CMakeFiles/iptf.dir/main.c.o: CMakeFiles/iptf.dir/flags.make
CMakeFiles/iptf.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huanglei/Code/iptransfrom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/iptf.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptf.dir/main.c.o -c /home/huanglei/Code/iptransfrom/main.c

CMakeFiles/iptf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptf.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/huanglei/Code/iptransfrom/main.c > CMakeFiles/iptf.dir/main.c.i

CMakeFiles/iptf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptf.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/huanglei/Code/iptransfrom/main.c -o CMakeFiles/iptf.dir/main.c.s

# Object files for target iptf
iptf_OBJECTS = \
"CMakeFiles/iptf.dir/main.c.o"

# External object files for target iptf
iptf_EXTERNAL_OBJECTS =

iptf: CMakeFiles/iptf.dir/main.c.o
iptf: CMakeFiles/iptf.dir/build.make
iptf: CMakeFiles/iptf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/huanglei/Code/iptransfrom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable iptf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iptf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/iptf.dir/build: iptf

.PHONY : CMakeFiles/iptf.dir/build

CMakeFiles/iptf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/iptf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/iptf.dir/clean

CMakeFiles/iptf.dir/depend:
	cd /home/huanglei/Code/iptransfrom && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huanglei/Code/iptransfrom /home/huanglei/Code/iptransfrom /home/huanglei/Code/iptransfrom /home/huanglei/Code/iptransfrom /home/huanglei/Code/iptransfrom/CMakeFiles/iptf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/iptf.dir/depend

