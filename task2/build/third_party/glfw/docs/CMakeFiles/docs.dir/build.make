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

# Utility rule file for docs.

# Include any custom commands dependencies for this target.
include third_party/glfw/docs/CMakeFiles/docs.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/glfw/docs/CMakeFiles/docs.dir/progress.make

third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/include/GLFW/glfw3.h
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/include/GLFW/glfw3native.h
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/main.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/news.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/quick.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/moving.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/compile.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/build.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/intro.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/context.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/monitor.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/window.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/input.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/vulkan.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/compat.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/internal.dox
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/DoxygenLayout.xml
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/header.html
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/footer.html
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/extra.css
third_party/glfw/docs/html/index.html: /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs/spaces.svg
third_party/glfw/docs/html/index.html: third_party/glfw/docs/Doxyfile
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tralf/Dev/mipt-3d-graphics-course/task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating HTML documentation"
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/glfw/docs && /opt/homebrew/bin/doxygen

docs: third_party/glfw/docs/html/index.html
docs: third_party/glfw/docs/CMakeFiles/docs.dir/build.make
.PHONY : docs

# Rule to build all files generated by this target.
third_party/glfw/docs/CMakeFiles/docs.dir/build: docs
.PHONY : third_party/glfw/docs/CMakeFiles/docs.dir/build

third_party/glfw/docs/CMakeFiles/docs.dir/clean:
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/glfw/docs && $(CMAKE_COMMAND) -P CMakeFiles/docs.dir/cmake_clean.cmake
.PHONY : third_party/glfw/docs/CMakeFiles/docs.dir/clean

third_party/glfw/docs/CMakeFiles/docs.dir/depend:
	cd /Users/tralf/Dev/mipt-3d-graphics-course/task2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tralf/Dev/mipt-3d-graphics-course/task2 /Users/tralf/Dev/mipt-3d-graphics-course/third_party/glfw/docs /Users/tralf/Dev/mipt-3d-graphics-course/task2/build /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/glfw/docs /Users/tralf/Dev/mipt-3d-graphics-course/task2/build/third_party/glfw/docs/CMakeFiles/docs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third_party/glfw/docs/CMakeFiles/docs.dir/depend

