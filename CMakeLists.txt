cmake_minimum_required(VERSION 3.20)
project(RainbowTriangle)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Generate GLAD files if they don't exist
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/include/glad/glad.h")
    message(STATUS "Generating GLAD files...")
    execute_process(
        COMMAND glad --api=gl:core=4.6 --out-path=${CMAKE_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE GLAD_RESULT
    )
    if(NOT GLAD_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to generate GLAD files. Make sure 'glad' command is available.")
    endif()
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${GLFW3_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/gl.c
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    ${OPENGL_LIBRARIES}
    ${GLFW3_LIBRARIES}
    ${CMAKE_DL_LIBS}  # for dlopen/dlsym
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${GLFW3_CFLAGS_OTHER})

# Optional: Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
