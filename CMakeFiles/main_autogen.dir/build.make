# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/vbroda/inventory-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vbroda/inventory-project

# Utility rule file for main_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/main_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_autogen.dir/progress.make

CMakeFiles/main_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vbroda/inventory-project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target main"
	/usr/bin/cmake -E cmake_autogen /home/vbroda/inventory-project/CMakeFiles/main_autogen.dir/AutogenInfo.json ""

main_autogen: CMakeFiles/main_autogen
main_autogen: CMakeFiles/main_autogen.dir/build.make
.PHONY : main_autogen

# Rule to build all files generated by this target.
CMakeFiles/main_autogen.dir/build: main_autogen
.PHONY : CMakeFiles/main_autogen.dir/build

CMakeFiles/main_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_autogen.dir/clean

CMakeFiles/main_autogen.dir/depend:
	cd /home/vbroda/inventory-project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vbroda/inventory-project /home/vbroda/inventory-project /home/vbroda/inventory-project /home/vbroda/inventory-project /home/vbroda/inventory-project/CMakeFiles/main_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main_autogen.dir/depend

