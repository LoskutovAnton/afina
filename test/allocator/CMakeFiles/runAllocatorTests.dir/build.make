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
include test/allocator/CMakeFiles/runAllocatorTests.dir/depend.make

# Include the progress variables for this target.
include test/allocator/CMakeFiles/runAllocatorTests.dir/progress.make

# Include the compile flags for this target's objects.
include test/allocator/CMakeFiles/runAllocatorTests.dir/flags.make

test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o: test/allocator/CMakeFiles/runAllocatorTests.dir/flags.make
test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o: test/allocator/SimpleTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antonloskutov/project_c/afina/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o"
	cd /home/antonloskutov/project_c/afina/test/allocator && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o -c /home/antonloskutov/project_c/afina/test/allocator/SimpleTest.cpp

test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.i"
	cd /home/antonloskutov/project_c/afina/test/allocator && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antonloskutov/project_c/afina/test/allocator/SimpleTest.cpp > CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.i

test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.s"
	cd /home/antonloskutov/project_c/afina/test/allocator && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antonloskutov/project_c/afina/test/allocator/SimpleTest.cpp -o CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.s

test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.requires:

.PHONY : test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.requires

test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.provides: test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.requires
	$(MAKE) -f test/allocator/CMakeFiles/runAllocatorTests.dir/build.make test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.provides.build
.PHONY : test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.provides

test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.provides.build: test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o


# Object files for target runAllocatorTests
runAllocatorTests_OBJECTS = \
"CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o"

# External object files for target runAllocatorTests
runAllocatorTests_EXTERNAL_OBJECTS = \
"/home/antonloskutov/project_c/afina/third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o"

test/allocator/runAllocatorTests: test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o
test/allocator/runAllocatorTests: third-party/backward-cpp/CMakeFiles/backward_object.dir/backward.cpp.o
test/allocator/runAllocatorTests: test/allocator/CMakeFiles/runAllocatorTests.dir/build.make
test/allocator/runAllocatorTests: src/allocator/libAllocator.a
test/allocator/runAllocatorTests: third-party/googletest-release-1.8.0/googlemock/gtest/libgtest.a
test/allocator/runAllocatorTests: third-party/googletest-release-1.8.0/googlemock/gtest/libgtest_main.a
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: /usr/lib/x86_64-linux-gnu/libdw.so
test/allocator/runAllocatorTests: third-party/googletest-release-1.8.0/googlemock/gtest/libgtest.a
test/allocator/runAllocatorTests: test/allocator/CMakeFiles/runAllocatorTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/antonloskutov/project_c/afina/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable runAllocatorTests"
	cd /home/antonloskutov/project_c/afina/test/allocator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runAllocatorTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/allocator/CMakeFiles/runAllocatorTests.dir/build: test/allocator/runAllocatorTests

.PHONY : test/allocator/CMakeFiles/runAllocatorTests.dir/build

test/allocator/CMakeFiles/runAllocatorTests.dir/requires: test/allocator/CMakeFiles/runAllocatorTests.dir/SimpleTest.cpp.o.requires

.PHONY : test/allocator/CMakeFiles/runAllocatorTests.dir/requires

test/allocator/CMakeFiles/runAllocatorTests.dir/clean:
	cd /home/antonloskutov/project_c/afina/test/allocator && $(CMAKE_COMMAND) -P CMakeFiles/runAllocatorTests.dir/cmake_clean.cmake
.PHONY : test/allocator/CMakeFiles/runAllocatorTests.dir/clean

test/allocator/CMakeFiles/runAllocatorTests.dir/depend:
	cd /home/antonloskutov/project_c/afina && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antonloskutov/project_c/afina /home/antonloskutov/project_c/afina/test/allocator /home/antonloskutov/project_c/afina /home/antonloskutov/project_c/afina/test/allocator /home/antonloskutov/project_c/afina/test/allocator/CMakeFiles/runAllocatorTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/allocator/CMakeFiles/runAllocatorTests.dir/depend

