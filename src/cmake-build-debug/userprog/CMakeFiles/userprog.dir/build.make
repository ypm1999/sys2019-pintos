# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/chen/Downloads/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/chen/Downloads/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chen/pintos/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/pintos/src/cmake-build-debug

# Include any dependencies generated for this target.
include userprog/CMakeFiles/userprog.dir/depend.make

# Include the progress variables for this target.
include userprog/CMakeFiles/userprog.dir/progress.make

# Include the compile flags for this target's objects.
include userprog/CMakeFiles/userprog.dir/flags.make

userprog/CMakeFiles/userprog.dir/exception.c.o: userprog/CMakeFiles/userprog.dir/flags.make
userprog/CMakeFiles/userprog.dir/exception.c.o: ../userprog/exception.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object userprog/CMakeFiles/userprog.dir/exception.c.o"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/userprog.dir/exception.c.o   -c /home/chen/pintos/src/userprog/exception.c

userprog/CMakeFiles/userprog.dir/exception.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/userprog.dir/exception.c.i"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chen/pintos/src/userprog/exception.c > CMakeFiles/userprog.dir/exception.c.i

userprog/CMakeFiles/userprog.dir/exception.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/userprog.dir/exception.c.s"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chen/pintos/src/userprog/exception.c -o CMakeFiles/userprog.dir/exception.c.s

userprog/CMakeFiles/userprog.dir/gdt.c.o: userprog/CMakeFiles/userprog.dir/flags.make
userprog/CMakeFiles/userprog.dir/gdt.c.o: ../userprog/gdt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object userprog/CMakeFiles/userprog.dir/gdt.c.o"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/userprog.dir/gdt.c.o   -c /home/chen/pintos/src/userprog/gdt.c

userprog/CMakeFiles/userprog.dir/gdt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/userprog.dir/gdt.c.i"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chen/pintos/src/userprog/gdt.c > CMakeFiles/userprog.dir/gdt.c.i

userprog/CMakeFiles/userprog.dir/gdt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/userprog.dir/gdt.c.s"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chen/pintos/src/userprog/gdt.c -o CMakeFiles/userprog.dir/gdt.c.s

userprog/CMakeFiles/userprog.dir/pagedir.c.o: userprog/CMakeFiles/userprog.dir/flags.make
userprog/CMakeFiles/userprog.dir/pagedir.c.o: ../userprog/pagedir.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object userprog/CMakeFiles/userprog.dir/pagedir.c.o"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/userprog.dir/pagedir.c.o   -c /home/chen/pintos/src/userprog/pagedir.c

userprog/CMakeFiles/userprog.dir/pagedir.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/userprog.dir/pagedir.c.i"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chen/pintos/src/userprog/pagedir.c > CMakeFiles/userprog.dir/pagedir.c.i

userprog/CMakeFiles/userprog.dir/pagedir.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/userprog.dir/pagedir.c.s"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chen/pintos/src/userprog/pagedir.c -o CMakeFiles/userprog.dir/pagedir.c.s

userprog/CMakeFiles/userprog.dir/process.c.o: userprog/CMakeFiles/userprog.dir/flags.make
userprog/CMakeFiles/userprog.dir/process.c.o: ../userprog/process.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object userprog/CMakeFiles/userprog.dir/process.c.o"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/userprog.dir/process.c.o   -c /home/chen/pintos/src/userprog/process.c

userprog/CMakeFiles/userprog.dir/process.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/userprog.dir/process.c.i"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chen/pintos/src/userprog/process.c > CMakeFiles/userprog.dir/process.c.i

userprog/CMakeFiles/userprog.dir/process.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/userprog.dir/process.c.s"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chen/pintos/src/userprog/process.c -o CMakeFiles/userprog.dir/process.c.s

userprog/CMakeFiles/userprog.dir/syscall.c.o: userprog/CMakeFiles/userprog.dir/flags.make
userprog/CMakeFiles/userprog.dir/syscall.c.o: ../userprog/syscall.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object userprog/CMakeFiles/userprog.dir/syscall.c.o"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/userprog.dir/syscall.c.o   -c /home/chen/pintos/src/userprog/syscall.c

userprog/CMakeFiles/userprog.dir/syscall.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/userprog.dir/syscall.c.i"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chen/pintos/src/userprog/syscall.c > CMakeFiles/userprog.dir/syscall.c.i

userprog/CMakeFiles/userprog.dir/syscall.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/userprog.dir/syscall.c.s"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chen/pintos/src/userprog/syscall.c -o CMakeFiles/userprog.dir/syscall.c.s

userprog/CMakeFiles/userprog.dir/tss.c.o: userprog/CMakeFiles/userprog.dir/flags.make
userprog/CMakeFiles/userprog.dir/tss.c.o: ../userprog/tss.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object userprog/CMakeFiles/userprog.dir/tss.c.o"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/userprog.dir/tss.c.o   -c /home/chen/pintos/src/userprog/tss.c

userprog/CMakeFiles/userprog.dir/tss.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/userprog.dir/tss.c.i"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chen/pintos/src/userprog/tss.c > CMakeFiles/userprog.dir/tss.c.i

userprog/CMakeFiles/userprog.dir/tss.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/userprog.dir/tss.c.s"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chen/pintos/src/userprog/tss.c -o CMakeFiles/userprog.dir/tss.c.s

# Object files for target userprog
userprog_OBJECTS = \
"CMakeFiles/userprog.dir/exception.c.o" \
"CMakeFiles/userprog.dir/gdt.c.o" \
"CMakeFiles/userprog.dir/pagedir.c.o" \
"CMakeFiles/userprog.dir/process.c.o" \
"CMakeFiles/userprog.dir/syscall.c.o" \
"CMakeFiles/userprog.dir/tss.c.o"

# External object files for target userprog
userprog_EXTERNAL_OBJECTS =

userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/exception.c.o
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/gdt.c.o
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/pagedir.c.o
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/process.c.o
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/syscall.c.o
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/tss.c.o
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/build.make
userprog/libuserprog.a: userprog/CMakeFiles/userprog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/pintos/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C static library libuserprog.a"
	cd /home/chen/pintos/src/cmake-build-debug/userprog && $(CMAKE_COMMAND) -P CMakeFiles/userprog.dir/cmake_clean_target.cmake
	cd /home/chen/pintos/src/cmake-build-debug/userprog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/userprog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
userprog/CMakeFiles/userprog.dir/build: userprog/libuserprog.a

.PHONY : userprog/CMakeFiles/userprog.dir/build

userprog/CMakeFiles/userprog.dir/clean:
	cd /home/chen/pintos/src/cmake-build-debug/userprog && $(CMAKE_COMMAND) -P CMakeFiles/userprog.dir/cmake_clean.cmake
.PHONY : userprog/CMakeFiles/userprog.dir/clean

userprog/CMakeFiles/userprog.dir/depend:
	cd /home/chen/pintos/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/pintos/src /home/chen/pintos/src/userprog /home/chen/pintos/src/cmake-build-debug /home/chen/pintos/src/cmake-build-debug/userprog /home/chen/pintos/src/cmake-build-debug/userprog/CMakeFiles/userprog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : userprog/CMakeFiles/userprog.dir/depend
