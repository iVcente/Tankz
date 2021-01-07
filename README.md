# Tankz
This is a simple 3D game where you control a tank and the objective is to destroy all enemies in the scenario. Right in the middle of the scenario there's a wall, on one side there's the tank and on the other side of the wall there are allies and enemies. The allies are represented by green trees and the enemies are represented by red trees. The tank can move in all directions and has two other axes that move independently. The tank can shoot one projectile at a time; it can collide with an ally, an enemy and a wall block. The projectile will be destroyed if it collides with any of these objects or in case it moves away from the scenario limits. The game ends when all the enemies are destroyed. Every object you hit you gain different points number, the sum of these points will be your final score. The final score and the points will be printed in the terminal.

<p align="center">
<img src="https://media.giphy.com/media/Emat6yP6sZR50TK0MB/giphy.gif">
</p>

<p align="center">
<img src="https://media.giphy.com/media/geCQavOUZHWqJymaAp/giphy.gif">
</p>

How to play the game
---

You can use the following commands:
* `W` : Moves the tank forward
* `S` : Moves the tank backward
* `A` : Rotates the tank to the left
* `D` : Rotates the tank to the right
* `Space Bar` : Shoots
* `↑` : Rotates the tank cannon up
* `↓` : Rotates the tank cannon down
* `←` : Rotates the tank second axis to the left
* `→` : Rotates the tank second axis to the right
* `I` : Moves the camera forward
* `K` : Moves the camera backward
* `L` : Moves the camera up
* `J` : Moves the camera down
* `1` : Sets the camera position looking to the center of the scenario while being at the left side
* `2` : Sets the camera position looking to the center of the scenario while being at the top side
* `3` : Sets the camera position looking to the center of the scenario while being at the right side
* `4` : Set the camera position looking to the center of the scenario while being at the bottom side
* `5` : Set the camera position looking to the center of the scenario while being at the left side and with a higher Y
* `F` : Full screen
* `ESC` : Exits the program

Finally, you can use the mouse to control the camera in the horizontal axis.

How the score system works
---

* Enemy destroyed: +10 points
* Ally destroyed: -10 points
* Wall block destroyed: -5 points

How to run the game
---

>On Windows 🖥:

```
g++-10 -lopengl32 -lglew32 -lfreeglut -lglu32 Tankz.cpp Camera.cpp GameObject.cpp Player.cpp Projectile.cpp stb_image.cpp -o Tankz
```

>On MacOS 🍎:

```
g++-10 -Wno-deprecated -framework OpenGL -framework GLUT Tankz.cpp Camera.cpp GameObject.cpp Player.cpp Projectile.cpp stb_image.cpp -o Tankz
```

>On Linux 🐧:

```
g++-10 -lglut -lGLU -lGL Tankz.cpp Camera.cpp GameObject.cpp Player.cpp Projectile.cpp stb_image.cpp -o Tankz
```

If you happen to have any issue trying to compile the program, here's a Gist to help you: link.

Technologies and libraries used
---
* C++
* OpenGL and GLUT
* [stb](https://github.com/nothings/stb) (stb_image.h)

I got help from:
---

* My college professor: Márcio Sarroglia Pinho
* These two channels on YouTube helped a lot: [Sergio Silva](https://www.youtube.com/channel/UCtaYud62YmszOEpGwkWVJPw) and [Tech with Tim](https://www.youtube.com/c/TechWithTim/featured)
