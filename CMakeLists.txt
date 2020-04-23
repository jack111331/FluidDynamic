cmake_minimum_required(VERSION 3.6)
project(FluidDynamic)

# - Setup Library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("./library/glfw-3.3.2")

find_package(OpenGL REQUIRED)

set(CMAKE_PREFIX_PATH "./library/glew-2.2.0")
set(CMAKE_LIBRARY_PATH "./library/glew-2.2.0/lib/Release/Win32/")
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

# Setup executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

# Setup compiler cfg
set(CMAKE_CXX_STANDARD 11)

include_directories("./include")

# Setup file to be compiled
set(FLUID_DYNAMIC_SOURCE)
set(FLUID_DYNAMIC_HEADER)

list(APPEND FLUID_DYNAMIC_SOURCE
        main.cpp
        NavierStokes.cpp
        Density.cpp
        Velocity.cpp
        Solver.cpp
        Fluid.cpp
        Shader.cpp
        )
list(APPEND FLUID_DYNAMIC_HEADER
        include/NavierStokes.h
        include/Density.h
        include/Velocity.h
        include/Quantity.h
        include/Solver.h
        include/Utility.h
        include/Shader.h

        include/stb_image.h
        )

set(all_code_files
        ${FLUID_DYNAMIC_HEADER}
        ${FLUID_DYNAMIC_SOURCE}
        )

add_executable(FluidDynamic ${all_code_files})
target_link_libraries(FluidDynamic glfw OpenGL::GL)