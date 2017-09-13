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
CMAKE_SOURCE_DIR = "/home/suporte/Área de Trabalho/pc"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/suporte/Área de Trabalho/pc/build"

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

scanner.c: ../scanner.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "[FLEX][scanner] Building scanner with flex 2.6.0"
	cd "/home/suporte/Área de Trabalho/pc" && /usr/bin/flex -o/home/suporte/Área\ de\ Trabalho/pc/build/scanner.c scanner.l

parser.c: ../parser.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "[BISON][parser] Building parser with bison 3.0.4"
	cd "/home/suporte/Área de Trabalho/pc" && /usr/bin/bison --verbose -d -o /home/suporte/Área\ de\ Trabalho/pc/build/parser.c parser.y

parser.h: parser.c
	@$(CMAKE_COMMAND) -E touch_nocreate parser.h

parser.output: parser.c
	@$(CMAKE_COMMAND) -E touch_nocreate parser.output

CMakeFiles/main.dir/scanner.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/scanner.c.o: scanner.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/scanner.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/scanner.c.o   -c "/home/suporte/Área de Trabalho/pc/build/scanner.c"

CMakeFiles/main.dir/scanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/scanner.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/build/scanner.c" > CMakeFiles/main.dir/scanner.c.i

CMakeFiles/main.dir/scanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/scanner.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/build/scanner.c" -o CMakeFiles/main.dir/scanner.c.s

CMakeFiles/main.dir/scanner.c.o.requires:

.PHONY : CMakeFiles/main.dir/scanner.c.o.requires

CMakeFiles/main.dir/scanner.c.o.provides: CMakeFiles/main.dir/scanner.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/scanner.c.o.provides.build
.PHONY : CMakeFiles/main.dir/scanner.c.o.provides

CMakeFiles/main.dir/scanner.c.o.provides.build: CMakeFiles/main.dir/scanner.c.o


CMakeFiles/main.dir/parser.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/parser.c.o: parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/parser.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/parser.c.o   -c "/home/suporte/Área de Trabalho/pc/build/parser.c"

CMakeFiles/main.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/parser.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/build/parser.c" > CMakeFiles/main.dir/parser.c.i

CMakeFiles/main.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/parser.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/build/parser.c" -o CMakeFiles/main.dir/parser.c.s

CMakeFiles/main.dir/parser.c.o.requires:

.PHONY : CMakeFiles/main.dir/parser.c.o.requires

CMakeFiles/main.dir/parser.c.o.provides: CMakeFiles/main.dir/parser.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/parser.c.o.provides.build
.PHONY : CMakeFiles/main.dir/parser.c.o.provides

CMakeFiles/main.dir/parser.c.o.provides.build: CMakeFiles/main.dir/parser.c.o


CMakeFiles/main.dir/src/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/src/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/main.c.o   -c "/home/suporte/Área de Trabalho/pc/src/main.c"

CMakeFiles/main.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/src/main.c" > CMakeFiles/main.dir/src/main.c.i

CMakeFiles/main.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/src/main.c" -o CMakeFiles/main.dir/src/main.c.s

CMakeFiles/main.dir/src/main.c.o.requires:

.PHONY : CMakeFiles/main.dir/src/main.c.o.requires

CMakeFiles/main.dir/src/main.c.o.provides: CMakeFiles/main.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/main.c.o.provides

CMakeFiles/main.dir/src/main.c.o.provides.build: CMakeFiles/main.dir/src/main.c.o


CMakeFiles/main.dir/src/cc_misc.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/cc_misc.c.o: ../src/cc_misc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/src/cc_misc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/cc_misc.c.o   -c "/home/suporte/Área de Trabalho/pc/src/cc_misc.c"

CMakeFiles/main.dir/src/cc_misc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/cc_misc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/src/cc_misc.c" > CMakeFiles/main.dir/src/cc_misc.c.i

CMakeFiles/main.dir/src/cc_misc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/cc_misc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/src/cc_misc.c" -o CMakeFiles/main.dir/src/cc_misc.c.s

CMakeFiles/main.dir/src/cc_misc.c.o.requires:

.PHONY : CMakeFiles/main.dir/src/cc_misc.c.o.requires

CMakeFiles/main.dir/src/cc_misc.c.o.provides: CMakeFiles/main.dir/src/cc_misc.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/cc_misc.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/cc_misc.c.o.provides

CMakeFiles/main.dir/src/cc_misc.c.o.provides.build: CMakeFiles/main.dir/src/cc_misc.c.o


CMakeFiles/main.dir/src/cc_gv.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/cc_gv.c.o: ../src/cc_gv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/main.dir/src/cc_gv.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/cc_gv.c.o   -c "/home/suporte/Área de Trabalho/pc/src/cc_gv.c"

CMakeFiles/main.dir/src/cc_gv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/cc_gv.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/src/cc_gv.c" > CMakeFiles/main.dir/src/cc_gv.c.i

CMakeFiles/main.dir/src/cc_gv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/cc_gv.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/src/cc_gv.c" -o CMakeFiles/main.dir/src/cc_gv.c.s

CMakeFiles/main.dir/src/cc_gv.c.o.requires:

.PHONY : CMakeFiles/main.dir/src/cc_gv.c.o.requires

CMakeFiles/main.dir/src/cc_gv.c.o.provides: CMakeFiles/main.dir/src/cc_gv.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/cc_gv.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/cc_gv.c.o.provides

CMakeFiles/main.dir/src/cc_gv.c.o.provides.build: CMakeFiles/main.dir/src/cc_gv.c.o


CMakeFiles/main.dir/src/cc_dict.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/cc_dict.c.o: ../src/cc_dict.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/main.dir/src/cc_dict.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/cc_dict.c.o   -c "/home/suporte/Área de Trabalho/pc/src/cc_dict.c"

CMakeFiles/main.dir/src/cc_dict.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/cc_dict.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/src/cc_dict.c" > CMakeFiles/main.dir/src/cc_dict.c.i

CMakeFiles/main.dir/src/cc_dict.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/cc_dict.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/src/cc_dict.c" -o CMakeFiles/main.dir/src/cc_dict.c.s

CMakeFiles/main.dir/src/cc_dict.c.o.requires:

.PHONY : CMakeFiles/main.dir/src/cc_dict.c.o.requires

CMakeFiles/main.dir/src/cc_dict.c.o.provides: CMakeFiles/main.dir/src/cc_dict.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/cc_dict.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/cc_dict.c.o.provides

CMakeFiles/main.dir/src/cc_dict.c.o.provides.build: CMakeFiles/main.dir/src/cc_dict.c.o


CMakeFiles/main.dir/src/cc_list.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/cc_list.c.o: ../src/cc_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/main.dir/src/cc_list.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/cc_list.c.o   -c "/home/suporte/Área de Trabalho/pc/src/cc_list.c"

CMakeFiles/main.dir/src/cc_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/cc_list.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/src/cc_list.c" > CMakeFiles/main.dir/src/cc_list.c.i

CMakeFiles/main.dir/src/cc_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/cc_list.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/src/cc_list.c" -o CMakeFiles/main.dir/src/cc_list.c.s

CMakeFiles/main.dir/src/cc_list.c.o.requires:

.PHONY : CMakeFiles/main.dir/src/cc_list.c.o.requires

CMakeFiles/main.dir/src/cc_list.c.o.provides: CMakeFiles/main.dir/src/cc_list.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/cc_list.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/cc_list.c.o.provides

CMakeFiles/main.dir/src/cc_list.c.o.provides.build: CMakeFiles/main.dir/src/cc_list.c.o


CMakeFiles/main.dir/src/cc_tree.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/cc_tree.c.o: ../src/cc_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/main.dir/src/cc_tree.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/cc_tree.c.o   -c "/home/suporte/Área de Trabalho/pc/src/cc_tree.c"

CMakeFiles/main.dir/src/cc_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/cc_tree.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/suporte/Área de Trabalho/pc/src/cc_tree.c" > CMakeFiles/main.dir/src/cc_tree.c.i

CMakeFiles/main.dir/src/cc_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/cc_tree.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/suporte/Área de Trabalho/pc/src/cc_tree.c" -o CMakeFiles/main.dir/src/cc_tree.c.s

CMakeFiles/main.dir/src/cc_tree.c.o.requires:

.PHONY : CMakeFiles/main.dir/src/cc_tree.c.o.requires

CMakeFiles/main.dir/src/cc_tree.c.o.provides: CMakeFiles/main.dir/src/cc_tree.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/cc_tree.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/cc_tree.c.o.provides

CMakeFiles/main.dir/src/cc_tree.c.o.provides.build: CMakeFiles/main.dir/src/cc_tree.c.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/scanner.c.o" \
"CMakeFiles/main.dir/parser.c.o" \
"CMakeFiles/main.dir/src/main.c.o" \
"CMakeFiles/main.dir/src/cc_misc.c.o" \
"CMakeFiles/main.dir/src/cc_gv.c.o" \
"CMakeFiles/main.dir/src/cc_dict.c.o" \
"CMakeFiles/main.dir/src/cc_list.c.o" \
"CMakeFiles/main.dir/src/cc_tree.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/scanner.c.o
main: CMakeFiles/main.dir/parser.c.o
main: CMakeFiles/main.dir/src/main.c.o
main: CMakeFiles/main.dir/src/cc_misc.c.o
main: CMakeFiles/main.dir/src/cc_gv.c.o
main: CMakeFiles/main.dir/src/cc_dict.c.o
main: CMakeFiles/main.dir/src/cc_list.c.o
main: CMakeFiles/main.dir/src/cc_tree.c.o
main: CMakeFiles/main.dir/build.make
main: /usr/lib/x86_64-linux-gnu/libfl.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/suporte/Área de Trabalho/pc/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/scanner.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/parser.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/main.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/cc_misc.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/cc_gv.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/cc_dict.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/cc_list.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/cc_tree.c.o.requires

.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend: scanner.c
CMakeFiles/main.dir/depend: parser.c
CMakeFiles/main.dir/depend: parser.h
CMakeFiles/main.dir/depend: parser.output
	cd "/home/suporte/Área de Trabalho/pc/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/suporte/Área de Trabalho/pc" "/home/suporte/Área de Trabalho/pc" "/home/suporte/Área de Trabalho/pc/build" "/home/suporte/Área de Trabalho/pc/build" "/home/suporte/Área de Trabalho/pc/build/CMakeFiles/main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

