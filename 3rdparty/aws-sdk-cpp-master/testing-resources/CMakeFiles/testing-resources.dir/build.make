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
CMAKE_SOURCE_DIR = /home/prateeks/code/aws-sdk-cpp-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/prateeks/code/aws-sdk-cpp-master

# Include any dependencies generated for this target.
include testing-resources/CMakeFiles/testing-resources.dir/depend.make

# Include the progress variables for this target.
include testing-resources/CMakeFiles/testing-resources.dir/progress.make

# Include the compile flags for this target's objects.
include testing-resources/CMakeFiles/testing-resources.dir/flags.make

testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o: testing-resources/CMakeFiles/testing-resources.dir/flags.make
testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o: testing-resources/CMakeFiles/testing-resources.dir/includes_CXX.rsp
testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o: testing-resources/source/MemoryTesting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/prateeks/code/aws-sdk-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o -c /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/MemoryTesting.cpp

testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.i"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/MemoryTesting.cpp > CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.i

testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.s"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/MemoryTesting.cpp -o CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.s

testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.requires:

.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.requires

testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.provides: testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.requires
	$(MAKE) -f testing-resources/CMakeFiles/testing-resources.dir/build.make testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.provides.build
.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.provides

testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.provides.build: testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o


testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o: testing-resources/CMakeFiles/testing-resources.dir/flags.make
testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o: testing-resources/CMakeFiles/testing-resources.dir/includes_CXX.rsp
testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o: testing-resources/source/TestingEnvironment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/prateeks/code/aws-sdk-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o -c /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/TestingEnvironment.cpp

testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.i"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/TestingEnvironment.cpp > CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.i

testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.s"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/TestingEnvironment.cpp -o CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.s

testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.requires:

.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.requires

testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.provides: testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.requires
	$(MAKE) -f testing-resources/CMakeFiles/testing-resources.dir/build.make testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.provides.build
.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.provides

testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.provides.build: testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o


testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o: testing-resources/CMakeFiles/testing-resources.dir/flags.make
testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o: testing-resources/CMakeFiles/testing-resources.dir/includes_CXX.rsp
testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o: testing-resources/source/external/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/prateeks/code/aws-sdk-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o -c /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/external/gtest-all.cc

testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.i"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/external/gtest-all.cc > CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.i

testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.s"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/external/gtest-all.cc -o CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.s

testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.requires:

.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.requires

testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.provides: testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.requires
	$(MAKE) -f testing-resources/CMakeFiles/testing-resources.dir/build.make testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.provides.build
.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.provides

testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.provides.build: testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o


testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o: testing-resources/CMakeFiles/testing-resources.dir/flags.make
testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o: testing-resources/CMakeFiles/testing-resources.dir/includes_CXX.rsp
testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o: testing-resources/source/platform/linux-shared/PlatformTesting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/prateeks/code/aws-sdk-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o -c /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/platform/linux-shared/PlatformTesting.cpp

testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.i"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/platform/linux-shared/PlatformTesting.cpp > CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.i

testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.s"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/prateeks/code/aws-sdk-cpp-master/testing-resources/source/platform/linux-shared/PlatformTesting.cpp -o CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.s

testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.requires:

.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.requires

testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.provides: testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.requires
	$(MAKE) -f testing-resources/CMakeFiles/testing-resources.dir/build.make testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.provides.build
.PHONY : testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.provides

testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.provides.build: testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o


# Object files for target testing-resources
testing__resources_OBJECTS = \
"CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o" \
"CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o" \
"CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o" \
"CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o"

# External object files for target testing-resources
testing__resources_EXTERNAL_OBJECTS =

testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o
testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o
testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o
testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o
testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/build.make
testing-resources/libtesting-resources.so: aws-cpp-sdk-core/libaws-cpp-sdk-core.so
testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/objects1.rsp
testing-resources/libtesting-resources.so: testing-resources/CMakeFiles/testing-resources.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/prateeks/code/aws-sdk-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libtesting-resources.so"
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testing-resources.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
testing-resources/CMakeFiles/testing-resources.dir/build: testing-resources/libtesting-resources.so

.PHONY : testing-resources/CMakeFiles/testing-resources.dir/build

testing-resources/CMakeFiles/testing-resources.dir/requires: testing-resources/CMakeFiles/testing-resources.dir/source/MemoryTesting.cpp.o.requires
testing-resources/CMakeFiles/testing-resources.dir/requires: testing-resources/CMakeFiles/testing-resources.dir/source/TestingEnvironment.cpp.o.requires
testing-resources/CMakeFiles/testing-resources.dir/requires: testing-resources/CMakeFiles/testing-resources.dir/source/external/gtest-all.cc.o.requires
testing-resources/CMakeFiles/testing-resources.dir/requires: testing-resources/CMakeFiles/testing-resources.dir/source/platform/linux-shared/PlatformTesting.cpp.o.requires

.PHONY : testing-resources/CMakeFiles/testing-resources.dir/requires

testing-resources/CMakeFiles/testing-resources.dir/clean:
	cd /home/prateeks/code/aws-sdk-cpp-master/testing-resources && $(CMAKE_COMMAND) -P CMakeFiles/testing-resources.dir/cmake_clean.cmake
.PHONY : testing-resources/CMakeFiles/testing-resources.dir/clean

testing-resources/CMakeFiles/testing-resources.dir/depend:
	cd /home/prateeks/code/aws-sdk-cpp-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/prateeks/code/aws-sdk-cpp-master /home/prateeks/code/aws-sdk-cpp-master/testing-resources /home/prateeks/code/aws-sdk-cpp-master /home/prateeks/code/aws-sdk-cpp-master/testing-resources /home/prateeks/code/aws-sdk-cpp-master/testing-resources/CMakeFiles/testing-resources.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testing-resources/CMakeFiles/testing-resources.dir/depend

