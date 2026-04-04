# Tankz

A project to learn C++ and OpenGL. It is a game where you control a tank, and the objective is to destroy all enemies in the scenario.

At the center of the map, there is a wall. On one side, there is the player’s tank; on the other side, there are allies and enemies. Allies are represented by green trees, while enemies are represented by red trees.

The tank can move in all directions and has two additional axes that move independently. It can shoot one projectile at a time. The projectile can collide with allies, enemies, or wall blocks, and it is destroyed upon collision or when it goes beyond the map boundaries.

The game ends when all enemies are destroyed.

Each object you hit grants a different number of points, and the total determines your final score. The score is displayed in the terminal.

<p align="center">
<img src="https://media.giphy.com/media/geCQavOUZHWqJymaAp/giphy.gif">
</p>

## How to Play the Game

Keybindings:
- `W`: Move the tank forward;
- `S`: Move the tank backward;
- `A`: Rotate the tank to the left;
- `D`: Rotate the tank to the right;
- `Space Bar`: Shoot;
- `↑`: Rotate the tank cannon up;
- `↓`: Rotate the tank cannon down;
- `←`: Rotate the tank’s second axis to the left;
- `→`: Rotate the tank’s second axis to the right;
- `I`: Move the camera forward;
- `K`: Move the camera backward;
- `L`: Move the camera up;
- `J`: Move the camera down;
- `1`: Set the camera to the left side, facing the center;
- `2`: Set the camera to the top side, facing the center;
- `3`: Set the camera to the right side, facing the center;
- `4`: Set the camera to the bottom side, facing the center;
- `5`: Set the camera to the left side with a higher Y position;
- `F`: Enable fullscreen;
- `ESC`: Exit the program.

You can also use the mouse to control the camera horizontally.

## How the Score System Works

- Enemy destroyed: +10 points;
- Ally destroyed: -10 points;
- Wall block destroyed: -5 points.

## How to run the game

Check [Releases](https://github.com/iVcente/Tankz/releases) to download precompiled binaries. If you prefer to build from source, make sure Make and CMake are installed before proceeding.

### macOS & Linux

Just run:
```bash
make all
```

### Windows

Download `vcpkg` (if installed anywhere else than `C:/`, setting `VCPKG_ROOT` environment variable is mandatory):
```bash
git clone https://github.com/microsoft/vcpkg C:/vcpkg
```

Set `VCPKG_ROOT` environment variable -- optional if `vcpkg` is in `C:/vcpkg`.

Execute `vcpkg` bootstrap:
```bash
./Path/To/vcpkg/bootstrap-vcpkg.bat
```

Install dependencies:
```bash
./vcpkg install freeglut glew
```

Build project:
```bash
make all
```

---

## Technologies and Libraries Used
- C++
- OpenGL and GLUT
- [stb](https://github.com/nothings/stb)(stb_image.h)

---

## Acknowledgements

- My college professor, Márcio Sarroglia Pinho;
- These two YouTube channels helped a lot: [Sergio Silva](https://www.youtube.com/channel/UCtaYud62YmszOEpGwkWVJPw) and [Tech with Tim](https://www.youtube.com/c/TechWithTim/featured).
