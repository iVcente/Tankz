#ifndef PLAYER_H
#define PLAYER_H

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "BasePolygons.h"
#include "Physics.h"
#include "Projectile.h"
#include "Vector.h"

/* 
 ? This header file defines the Player. The player controls a tank and its
 ? through the tank that the player interacts with the game. It also defines
 ? three structs responsible for allowing different actions to the player:
 ? TankBase, TankAxis and TankCannon.
 */

struct TankBase {
    Vec3 direction = Vec3(1, 0, 0); // Move forward, backward and rotates on left and right
    Vec3 position = Vec3(10.0f, 0.0f, -12.5f); // Inital position
    Vec3 dimensions = Vec3(5.0f, 1.0f, 3.0f); // Width, Height, Depth
};

struct TankAxis {
    Vec3 direction = Vec3(1, 0, 0); // Rotates left and right
    Vec3 position = Vec3(10.0f, 1.0f, -12.5f);
    //Vec3 position = Vec3(8.5f, 1.0f, -12.5f);
    Vec3 dimensions = Vec3(2.0f, 1.0f, 2.0f);
};

struct TankCannon {
    Vec3 direction = Vec3(1, 0, 0);
    Vec3 position = Vec3(10.0f, 1.75f, -12.5f);
    //Vec3 position = Vec3(9.5f, 1.75f, -12.5f);
    Vec3 dimensions = Vec3(4.0f, 0.5f, 1.0f);
};

class Player {
    private:
        float speed = 0.5f;
        float currentBaseRotation = 0.0f;
        float currentAxisRotation = 0.0f;
        float currentCannonRotation = 0.0f;
        float rotationAngleBase = 10.0f; // Degrees
        float rotationAngleAxis = 5.0f; // Degrees
        float rotationAngleCannon = 1.0f; // Degrees
        TankBase base;
        TankAxis axis;
        TankCannon cannon;
        BoundingBox boundingBox;
        void drawBase(GLuint textureID);
        void drawAxis(GLuint textureID);
        void drawCannon(GLuint textureID);
        
    public:
        Player();
        void drawTank(GLuint texturesIDs[]);
        void drawBoundingBox();
        void moveForward();
        void moveBackward();
        void rotateLeft();
        void rotateRight();
        void rotateAxisLeft();
        void rotateAxisRight();
        void rotateCannonUp();
        void rotateCannonDown();
        void shoot(Projectile& projectile);
};

#endif // PLAYER_H