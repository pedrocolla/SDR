# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /srv/clusterfs/sdr/gnuradio/gr-customModule

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /srv/clusterfs/sdr/gnuradio/gr-customModule/build

# Utility rule file for copy_module_for_tests.

# Include any custom commands dependencies for this target.
include python/customModule/CMakeFiles/copy_module_for_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include python/customModule/CMakeFiles/copy_module_for_tests.dir/progress.make

python/customModule/CMakeFiles/copy_module_for_tests:
	cd /srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule && /usr/bin/cmake -E copy_directory /srv/clusterfs/sdr/gnuradio/gr-customModule/python/customModule /srv/clusterfs/sdr/gnuradio/gr-customModule/build/test_modules/gnuradio/customModule/

copy_module_for_tests: python/customModule/CMakeFiles/copy_module_for_tests
copy_module_for_tests: python/customModule/CMakeFiles/copy_module_for_tests.dir/build.make
.PHONY : copy_module_for_tests

# Rule to build all files generated by this target.
python/customModule/CMakeFiles/copy_module_for_tests.dir/build: copy_module_for_tests
.PHONY : python/customModule/CMakeFiles/copy_module_for_tests.dir/build

python/customModule/CMakeFiles/copy_module_for_tests.dir/clean:
	cd /srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule && $(CMAKE_COMMAND) -P CMakeFiles/copy_module_for_tests.dir/cmake_clean.cmake
.PHONY : python/customModule/CMakeFiles/copy_module_for_tests.dir/clean

python/customModule/CMakeFiles/copy_module_for_tests.dir/depend:
	cd /srv/clusterfs/sdr/gnuradio/gr-customModule/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /srv/clusterfs/sdr/gnuradio/gr-customModule /srv/clusterfs/sdr/gnuradio/gr-customModule/python/customModule /srv/clusterfs/sdr/gnuradio/gr-customModule/build /srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule /srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/CMakeFiles/copy_module_for_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : python/customModule/CMakeFiles/copy_module_for_tests.dir/depend

