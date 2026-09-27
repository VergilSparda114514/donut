# Donut

A spinning ASCII donut that runs on the terminal, implemented in C++
![Donut](screenshots/donut.png)

## Requirements

* [CMake 3.20+](https://cmake.org/)

# Getting Started

### Command line arguments

* `-w=` to the width of the viewport
* `-h=` to the height of the viewport
* `-fps=` to the target FPS of the application
* `-shd=` (y/n) to enable/disable complex shading

## Building

1. Clone the repository using `git clone --recursive https://github.com/VergilSparda114514/donut.git`
2. Run `cmake` to generate Makefiles
3. Run `make` to build the project

### 3rd party libraries

* [FTXUI](https://github.com/ArthurSonzogni/FTXUI)
* [glm](https://github.com/g-truc/glm)

