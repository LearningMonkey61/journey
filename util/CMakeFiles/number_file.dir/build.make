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
CMAKE_SOURCE_DIR = /home/pntandcnt/study/c++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pntandcnt/study/c++

# Include any dependencies generated for this target.
include util/CMakeFiles/number_file.dir/depend.make

# Include the progress variables for this target.
include util/CMakeFiles/number_file.dir/progress.make

# Include the compile flags for this target's objects.
include util/CMakeFiles/number_file.dir/flags.make

util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o: util/CMakeFiles/number_file.dir/flags.make
util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o: util/number_file/number_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pntandcnt/study/c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o"
	cd /home/pntandcnt/study/c++/util && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/number_file.dir/number_file/number_file.cpp.o -c /home/pntandcnt/study/c++/util/number_file/number_file.cpp

util/CMakeFiles/number_file.dir/number_file/number_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/number_file.dir/number_file/number_file.cpp.i"
	cd /home/pntandcnt/study/c++/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pntandcnt/study/c++/util/number_file/number_file.cpp > CMakeFiles/number_file.dir/number_file/number_file.cpp.i

util/CMakeFiles/number_file.dir/number_file/number_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/number_file.dir/number_file/number_file.cpp.s"
	cd /home/pntandcnt/study/c++/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pntandcnt/study/c++/util/number_file/number_file.cpp -o CMakeFiles/number_file.dir/number_file/number_file.cpp.s

util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.requires:

.PHONY : util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.requires

util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.provides: util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.requires
	$(MAKE) -f util/CMakeFiles/number_file.dir/build.make util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.provides.build
.PHONY : util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.provides

util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.provides.build: util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o


# Object files for target number_file
number_file_OBJECTS = \
"CMakeFiles/number_file.dir/number_file/number_file.cpp.o"

# External object files for target number_file
number_file_EXTERNAL_OBJECTS =

bin/number_file: util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o
bin/number_file: util/CMakeFiles/number_file.dir/build.make
bin/number_file: lib/libcommond.a
bin/number_file: /usr/local/lib/libboost_program_options.so
bin/number_file: /usr/local/lib/libboost_filesystem.so
bin/number_file: /usr/local/lib/libboost_system.so
bin/number_file: util/CMakeFiles/number_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pntandcnt/study/c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/number_file"
	cd /home/pntandcnt/study/c++/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/number_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
util/CMakeFiles/number_file.dir/build: bin/number_file

.PHONY : util/CMakeFiles/number_file.dir/build

util/CMakeFiles/number_file.dir/requires: util/CMakeFiles/number_file.dir/number_file/number_file.cpp.o.requires

.PHONY : util/CMakeFiles/number_file.dir/requires

util/CMakeFiles/number_file.dir/clean:
	cd /home/pntandcnt/study/c++/util && $(CMAKE_COMMAND) -P CMakeFiles/number_file.dir/cmake_clean.cmake
.PHONY : util/CMakeFiles/number_file.dir/clean

util/CMakeFiles/number_file.dir/depend:
	cd /home/pntandcnt/study/c++ && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pntandcnt/study/c++ /home/pntandcnt/study/c++/util /home/pntandcnt/study/c++ /home/pntandcnt/study/c++/util /home/pntandcnt/study/c++/util/CMakeFiles/number_file.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : util/CMakeFiles/number_file.dir/depend

