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
include src/allocator/CMakeFiles/Allocator.dir/depend.make

# Include the progress variables for this target.
include src/allocator/CMakeFiles/Allocator.dir/progress.make

# Include the compile flags for this target's objects.
include src/allocator/CMakeFiles/Allocator.dir/flags.make

src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o: src/allocator/CMakeFiles/Allocator.dir/flags.make
src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o: src/allocator/Simple.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antonloskutov/project_c/afina/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o"
	cd /home/antonloskutov/project_c/afina/src/allocator && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Allocator.dir/Simple.cpp.o -c /home/antonloskutov/project_c/afina/src/allocator/Simple.cpp

src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Allocator.dir/Simple.cpp.i"
	cd /home/antonloskutov/project_c/afina/src/allocator && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antonloskutov/project_c/afina/src/allocator/Simple.cpp > CMakeFiles/Allocator.dir/Simple.cpp.i

src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Allocator.dir/Simple.cpp.s"
	cd /home/antonloskutov/project_c/afina/src/allocator && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antonloskutov/project_c/afina/src/allocator/Simple.cpp -o CMakeFiles/Allocator.dir/Simple.cpp.s

src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.requires:

.PHONY : src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.requires

src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.provides: src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.requires
	$(MAKE) -f src/allocator/CMakeFiles/Allocator.dir/build.make src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.provides.build
.PHONY : src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.provides

src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.provides.build: src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o


src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o: src/allocator/CMakeFiles/Allocator.dir/flags.make
src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o: src/allocator/Pointer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antonloskutov/project_c/afina/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o"
	cd /home/antonloskutov/project_c/afina/src/allocator && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Allocator.dir/Pointer.cpp.o -c /home/antonloskutov/project_c/afina/src/allocator/Pointer.cpp

src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Allocator.dir/Pointer.cpp.i"
	cd /home/antonloskutov/project_c/afina/src/allocator && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antonloskutov/project_c/afina/src/allocator/Pointer.cpp > CMakeFiles/Allocator.dir/Pointer.cpp.i

src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Allocator.dir/Pointer.cpp.s"
	cd /home/antonloskutov/project_c/afina/src/allocator && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antonloskutov/project_c/afina/src/allocator/Pointer.cpp -o CMakeFiles/Allocator.dir/Pointer.cpp.s

src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.requires:

.PHONY : src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.requires

src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.provides: src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.requires
	$(MAKE) -f src/allocator/CMakeFiles/Allocator.dir/build.make src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.provides.build
.PHONY : src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.provides

src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.provides.build: src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o


# Object files for target Allocator
Allocator_OBJECTS = \
"CMakeFiles/Allocator.dir/Simple.cpp.o" \
"CMakeFiles/Allocator.dir/Pointer.cpp.o"

# External object files for target Allocator
Allocator_EXTERNAL_OBJECTS =

src/allocator/libAllocator.a: src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o
src/allocator/libAllocator.a: src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o
src/allocator/libAllocator.a: src/allocator/CMakeFiles/Allocator.dir/build.make
src/allocator/libAllocator.a: src/allocator/CMakeFiles/Allocator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/antonloskutov/project_c/afina/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libAllocator.a"
	cd /home/antonloskutov/project_c/afina/src/allocator && $(CMAKE_COMMAND) -P CMakeFiles/Allocator.dir/cmake_clean_target.cmake
	cd /home/antonloskutov/project_c/afina/src/allocator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Allocator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/allocator/CMakeFiles/Allocator.dir/build: src/allocator/libAllocator.a

.PHONY : src/allocator/CMakeFiles/Allocator.dir/build

src/allocator/CMakeFiles/Allocator.dir/requires: src/allocator/CMakeFiles/Allocator.dir/Simple.cpp.o.requires
src/allocator/CMakeFiles/Allocator.dir/requires: src/allocator/CMakeFiles/Allocator.dir/Pointer.cpp.o.requires

.PHONY : src/allocator/CMakeFiles/Allocator.dir/requires

src/allocator/CMakeFiles/Allocator.dir/clean:
	cd /home/antonloskutov/project_c/afina/src/allocator && $(CMAKE_COMMAND) -P CMakeFiles/Allocator.dir/cmake_clean.cmake
.PHONY : src/allocator/CMakeFiles/Allocator.dir/clean

src/allocator/CMakeFiles/Allocator.dir/depend:
	cd /home/antonloskutov/project_c/afina && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antonloskutov/project_c/afina /home/antonloskutov/project_c/afina/src/allocator /home/antonloskutov/project_c/afina /home/antonloskutov/project_c/afina/src/allocator /home/antonloskutov/project_c/afina/src/allocator/CMakeFiles/Allocator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/allocator/CMakeFiles/Allocator.dir/depend

