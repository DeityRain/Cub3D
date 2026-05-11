This project has been created as part of the 42 curriculum by qdeffaux.

# cub3D - A 42 Graphics Project

This project is a 3D game engine built from scratch using the **Raycasting** technique, inspired by the world-famous 90's game *Wolfenstein 3D*. It explores the concepts of basic computer graphics, coordinate geometry, and the MiniLibX library.

## Description

The goal of `cub3D` is to create a dynamic 3D perspective inside a maze using a 2D map. By utilizing the **DDA (Digital Differential Analyzer)** algorithm, the engine calculates the distance between the player and the walls in real-time, rendering a three-dimensional view with wall textures, floor/ceiling colors, and smooth movement logic.

### Key Features:
- **Fast 3D Rendering**: Optimized raycasting using the DDA algorithm.
- **Dynamic Textures**: Different textures for North, South, East, and West walls.
- **Robust Parsing**: Advanced `.cub` file validation (colors, paths, map enclosure).
- **Smooth Controls**: Multi-key management for simultaneous rotation and movement.
- **Zero-Leak Policy**: 100% leak-free implementation, verified and audited with Valgrind.

## Instructions

### Compilation
The project uses a `Makefile` to compile both the `libft` and the `mlx` library along with the main source files.

```bash
# Clone the repository
git clone https://github.com/your-username/Cub3D.git
cd Cub3D

# Compile the project
make
```

### Execution
To run the game, provide a valid `.cub` map file as an argument:

```bash
./cub3D maps/miniMap.cub
```

### Controls
| Key | Action |
| :--- | :--- |
| **W, A, S, D** | Move Forward, Left, Backward, Right |
| **Left/Right Arrows** | Rotate Camera |
| **ESC** | Safely Close Game (Cleanup and Exit) |
| **Window [X]** | Close Game |

## Map Format
The engine requires a `.cub` file containing:
- **Texture Paths**: `NO`, `SO`, `WE`, `EA` followed by paths to `.xpm` textures.
- **Colors**: `F` (Floor) and `C` (Ceiling) followed by RGB values (e.g., `220,100,0`).
- **The Map**: Composed of `1` (Wall), `0` (Empty), and `N/S/E/W` (Player Start Position).

## Technical Implementation & Memory Safety

One of the highlights of this implementation is the **perfect memory score**. Even in cases of invalid maps or interrupted execution, the program ensures all heap-allocated memory is reclaimed.

To run the memory audit yourself (using the provided suppression file to filter MLX internal noise):
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=mlx.supp ./cub3D maps/miniMap.cub
```
**Result:** `Definitely lost: 0 bytes in 0 blocks` | `ERROR SUMMARY: 0 errors from 0 contexts`.

## Resources

### Documentation & Tutorials
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html): The primary resource for understanding DDA logic.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx): Reference for the 42 graphics library.

### Use of AI
AI (Gemini) was used during this project for:
- **Static Analysis**: Identifying edge-case memory leaks in the map parsing logic (specifically partial grid allocation failures).
- **Valgrind Optimization**: Creating custom suppression files to filter out MiniLibX/X11 library-level noise.
- **Documentation**: Structuring the technical explanations and formatting for this README.

---
*This project was completed according to the 42 School Norm and requirements.*
