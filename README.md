# Rainbow Triangle OpenGL

A simple OpenGL program that renders a colorful triangle with rainbow vertex colors.

## Description

This project demonstrates basic OpenGL concepts including:
- Vertex buffer objects (VBOs)
- Vertex array objects (VAOs)
- Basic vertex and fragment shaders
- Per-vertex color interpolation

The triangle displays with red, green, and blue vertices that smoothly blend across the surface.

## Prerequisites

- OpenGL 3.3 or higher
- GLFW (for window management)
- GLAD (for OpenGL function loading)
- A C++ compiler with C++11 support

## Building

This project uses CMake for cross-platform building.

```bash
mkdir build
cd build
cmake ..
make
./rainbow_triangle
```

### Windows
```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
.\Release\rainbow_triangle.exe
```

## Usage

Run the executable to display the rainbow triangle. Press ESC or close the window to exit.

## What I Learned

- Setting up a basic OpenGL rendering pipeline
- Writing simple vertex and fragment shaders
- Understanding how vertex attributes work
- Color interpolation across triangle surfaces


## License

This project is open source and available under the [Apache License](LICENSE).
