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
CMAKE_SOURCE_DIR = /home/ubuntu/Desktop/music_vis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Desktop/music_vis/build

# Include any dependencies generated for this target.
include aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/depend.make

# Include the progress variables for this target.
include aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/progress.make

# Include the compile flags for this target's objects.
include aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/flags.make

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/flags.make
aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o: ../aquila-src/examples/am_modulation/am_modulation.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Desktop/music_vis/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o"
	cd /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/am_modulation.dir/am_modulation.cpp.o -c /home/ubuntu/Desktop/music_vis/aquila-src/examples/am_modulation/am_modulation.cpp

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/am_modulation.dir/am_modulation.cpp.i"
	cd /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Desktop/music_vis/aquila-src/examples/am_modulation/am_modulation.cpp > CMakeFiles/am_modulation.dir/am_modulation.cpp.i

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/am_modulation.dir/am_modulation.cpp.s"
	cd /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Desktop/music_vis/aquila-src/examples/am_modulation/am_modulation.cpp -o CMakeFiles/am_modulation.dir/am_modulation.cpp.s

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires:
.PHONY : aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires
	$(MAKE) -f aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/build.make aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides.build
.PHONY : aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides.build: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o

# Object files for target am_modulation
am_modulation_OBJECTS = \
"CMakeFiles/am_modulation.dir/am_modulation.cpp.o"

# External object files for target am_modulation
am_modulation_EXTERNAL_OBJECTS =

aquila-src/examples/am_modulation/am_modulation: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o
aquila-src/examples/am_modulation/am_modulation: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/build.make
aquila-src/examples/am_modulation/am_modulation: aquila-src/libAquila.a
aquila-src/examples/am_modulation/am_modulation: aquila-src/lib/libOoura_fft.a
aquila-src/examples/am_modulation/am_modulation: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable am_modulation"
	cd /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/am_modulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/build: aquila-src/examples/am_modulation/am_modulation
.PHONY : aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/build

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/requires: aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires
.PHONY : aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/requires

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/clean:
	cd /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation && $(CMAKE_COMMAND) -P CMakeFiles/am_modulation.dir/cmake_clean.cmake
.PHONY : aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/clean

aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/depend:
	cd /home/ubuntu/Desktop/music_vis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Desktop/music_vis /home/ubuntu/Desktop/music_vis/aquila-src/examples/am_modulation /home/ubuntu/Desktop/music_vis/build /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation /home/ubuntu/Desktop/music_vis/build/aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : aquila-src/examples/am_modulation/CMakeFiles/am_modulation.dir/depend

