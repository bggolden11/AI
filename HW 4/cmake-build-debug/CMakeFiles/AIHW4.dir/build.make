# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/briangoldenberg/GitHub/AIHW4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AIHW4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AIHW4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AIHW4.dir/flags.make

CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.o: CMakeFiles/AIHW4.dir/flags.make
CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.o: ../HW\ 5/IterativeDeepening.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.o -c "/Users/briangoldenberg/GitHub/AIHW4/HW 5/IterativeDeepening.cpp"

CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/briangoldenberg/GitHub/AIHW4/HW 5/IterativeDeepening.cpp" > CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.i

CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/briangoldenberg/GitHub/AIHW4/HW 5/IterativeDeepening.cpp" -o CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.s

CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.o: CMakeFiles/AIHW4.dir/flags.make
CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.o: ../HW\ 6/AStar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.o -c "/Users/briangoldenberg/GitHub/AIHW4/HW 6/AStar.cpp"

CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/briangoldenberg/GitHub/AIHW4/HW 6/AStar.cpp" > CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.i

CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/briangoldenberg/GitHub/AIHW4/HW 6/AStar.cpp" -o CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.s

# Object files for target AIHW4
AIHW4_OBJECTS = \
"CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.o" \
"CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.o"

# External object files for target AIHW4
AIHW4_EXTERNAL_OBJECTS =

AIHW4: CMakeFiles/AIHW4.dir/HW_5/IterativeDeepening.cpp.o
AIHW4: CMakeFiles/AIHW4.dir/HW_6/AStar.cpp.o
AIHW4: CMakeFiles/AIHW4.dir/build.make
AIHW4: CMakeFiles/AIHW4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AIHW4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AIHW4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AIHW4.dir/build: AIHW4

.PHONY : CMakeFiles/AIHW4.dir/build

CMakeFiles/AIHW4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AIHW4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AIHW4.dir/clean

CMakeFiles/AIHW4.dir/depend:
	cd /Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/briangoldenberg/GitHub/AIHW4 /Users/briangoldenberg/GitHub/AIHW4 /Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug /Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug /Users/briangoldenberg/GitHub/AIHW4/cmake-build-debug/CMakeFiles/AIHW4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AIHW4.dir/depend
