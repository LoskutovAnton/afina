# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/antonloskutov/project_c/afina

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antonloskutov/project_c/afina

# Include any dependencies generated for this target.
include third-party/backward-cpp/CMakeFiles/backward_object.dir/depend.make

# Include the progress variables for this target.
include third-party/backward-cpp/CMakeFiles/backward_object.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/backward-cpp/CMakeFiles/backward_object.dir/flags.make

third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o: third-party/backward-cpp/CMakeFiles/backward_object.dir/flags.make
third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o: third-party/backward-cpp/backward.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antonloskutov/project_c/afina/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o"
	cd /home/antonloskutov/project_c/afina/third-party/backward-cpp && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backward_object.dir/backward.cpp.o -c /home/antonloskutov/project_c/afina/third-party/backward-cpp/backward.cpp

third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backward_object.dir/backward.cpp.i"
	cd /home/antonloskutov/project_c/afina/third-party/backward-cpp && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antonloskutov/project_c/afina/third-party/backward-cpp/backward.cpp > CMakeFiles/backward_object.dir/backward.cpp.i

third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backward_object.dir/backward.cpp.s"
	cd /home/antonloskutov/project_c/afina/third-party/backward-cpp && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antonloskutov/project_c/afina/third-party/backward-cpp/backward.cpp -o CMakeFiles/backward_object.dir/backward.cpp.s

third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.requires:

.PHONY : third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.requires

third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.provides: third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.requires
	$(MAKE) -f third-party/backward-cpp/CMakeFiles/backward_object.dir/build.make third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.provides.build
.PHONY : third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.provides

third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.provides.build: third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o


backward_object: third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o
backward_object: third-party/backward-cpp/CMakeFiles/backward_object.dir/build.make

.PHONY : backward_object

# Rule to build all files generated by this target.
third-party/backward-cpp/CMakeFiles/backward_object.dir/build: backward_object

.PHONY : third-party/backward-cpp/CMakeFiles/backward_object.dir/build

third-party/backward-cpp/CMakeFiles/backward_object.dir/requires: third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o.requires

.PHONY : third-party/backward-cpp/CMakeFiles/backward_object.dir/requires

third-party/backward-cpp/CMakeFiles/backward_object.dir/clean:
	cd /home/antonloskutov/project_c/afina/third-party/backward-cpp && $(CMAKE_COMMAND) -P CMakeFiles/backward_object.dir/cmake_clean.cmake
.PHONY : third-party/backward-cpp/CMakeFiles/backward_object.dir/clean

third-party/backward-cpp/CMakeFiles/backward_object.dir/depend:
	cd /home/antonloskutov/project_c/afina && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antonloskutov/project_c/afina /home/antonloskutov/project_c/afina/third-party/backward-cpp /home/antonloskutov/project_c/afina /home/antonloskutov/project_c/afina/third-party/backward-cpp /home/antonloskutov/project_c/afina/third-party/backward-cpp/CMakeFiles/backward_object.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/backward-cpp/CMakeFiles/backward_object.dir/depend

