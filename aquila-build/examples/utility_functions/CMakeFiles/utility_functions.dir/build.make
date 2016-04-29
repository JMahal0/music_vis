# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/Desktop/music_vis/aquila-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Desktop/music_vis/aquila-build

# Include any dependencies generated for this target.
include examples/utility_functions/CMakeFiles/utility_functions.dir/depend.make

# Include the progress variables for this target.
include examples/utility_functions/CMakeFiles/utility_functions.dir/progress.make

# Include the compile flags for this target's objects.
include examples/utility_functions/CMakeFiles/utility_functions.dir/flags.make

examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o: examples/utility_functions/CMakeFiles/utility_functions.dir/flags.make
examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o: /home/ubuntu/Desktop/music_vis/aquila-src/examples/utility_functions/utility_functions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Desktop/music_vis/aquila-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o"
	cd /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/utility_functions.dir/utility_functions.cpp.o -c /home/ubuntu/Desktop/music_vis/aquila-src/examples/utility_functions/utility_functions.cpp

examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility_functions.dir/utility_functions.cpp.i"
	cd /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Desktop/music_vis/aquila-src/examples/utility_functions/utility_functions.cpp > CMakeFiles/utility_functions.dir/utility_functions.cpp.i

examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility_functions.dir/utility_functions.cpp.s"
	cd /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Desktop/music_vis/aquila-src/examples/utility_functions/utility_functions.cpp -o CMakeFiles/utility_functions.dir/utility_functions.cpp.s

examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.requires:
.PHONY : examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.requires

examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.provides: examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.requires
	$(MAKE) -f examples/utility_functions/CMakeFiles/utility_functions.dir/build.make examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.provides.build
.PHONY : examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.provides

examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.provides.build: examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o

# Object files for target utility_functions
utility_functions_OBJECTS = \
"CMakeFiles/utility_functions.dir/utility_functions.cpp.o"

# External object files for target utility_functions
utility_functions_EXTERNAL_OBJECTS =

examples/utility_functions/utility_functions: examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o
examples/utility_functions/utility_functions: examples/utility_functions/CMakeFiles/utility_functions.dir/build.make
examples/utility_functions/utility_functions: libAquila.a
examples/utility_functions/utility_functions: lib/libOoura_fft.a
examples/utility_functions/utility_functions: examples/utility_functions/CMakeFiles/utility_functions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable utility_functions"
	cd /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utility_functions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/utility_functions/CMakeFiles/utility_functions.dir/build: examples/utility_functions/utility_functions
.PHONY : examples/utility_functions/CMakeFiles/utility_functions.dir/build

examples/utility_functions/CMakeFiles/utility_functions.dir/requires: examples/utility_functions/CMakeFiles/utility_functions.dir/utility_functions.cpp.o.requires
.PHONY : examples/utility_functions/CMakeFiles/utility_functions.dir/requires

examples/utility_functions/CMakeFiles/utility_functions.dir/clean:
	cd /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions && $(CMAKE_COMMAND) -P CMakeFiles/utility_functions.dir/cmake_clean.cmake
.PHONY : examples/utility_functions/CMakeFiles/utility_functions.dir/clean

examples/utility_functions/CMakeFiles/utility_functions.dir/depend:
	cd /home/ubuntu/Desktop/music_vis/aquila-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Desktop/music_vis/aquila-src /home/ubuntu/Desktop/music_vis/aquila-src/examples/utility_functions /home/ubuntu/Desktop/music_vis/aquila-build /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions /home/ubuntu/Desktop/music_vis/aquila-build/examples/utility_functions/CMakeFiles/utility_functions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/utility_functions/CMakeFiles/utility_functions.dir/depend

