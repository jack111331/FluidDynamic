# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Code\FluidDynamic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Code\FluidDynamic\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FluidDynamic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FluidDynamic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FluidDynamic.dir/flags.make

CMakeFiles/FluidDynamic.dir/main.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/main.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FluidDynamic.dir/main.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\main.cpp.obj -c D:\Code\FluidDynamic\main.cpp

CMakeFiles/FluidDynamic.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/main.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\main.cpp > CMakeFiles\FluidDynamic.dir\main.cpp.i

CMakeFiles/FluidDynamic.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/main.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\main.cpp -o CMakeFiles\FluidDynamic.dir\main.cpp.s

CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.obj: ../NavierStokes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\NavierStokes.cpp.obj -c D:\Code\FluidDynamic\NavierStokes.cpp

CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\NavierStokes.cpp > CMakeFiles\FluidDynamic.dir\NavierStokes.cpp.i

CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\NavierStokes.cpp -o CMakeFiles\FluidDynamic.dir\NavierStokes.cpp.s

CMakeFiles/FluidDynamic.dir/Density.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Density.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Density.cpp.obj: ../Density.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/FluidDynamic.dir/Density.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Density.cpp.obj -c D:\Code\FluidDynamic\Density.cpp

CMakeFiles/FluidDynamic.dir/Density.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Density.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Density.cpp > CMakeFiles\FluidDynamic.dir\Density.cpp.i

CMakeFiles/FluidDynamic.dir/Density.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Density.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Density.cpp -o CMakeFiles\FluidDynamic.dir\Density.cpp.s

CMakeFiles/FluidDynamic.dir/Velocity.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Velocity.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Velocity.cpp.obj: ../Velocity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/FluidDynamic.dir/Velocity.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Velocity.cpp.obj -c D:\Code\FluidDynamic\Velocity.cpp

CMakeFiles/FluidDynamic.dir/Velocity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Velocity.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Velocity.cpp > CMakeFiles\FluidDynamic.dir\Velocity.cpp.i

CMakeFiles/FluidDynamic.dir/Velocity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Velocity.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Velocity.cpp -o CMakeFiles\FluidDynamic.dir\Velocity.cpp.s

CMakeFiles/FluidDynamic.dir/Solver.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Solver.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Solver.cpp.obj: ../Solver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/FluidDynamic.dir/Solver.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Solver.cpp.obj -c D:\Code\FluidDynamic\Solver.cpp

CMakeFiles/FluidDynamic.dir/Solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Solver.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Solver.cpp > CMakeFiles\FluidDynamic.dir\Solver.cpp.i

CMakeFiles/FluidDynamic.dir/Solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Solver.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Solver.cpp -o CMakeFiles\FluidDynamic.dir\Solver.cpp.s

CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.obj: ../Fluid2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Fluid2D.cpp.obj -c D:\Code\FluidDynamic\Fluid2D.cpp

CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Fluid2D.cpp > CMakeFiles\FluidDynamic.dir\Fluid2D.cpp.i

CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Fluid2D.cpp -o CMakeFiles\FluidDynamic.dir\Fluid2D.cpp.s

CMakeFiles/FluidDynamic.dir/Control.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Control.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Control.cpp.obj: ../Control.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/FluidDynamic.dir/Control.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Control.cpp.obj -c D:\Code\FluidDynamic\Control.cpp

CMakeFiles/FluidDynamic.dir/Control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Control.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Control.cpp > CMakeFiles\FluidDynamic.dir\Control.cpp.i

CMakeFiles/FluidDynamic.dir/Control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Control.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Control.cpp -o CMakeFiles\FluidDynamic.dir\Control.cpp.s

CMakeFiles/FluidDynamic.dir/Shader.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Shader.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Shader.cpp.obj: ../Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/FluidDynamic.dir/Shader.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Shader.cpp.obj -c D:\Code\FluidDynamic\Shader.cpp

CMakeFiles/FluidDynamic.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Shader.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Shader.cpp > CMakeFiles\FluidDynamic.dir\Shader.cpp.i

CMakeFiles/FluidDynamic.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Shader.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Shader.cpp -o CMakeFiles\FluidDynamic.dir\Shader.cpp.s

CMakeFiles/FluidDynamic.dir/Keyframe.cpp.obj: CMakeFiles/FluidDynamic.dir/flags.make
CMakeFiles/FluidDynamic.dir/Keyframe.cpp.obj: CMakeFiles/FluidDynamic.dir/includes_CXX.rsp
CMakeFiles/FluidDynamic.dir/Keyframe.cpp.obj: ../Keyframe.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/FluidDynamic.dir/Keyframe.cpp.obj"
	D:\MinGW\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FluidDynamic.dir\Keyframe.cpp.obj -c D:\Code\FluidDynamic\Keyframe.cpp

CMakeFiles/FluidDynamic.dir/Keyframe.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FluidDynamic.dir/Keyframe.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\FluidDynamic\Keyframe.cpp > CMakeFiles\FluidDynamic.dir\Keyframe.cpp.i

CMakeFiles/FluidDynamic.dir/Keyframe.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FluidDynamic.dir/Keyframe.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\FluidDynamic\Keyframe.cpp -o CMakeFiles\FluidDynamic.dir\Keyframe.cpp.s

# Object files for target FluidDynamic
FluidDynamic_OBJECTS = \
"CMakeFiles/FluidDynamic.dir/main.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Density.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Velocity.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Solver.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Control.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Shader.cpp.obj" \
"CMakeFiles/FluidDynamic.dir/Keyframe.cpp.obj"

# External object files for target FluidDynamic
FluidDynamic_EXTERNAL_OBJECTS =

../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/main.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/NavierStokes.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Density.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Velocity.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Solver.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Fluid2D.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Control.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Shader.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/Keyframe.cpp.obj
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/build.make
../bin/FluidDynamic.exe: ../library/glew-2.2.0/lib/Release/Win32/glew32.lib
../bin/FluidDynamic.exe: ../library/glew-2.2.0/lib/Release/Win32/glew32.lib
../bin/FluidDynamic.exe: library/glfw-3.3.2/src/libglfw3.a
../bin/FluidDynamic.exe: ../library/glew-2.2.0/lib/Release/Win32/glew32.lib
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/linklibs.rsp
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/objects1.rsp
../bin/FluidDynamic.exe: CMakeFiles/FluidDynamic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ..\bin\FluidDynamic.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\FluidDynamic.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FluidDynamic.dir/build: ../bin/FluidDynamic.exe

.PHONY : CMakeFiles/FluidDynamic.dir/build

CMakeFiles/FluidDynamic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\FluidDynamic.dir\cmake_clean.cmake
.PHONY : CMakeFiles/FluidDynamic.dir/clean

CMakeFiles/FluidDynamic.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Code\FluidDynamic D:\Code\FluidDynamic D:\Code\FluidDynamic\cmake-build-debug D:\Code\FluidDynamic\cmake-build-debug D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles\FluidDynamic.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FluidDynamic.dir/depend

