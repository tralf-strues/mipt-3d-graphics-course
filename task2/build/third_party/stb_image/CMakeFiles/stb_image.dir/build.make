# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.21.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tralf/Dev/mipt-3d-graphics-course/task2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tralf/Dev/mipt-3d-graphics-course/task2/build

# Include any dependencies generated for this target.
include third_party/stb_image/CMakeFiles/stb_image.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/stb_image/CMakeFiles/stb_image.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/stb_image/CMakeFiles/stb_image.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/stb_image/CMakeFiles/stb_image.dir/flags.make

third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o: third_party/stb_image/CMakeFiles/stb_image.dir/flags.make
third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/stb_image/src/stb_image.cpp
third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o: third_party/stb_image/CMakeFiles/stb_image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tralf/Dev/mipt-3d-graphics-course/task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o"
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o -MF CMakeFiles/stb_image.dir/src/stb_image.cpp.o.d -o CMakeFiles/stb_image.dir/src/stb_image.cpp.o -c /Users/tralf/Dev/mipt-3d-graphics-course/third_party/stb_image/src/stb_image.cpp

third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stb_image.dir/src/stb_image.cpp.i"
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tralf/Dev/mipt-3d-graphics-course/third_party/stb_image/src/stb_image.cpp > CMakeFiles/stb_image.dir/src/stb_image.cpp.i

third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stb_image.dir/src/stb_image.cpp.s"
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tralf/Dev/mipt-3d-graphics-course/third_party/stb_image/src/stb_image.cpp -o CMakeFiles/stb_image.dir/src/stb_image.cpp.s

# Object files for target stb_image
stb_image_OBJECTS = \
"CMakeFiles/stb_image.dir/src/stb_image.cpp.o"

# External object files for target stb_image
stb_image_EXTERNAL_OBJECTS =

third_party/stb_image/libstb_imaged.dylib: third_party/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o
third_party/stb_image/libstb_imaged.dylib: third_party/stb_image/CMakeFiles/stb_image.dir/build.make
third_party/stb_image/libstb_imaged.dylib: third_party/stb_image/CMakeFiles/stb_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/tralf/Dev/mipt-3d-graphics-course/task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libstb_imaged.dylib"
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stb_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third_party/stb_image/CMakeFiles/stb_image.dir/build: third_party/stb_image/libstb_imaged.dylib
.PHONY : third_party/stb_image/CMakeFiles/stb_image.dir/build

third_party/stb_image/CMakeFiles/stb_image.dir/clean:
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean.cmake
.PHONY : third_party/stb_image/CMakeFiles/stb_image.dir/clean

third_party/stb_image/CMakeFiles/stb_image.dir/depend:
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tralf/Dev/mipt-3d-graphics-course/task2 /Users/tralf/Dev/mipt-3d-graphics-course/third_party/stb_image /Users/tralf/Dev/mipt-3d-graphics-course/task2/build /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/stb_image/CMakeFiles/stb_image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third_party/stb_image/CMakeFiles/stb_image.dir/depend

