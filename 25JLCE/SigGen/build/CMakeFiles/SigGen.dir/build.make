# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Users\Euryt\Desktop\SigGen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Users\Euryt\Desktop\SigGen\build

# Include any dependencies generated for this target.
include CMakeFiles/SigGen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SigGen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SigGen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SigGen.dir/flags.make

CMakeFiles/SigGen.dir/codegen:
.PHONY : CMakeFiles/SigGen.dir/codegen

CMakeFiles/SigGen.dir/main.c.obj: CMakeFiles/SigGen.dir/flags.make
CMakeFiles/SigGen.dir/main.c.obj: CMakeFiles/SigGen.dir/includes_C.rsp
CMakeFiles/SigGen.dir/main.c.obj: D:/Users/Euryt/Desktop/SigGen/main.c
CMakeFiles/SigGen.dir/main.c.obj: CMakeFiles/SigGen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Users\Euryt\Desktop\SigGen\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SigGen.dir/main.c.obj"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SigGen.dir/main.c.obj -MF CMakeFiles\SigGen.dir\main.c.obj.d -o CMakeFiles\SigGen.dir\main.c.obj -c D:\Users\Euryt\Desktop\SigGen\main.c

CMakeFiles/SigGen.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SigGen.dir/main.c.i"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Users\Euryt\Desktop\SigGen\main.c > CMakeFiles\SigGen.dir\main.c.i

CMakeFiles/SigGen.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SigGen.dir/main.c.s"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Users\Euryt\Desktop\SigGen\main.c -o CMakeFiles\SigGen.dir\main.c.s

CMakeFiles/SigGen.dir/serial.c.obj: CMakeFiles/SigGen.dir/flags.make
CMakeFiles/SigGen.dir/serial.c.obj: CMakeFiles/SigGen.dir/includes_C.rsp
CMakeFiles/SigGen.dir/serial.c.obj: D:/Users/Euryt/Desktop/SigGen/serial.c
CMakeFiles/SigGen.dir/serial.c.obj: CMakeFiles/SigGen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Users\Euryt\Desktop\SigGen\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/SigGen.dir/serial.c.obj"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SigGen.dir/serial.c.obj -MF CMakeFiles\SigGen.dir\serial.c.obj.d -o CMakeFiles\SigGen.dir\serial.c.obj -c D:\Users\Euryt\Desktop\SigGen\serial.c

CMakeFiles/SigGen.dir/serial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SigGen.dir/serial.c.i"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Users\Euryt\Desktop\SigGen\serial.c > CMakeFiles\SigGen.dir\serial.c.i

CMakeFiles/SigGen.dir/serial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SigGen.dir/serial.c.s"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Users\Euryt\Desktop\SigGen\serial.c -o CMakeFiles\SigGen.dir\serial.c.s

CMakeFiles/SigGen.dir/DG4202.c.obj: CMakeFiles/SigGen.dir/flags.make
CMakeFiles/SigGen.dir/DG4202.c.obj: CMakeFiles/SigGen.dir/includes_C.rsp
CMakeFiles/SigGen.dir/DG4202.c.obj: D:/Users/Euryt/Desktop/SigGen/DG4202.c
CMakeFiles/SigGen.dir/DG4202.c.obj: CMakeFiles/SigGen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Users\Euryt\Desktop\SigGen\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/SigGen.dir/DG4202.c.obj"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SigGen.dir/DG4202.c.obj -MF CMakeFiles\SigGen.dir\DG4202.c.obj.d -o CMakeFiles\SigGen.dir\DG4202.c.obj -c D:\Users\Euryt\Desktop\SigGen\DG4202.c

CMakeFiles/SigGen.dir/DG4202.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SigGen.dir/DG4202.c.i"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Users\Euryt\Desktop\SigGen\DG4202.c > CMakeFiles\SigGen.dir\DG4202.c.i

CMakeFiles/SigGen.dir/DG4202.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SigGen.dir/DG4202.c.s"
	D:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Users\Euryt\Desktop\SigGen\DG4202.c -o CMakeFiles\SigGen.dir\DG4202.c.s

# Object files for target SigGen
SigGen_OBJECTS = \
"CMakeFiles/SigGen.dir/main.c.obj" \
"CMakeFiles/SigGen.dir/serial.c.obj" \
"CMakeFiles/SigGen.dir/DG4202.c.obj"

# External object files for target SigGen
SigGen_EXTERNAL_OBJECTS =

SigGen.exe: CMakeFiles/SigGen.dir/main.c.obj
SigGen.exe: CMakeFiles/SigGen.dir/serial.c.obj
SigGen.exe: CMakeFiles/SigGen.dir/DG4202.c.obj
SigGen.exe: CMakeFiles/SigGen.dir/build.make
SigGen.exe: C:/Program\ Files/IVI\ Foundation/VISA/Win64/Lib_x64/msc/visa64.lib
SigGen.exe: C:/Program\ Files/IVI\ Foundation/VISA/Win64/Lib_x64/msc/visa32.lib
SigGen.exe: C:/Program\ Files/IVI\ Foundation/VISA/Win64/Lib_x64/msc/nivisa64.lib
SigGen.exe: CMakeFiles/SigGen.dir/linkLibs.rsp
SigGen.exe: CMakeFiles/SigGen.dir/objects1.rsp
SigGen.exe: CMakeFiles/SigGen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Users\Euryt\Desktop\SigGen\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable SigGen.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SigGen.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SigGen.dir/build: SigGen.exe
.PHONY : CMakeFiles/SigGen.dir/build

CMakeFiles/SigGen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SigGen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SigGen.dir/clean

CMakeFiles/SigGen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Users\Euryt\Desktop\SigGen D:\Users\Euryt\Desktop\SigGen D:\Users\Euryt\Desktop\SigGen\build D:\Users\Euryt\Desktop\SigGen\build D:\Users\Euryt\Desktop\SigGen\build\CMakeFiles\SigGen.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SigGen.dir/depend

