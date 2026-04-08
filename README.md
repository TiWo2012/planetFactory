# 🏭 planetFactory

A factory building game built with C++23 and [raylib](https://www.raylib.com/). Place cores, build conveyor belts, and automate your production lines on an infinite grid.

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)
![raylib](https://img.shields.io/badge/raylib-5.5-green.svg)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-orange.svg)
![AI](https://img.shields.io/badge/AI--Generated-red.svg)

## ✨ Features

- **Grid-based building** — Place objects on a 32-pixel aligned grid
- **Conveyor belts** — Transport items between cores with animated belt systems
- **Proximity detection** — Belts automatically connect to nearby cores
- **Camera system** — Smooth camera following the player with zoom support
- **Modular architecture** — Clean OOP design with extensible object types

## 🎮 Controls

| Key | Action |
|-----|--------|
| `WASD` / Arrow keys | Move player |
| `1` | Place **Core** at mouse position |
| `2` | Place **Belt** at mouse position |
| `Mouse` | Aim / target for placement |
| `Resize window` | Dynamic viewport adjustment |

## 🚀 Getting Started

### Prerequisites

- **CMake** 3.20 or higher
- **C++23** compatible compiler (GCC 13+, Clang 16+, MSVC 2022+)
- **Git** (for fetching raylib)

### Building

```bash
# Clone the repository
git clone <repo-url>
cd planetFactory

# Create build directory
mkdir -p build && cd build

# Generate build files
cmake ..

# Compile
make -j$(nproc)
```

Or use the convenience script:

```bash
./run.sh
```

### Running

```bash
./build/planetFactory
```

## 🏗️ Project Structure

```
planetFactory/
├── include/           # Header files
│   ├── belt.h         # Conveyor belt class
│   ├── constants.h    # Game constants
│   ├── core.h         # Core building class
│   ├── object.h       # Base object interface
│   └── player.h       # Player controller
├── src/               # Source files
│   ├── main.cpp       # Entry point & game loop
│   ├── belt.cpp       # Belt implementation
│   ├── core.cpp       # Core implementation
│   ├── object.cpp     # Base object logic
│   └── player.cpp     # Player movement
├── CMakeLists.txt     # Build configuration
├── run.sh             # Quick build & run script
└── README.md          # This file
```

## 🧩 Architecture

The game follows a component-like OOP pattern:

- **`Object`** — Abstract base class for all placeable entities
- **`Core`** — Central building that can connect to belts
- **`Belt`** — Conveyor system that transports items, snaps to nearby cores
- **`Player`** — 2D character controller with grid-based positioning

Objects are stored in an `unordered_map` indexed by unique IDs, enabling efficient lookup and dynamic creation/destruction.

## 🔧 Configuration

Edit `include/constants.h` to tweak game parameters:

```cpp
#define SCREEN_WIDTH    800    // Window width
#define SCREEN_HEIGHT   600    // Window height
#define PLAYER_SPEED    200    // Player movement speed (px/s)
#define OFFSET          32     // Grid cell size (px)
#define BELT_MOVE_SPEED 100    // Belt animation speed
```

## 📝 License

This project is licensed under the [GPL-3.0](LICENSE).

> **Note**: This README file was AI-generated.

---

*Built with raylib and modern C++23 features.*
