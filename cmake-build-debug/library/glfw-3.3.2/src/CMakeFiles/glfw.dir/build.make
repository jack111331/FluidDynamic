# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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
include library/glfw-3.3.2/src/CMakeFiles/glfw.dir/depend.make

# Include the progress variables for this target.
include library/glfw-3.3.2/src/CMakeFiles/glfw.dir/progress.make

# Include the compile flags for this target's objects.
include library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.obj: ../library/glfw-3.3.2/src/context.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\context.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\context.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/context.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\context.c > CMakeFiles\glfw.dir\context.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/context.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\context.c -o CMakeFiles\glfw.dir\context.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.obj: ../library/glfw-3.3.2/src/init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\init.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\init.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/init.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\init.c > CMakeFiles\glfw.dir\init.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/init.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\init.c -o CMakeFiles\glfw.dir\init.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.obj: ../library/glfw-3.3.2/src/input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\input.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\input.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/input.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\input.c > CMakeFiles\glfw.dir\input.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/input.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\input.c -o CMakeFiles\glfw.dir\input.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.obj: ../library/glfw-3.3.2/src/monitor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\monitor.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\monitor.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/monitor.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\monitor.c > CMakeFiles\glfw.dir\monitor.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/monitor.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\monitor.c -o CMakeFiles\glfw.dir\monitor.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.obj: ../library/glfw-3.3.2/src/vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\vulkan.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\vulkan.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/vulkan.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\vulkan.c > CMakeFiles\glfw.dir\vulkan.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/vulkan.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\vulkan.c -o CMakeFiles\glfw.dir\vulkan.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.obj: ../library/glfw-3.3.2/src/window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\window.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\window.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/window.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\window.c > CMakeFiles\glfw.dir\window.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/window.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\window.c -o CMakeFiles\glfw.dir\window.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.obj: ../library/glfw-3.3.2/src/win32_init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\win32_init.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_init.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/win32_init.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_init.c > CMakeFiles\glfw.dir\win32_init.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/win32_init.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_init.c -o CMakeFiles\glfw.dir\win32_init.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.obj: ../library/glfw-3.3.2/src/win32_joystick.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\win32_joystick.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_joystick.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/win32_joystick.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_joystick.c > CMakeFiles\glfw.dir\win32_joystick.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/win32_joystick.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_joystick.c -o CMakeFiles\glfw.dir\win32_joystick.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.obj: ../library/glfw-3.3.2/src/win32_monitor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\win32_monitor.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_monitor.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/win32_monitor.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_monitor.c > CMakeFiles\glfw.dir\win32_monitor.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/win32_monitor.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_monitor.c -o CMakeFiles\glfw.dir\win32_monitor.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.obj: ../library/glfw-3.3.2/src/win32_time.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\win32_time.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_time.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/win32_time.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_time.c > CMakeFiles\glfw.dir\win32_time.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/win32_time.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_time.c -o CMakeFiles\glfw.dir\win32_time.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.obj: ../library/glfw-3.3.2/src/win32_thread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\win32_thread.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_thread.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/win32_thread.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_thread.c > CMakeFiles\glfw.dir\win32_thread.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/win32_thread.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_thread.c -o CMakeFiles\glfw.dir\win32_thread.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.obj: ../library/glfw-3.3.2/src/win32_window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\win32_window.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_window.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/win32_window.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_window.c > CMakeFiles\glfw.dir\win32_window.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/win32_window.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\win32_window.c -o CMakeFiles\glfw.dir\win32_window.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.obj: ../library/glfw-3.3.2/src/wgl_context.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\wgl_context.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\wgl_context.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/wgl_context.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\wgl_context.c > CMakeFiles\glfw.dir\wgl_context.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/wgl_context.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\wgl_context.c -o CMakeFiles\glfw.dir\wgl_context.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.obj: ../library/glfw-3.3.2/src/egl_context.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\egl_context.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\egl_context.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/egl_context.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\egl_context.c > CMakeFiles\glfw.dir\egl_context.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/egl_context.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\egl_context.c -o CMakeFiles\glfw.dir\egl_context.c.s

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/flags.make
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.obj: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/includes_C.rsp
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.obj: ../library/glfw-3.3.2/src/osmesa_context.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.obj"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -o CMakeFiles\glfw.dir\osmesa_context.c.obj   -c D:\Code\FluidDynamic\library\glfw-3.3.2\src\osmesa_context.c

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/osmesa_context.c.i"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -E D:\Code\FluidDynamic\library\glfw-3.3.2\src\osmesa_context.c > CMakeFiles\glfw.dir\osmesa_context.c.i

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/osmesa_context.c.s"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -Wdeclaration-after-statement -S D:\Code\FluidDynamic\library\glfw-3.3.2\src\osmesa_context.c -o CMakeFiles\glfw.dir\osmesa_context.c.s

# Object files for target glfw
glfw_OBJECTS = \
"CMakeFiles/glfw.dir/context.c.obj" \
"CMakeFiles/glfw.dir/init.c.obj" \
"CMakeFiles/glfw.dir/input.c.obj" \
"CMakeFiles/glfw.dir/monitor.c.obj" \
"CMakeFiles/glfw.dir/vulkan.c.obj" \
"CMakeFiles/glfw.dir/window.c.obj" \
"CMakeFiles/glfw.dir/win32_init.c.obj" \
"CMakeFiles/glfw.dir/win32_joystick.c.obj" \
"CMakeFiles/glfw.dir/win32_monitor.c.obj" \
"CMakeFiles/glfw.dir/win32_time.c.obj" \
"CMakeFiles/glfw.dir/win32_thread.c.obj" \
"CMakeFiles/glfw.dir/win32_window.c.obj" \
"CMakeFiles/glfw.dir/wgl_context.c.obj" \
"CMakeFiles/glfw.dir/egl_context.c.obj" \
"CMakeFiles/glfw.dir/osmesa_context.c.obj"

# External object files for target glfw
glfw_EXTERNAL_OBJECTS =

library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/context.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/init.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/input.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/monitor.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/vulkan.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/window.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_init.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_joystick.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_monitor.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_time.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_thread.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/win32_window.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/wgl_context.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/egl_context.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/osmesa_context.c.obj
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/build.make
library/glfw-3.3.2/src/glfw3.dll: ../library/glew-2.2.0/lib/Release/Win32/glew32.lib
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/linklibs.rsp
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/objects1.rsp
library/glfw-3.3.2/src/glfw3.dll: library/glfw-3.3.2/src/CMakeFiles/glfw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Code\FluidDynamic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C shared library glfw3.dll"
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glfw.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
library/glfw-3.3.2/src/CMakeFiles/glfw.dir/build: library/glfw-3.3.2/src/glfw3.dll

.PHONY : library/glfw-3.3.2/src/CMakeFiles/glfw.dir/build

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/clean:
	cd /d D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src && $(CMAKE_COMMAND) -P CMakeFiles\glfw.dir\cmake_clean.cmake
.PHONY : library/glfw-3.3.2/src/CMakeFiles/glfw.dir/clean

library/glfw-3.3.2/src/CMakeFiles/glfw.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Code\FluidDynamic D:\Code\FluidDynamic\library\glfw-3.3.2\src D:\Code\FluidDynamic\cmake-build-debug D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src D:\Code\FluidDynamic\cmake-build-debug\library\glfw-3.3.2\src\CMakeFiles\glfw.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : library/glfw-3.3.2/src/CMakeFiles/glfw.dir/depend

