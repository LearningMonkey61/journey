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
include algorithm/CMakeFiles/binary_search.dir/depend.make

# Include the progress variables for this target.
include algorithm/CMakeFiles/binary_search.dir/progress.make

# Include the compile flags for this target's objects.
include algorithm/CMakeFiles/binary_search.dir/flags.make

algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o: algorithm/CMakeFiles/binary_search.dir/flags.make
algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o: algorithm/binary_search/binary_search.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pntandcnt/study/c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o"
	cd /home/pntandcnt/study/c++/algorithm && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o -c /home/pntandcnt/study/c++/algorithm/binary_search/binary_search.cpp

algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.i"
	cd /home/pntandcnt/study/c++/algorithm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pntandcnt/study/c++/algorithm/binary_search/binary_search.cpp > CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.i

algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.s"
	cd /home/pntandcnt/study/c++/algorithm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pntandcnt/study/c++/algorithm/binary_search/binary_search.cpp -o CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.s

algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.requires:

.PHONY : algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.requires

algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.provides: algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.requires
	$(MAKE) -f algorithm/CMakeFiles/binary_search.dir/build.make algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.provides.build
.PHONY : algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.provides

algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.provides.build: algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o


# Object files for target binary_search
binary_search_OBJECTS = \
"CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o"

# External object files for target binary_search
binary_search_EXTERNAL_OBJECTS =

bin/binary_search: algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o
bin/binary_search: algorithm/CMakeFiles/binary_search.dir/build.make
bin/binary_search: lib/libcommond.a
bin/binary_search: /usr/local/lib/libboost_program_options.so
bin/binary_search: /usr/local/lib/libboost_filesystem.so
bin/binary_search: /usr/local/lib/libboost_system.so
bin/binary_search: algorithm/CMakeFiles/binary_search.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pntandcnt/study/c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/binary_search"
	cd /home/pntandcnt/study/c++/algorithm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binary_search.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
algorithm/CMakeFiles/binary_search.dir/build: bin/binary_search

.PHONY : algorithm/CMakeFiles/binary_search.dir/build

algorithm/CMakeFiles/binary_search.dir/requires: algorithm/CMakeFiles/binary_search.dir/binary_search/binary_search.cpp.o.requires

.PHONY : algorithm/CMakeFiles/binary_search.dir/requires

algorithm/CMakeFiles/binary_search.dir/clean:
	cd /home/pntandcnt/study/c++/algorithm && $(CMAKE_COMMAND) -P CMakeFiles/binary_search.dir/cmake_clean.cmake
.PHONY : algorithm/CMakeFiles/binary_search.dir/clean

algorithm/CMakeFiles/binary_search.dir/depend:
	cd /home/pntandcnt/study/c++ && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pntandcnt/study/c++ /home/pntandcnt/study/c++/algorithm /home/pntandcnt/study/c++ /home/pntandcnt/study/c++/algorithm /home/pntandcnt/study/c++/algorithm/CMakeFiles/binary_search.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : algorithm/CMakeFiles/binary_search.dir/depend

