# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = C:\cmake-3.20.2-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = C:\cmake-3.20.2-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = H:\vscodeprj\leetcodeCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = H:\vscodeprj\leetcodeCPP\build

# Include any dependencies generated for this target.
include CMakeFiles/leetcodeCPP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/leetcodeCPP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/leetcodeCPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/leetcodeCPP.dir/flags.make

CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj: CMakeFiles/leetcodeCPP.dir/flags.make
CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj: CMakeFiles/leetcodeCPP.dir/includes_CXX.rsp
CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj: ../src/main.cpp
CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj: CMakeFiles/leetcodeCPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=H:\vscodeprj\leetcodeCPP\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj"
	C:\PROGRA~1\LLVM\bin\CLANG_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj -MF CMakeFiles\leetcodeCPP.dir\src\main.cpp.obj.d -o CMakeFiles\leetcodeCPP.dir\src\main.cpp.obj -c H:\vscodeprj\leetcodeCPP\src\main.cpp

CMakeFiles/leetcodeCPP.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leetcodeCPP.dir/src/main.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles/leetcodeCPP.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leetcodeCPP.dir/src/main.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

# Object files for target leetcodeCPP
leetcodeCPP_OBJECTS = \
"CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj"

# External object files for target leetcodeCPP
leetcodeCPP_EXTERNAL_OBJECTS =

leetcodeCPP.exe: CMakeFiles/leetcodeCPP.dir/src/main.cpp.obj
leetcodeCPP.exe: CMakeFiles/leetcodeCPP.dir/build.make
leetcodeCPP.exe: CMakeFiles/leetcodeCPP.dir/linklibs.rsp
leetcodeCPP.exe: CMakeFiles/leetcodeCPP.dir/objects1.rsp
leetcodeCPP.exe: CMakeFiles/leetcodeCPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=H:\vscodeprj\leetcodeCPP\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable leetcodeCPP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\leetcodeCPP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/leetcodeCPP.dir/build: leetcodeCPP.exe
.PHONY : CMakeFiles/leetcodeCPP.dir/build

CMakeFiles/leetcodeCPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\leetcodeCPP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/leetcodeCPP.dir/clean

CMakeFiles/leetcodeCPP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" H:\vscodeprj\leetcodeCPP H:\vscodeprj\leetcodeCPP H:\vscodeprj\leetcodeCPP\build H:\vscodeprj\leetcodeCPP\build H:\vscodeprj\leetcodeCPP\build\CMakeFiles\leetcodeCPP.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/leetcodeCPP.dir/depend

