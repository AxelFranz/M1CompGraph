# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/axel/3D/easycppogl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/axel/3D/easycppogl/build

# Include any dependencies generated for this target.
include TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/compiler_depend.make

# Include the progress variables for this target.
include TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/progress.make

# Include the compile flags for this target's objects.
include TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/flags.make

TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o: TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/flags.make
TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o: /home/axel/3D/easycppogl/TP_Prog_Graphique_3D/tuto2_3.cpp
TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o: TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/axel/3D/easycppogl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o"
	cd /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o -MF CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o.d -o CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o -c /home/axel/3D/easycppogl/TP_Prog_Graphique_3D/tuto2_3.cpp

TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tuto2_3.dir/tuto2_3.cpp.i"
	cd /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/3D/easycppogl/TP_Prog_Graphique_3D/tuto2_3.cpp > CMakeFiles/tuto2_3.dir/tuto2_3.cpp.i

TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tuto2_3.dir/tuto2_3.cpp.s"
	cd /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/3D/easycppogl/TP_Prog_Graphique_3D/tuto2_3.cpp -o CMakeFiles/tuto2_3.dir/tuto2_3.cpp.s

# Object files for target tuto2_3
tuto2_3_OBJECTS = \
"CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o"

# External object files for target tuto2_3
tuto2_3_EXTERNAL_OBJECTS =

TP_Prog_Graphique_3D/tuto2_3: TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/tuto2_3.cpp.o
TP_Prog_Graphique_3D/tuto2_3: TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/build.make
TP_Prog_Graphique_3D/tuto2_3: easycppogl_src/libeasycppogl_d.a
TP_Prog_Graphique_3D/tuto2_3: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
TP_Prog_Graphique_3D/tuto2_3: /usr/lib/x86_64-linux-gnu/libassimp.so.5.3.0
TP_Prog_Graphique_3D/tuto2_3: TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/axel/3D/easycppogl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tuto2_3"
	cd /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tuto2_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/build: TP_Prog_Graphique_3D/tuto2_3
.PHONY : TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/build

TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/clean:
	cd /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D && $(CMAKE_COMMAND) -P CMakeFiles/tuto2_3.dir/cmake_clean.cmake
.PHONY : TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/clean

TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/depend:
	cd /home/axel/3D/easycppogl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/axel/3D/easycppogl /home/axel/3D/easycppogl/TP_Prog_Graphique_3D /home/axel/3D/easycppogl/build /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D /home/axel/3D/easycppogl/build/TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : TP_Prog_Graphique_3D/CMakeFiles/tuto2_3.dir/depend

