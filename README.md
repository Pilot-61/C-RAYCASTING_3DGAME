# cub3D

A raycasting-based 3D maze game inspired by the classic Wolfenstein 3D, created as part of the 42 school curriculum. This project implements a first-person perspective renderer inside a maze using raycasting techniques.

![cub3D Preview](https://via.placeholder.com/800x400?text=cub3D+Preview)

## Table of Contents
- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
  - [Linux](#linux)
  - [macOS](#macos)
- [Usage](#usage)
- [Map Format](#map-format)
- [Controls](#controls)
- [Bonus Features](#bonus-features)
- [Troubleshooting](#troubleshooting)

## About

cub3D is a first-person 3D maze renderer using raycasting techniques. Inspired by Wolfenstein 3D, this project demonstrates fundamental computer graphics principles in a playable 3D environment.

## Features

- Textured walls with different textures based on orientation (North, South, East, West)
- Custom ceiling and floor colors
- Smooth window management
- Map parsing from a configuration file
- First-person navigation in a 3D environment
- Raycasting-based rendering

## Requirements

- GCC Compiler
- Make
- GLFW library
- MLX42 library
- CMake (for MLX compilation)

## Installation

### Linux

1. **Install dependencies**:
   ```bash
   sudo apt update
   sudo apt install gcc make cmake xorg libxext-dev libbsd-dev libglfw3 libglfw3-dev
   ```

2. **Clone the repository**:
   ```bash
   git clone https://github.com/Pilot-61/C-RAYCASTING_3DGAME.git cub3D
   cd cub3D
   ```

3. **Download and set up MLX42**:
   ```bash
   git clone https://github.com/codam-coding-college/MLX42.git MLX
   ```

4. **Compile and run the project**:
   ```bash
   make
   ```

### macOS

1. **Install Homebrew** (if not already installed):
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install dependencies**:
   ```bash
   brew update
   brew install cmake glfw
   ```

3. **Clone the repository**:
   ```bash
   git clone https://github.com/Pilot-61/C-RAYCASTING_3DGAME.git cub3D
   cd cub3D
   ```

4. **Download and set up MLX42**:
   ```bash
   git clone https://github.com/codam-coding-college/MLX42.git MLX
   ```

5. **Compile and run the project**:
   ```bash
   make
   ```

## Usage

Run the program with a map file:

```bash
./cub3D mandatory/maps/example.cub
```

Or run the bonus version:

```bash
make bonus
./cub_bonus bonus/bonus_maps/example.cub
```

## Map Format

The map must be provided in a `.cub` file format with the following specifications:

```
NO ./path_to_the_north_texture.xpm
SO ./path_to_the_south_texture.xpm
WE ./path_to_the_west_texture.xpm
EA ./path_to_the_east_texture.xpm
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Where:
- `NO`, `SO`, `WE`, `EA`: Paths to wall textures for different orientations
- `F`: RGB color for the floor (format: R,G,B)
- `C`: RGB color for the ceiling (format: R,G,B)
- Map characters:
  - `0`: Empty space
  - `1`: Wall
  - `N`, `S`, `E`, `W`: Player's starting position and orientation

## Controls

- `W`: Move forward
- `S`: Move backward
- `A`: Move left
- `D`: Move right
- `←`, `→`: Rotate camera left/right
- `ESC`: Exit the game

## Bonus Features

The bonus version includes:
- Wall collisions
- Minimap system
- Doors that can open and close
- Animated sprites
- Mouse rotation for point of view

To compile and run the bonus version:
```bash
make bonus
./cub_bonus bonus/bonus_maps/example.cub
```

## Troubleshooting

### Common Issues

1. **MLX Compilation Errors**:
   - Ensure all dependencies are installed
   - Try recompiling MLX separately:
     ```bash
     cd MLX
     cmake -B build
     cmake --build build -j4
     ```

2. **Graphics/Display Issues**:
   - Linux: Make sure X11 and OpenGL are properly installed
   - macOS: Ensure you have the latest version of GLFW

3. **Map Parsing Errors**:
   - Check your map file for syntax errors
   - Ensure the map is enclosed by walls
   - Verify texture paths are correct
