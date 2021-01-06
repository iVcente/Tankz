#ifndef PHYSICS_H
#define PHYSICS_H

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

#include "Vector.h"

/* 
 ? This header file contains e provides all the functions related 
 ? to the game's physics. It also defines a struct for the bounding boxes,
 ? the scenario dimensions and a struct called `MotionXY` to help determine
 ? the projectile motion. 
 */

struct BoundingBox {
    Vec3 center;
    Vec3 halfSize;

    BoundingBox() {
        center = Vec3(0.0f, 0.0f, 0.0f);
        halfSize = Vec3(0.0f, 0.0f, 0.0f);
    }

    BoundingBox(Vec3 center, Vec3 halfSize) {
        this->center = center;
        this->halfSize = halfSize;
    }
};

// Scenario dimensions
const int MIN_WIDTH = 1;
const int MAX_WIDTH = 50;
const int MIN_DEPTH = 1;
const int MAX_DEPTH = 25;
const int MIN_HEIGHT = 0;
const int MAX_HEIGHT = 4;
const int DIV_WALL_HEIGHT = 8;
const int WALL_HEIGHT = 4;

/* 
 * Checks whether the new position of the tank's movement is valid or not.
 * 
 * Parameters: `boundingBox` and `newPosition`.
 * Returns `true` or `false`.
 */
inline bool insideBoundariesTank(BoundingBox boundingBox, Vec3 newBasePosition) {
    float top = newBasePosition.z - boundingBox.halfSize.x;
    float bottom = newBasePosition.z + boundingBox.halfSize.x;
    float left = newBasePosition.x - boundingBox.halfSize.x;
    float right = newBasePosition.x + boundingBox.halfSize.x;

    if ((top >= -MAX_DEPTH) && (bottom <= -MIN_DEPTH) && (left >= MIN_WIDTH) && (right <= (MAX_WIDTH/2 - 0.5f)))
        return true;

    return false;

    /*
    if ((top <= -MAX_DEPTH) || (bottom >= -MIN_DEPTH) || (left <= MIN_WIDTH) || (right >= (MAX_WIDTH/2 - 0.5f)))
        return false;

    return true;
    */
}

/* 
 * Checks whether the new position of the projectile's movement is valid or not.
 * 
 * Parameters: `boundingBox` and `newPosition`.
 * Returns `true` or `false`.
 */
inline bool insideBoundariesProjectile(BoundingBox boundingBox, Vec3 newPosition) {
    float top = newPosition.z - boundingBox.halfSize.z;
    float bottom = newPosition.z + boundingBox.halfSize.z;
    float left = newPosition.x - boundingBox.halfSize.x;
    float right = newPosition.x + boundingBox.halfSize.x;
    float floor = newPosition.y - boundingBox.halfSize.y;
    float ceiling = newPosition.y + boundingBox.halfSize.y;

    if ((top >= -MAX_DEPTH) && (bottom <= -MIN_DEPTH) && (left >= MIN_WIDTH) && (right <= (MAX_WIDTH - 0.5f)) && (floor >= MIN_HEIGHT))
        return true;

    return false;

    /*
    if ((top <= -MAX_DEPTH) || (bottom >= -MIN_DEPTH) || (left <= MIN_WIDTH) || (right >= (MAX_WIDTH/2 - 0.5f)))
        return false;

    return true;
    */
}

/* 
 * Checks whether there's a collision between two objects' bounding boxes.
 * 
 * Parameters: `b1` and `b2`.
 * Returns `true` or `false`.
 */
inline bool checkCollision(BoundingBox b1, BoundingBox b2) {
    if (abs(b1.center.x - b2.center.x) > (b1.halfSize.x + b2.halfSize.x))
        return false;
    if (abs(b1.center.y - b2.center.y) > (b1.halfSize.y + b2.halfSize.y))
        return false;
    if (abs(b1.center.z - b2.center.z) > (b1.halfSize.z + b2.halfSize.z))
        return false;
    return true;
}

/* 
 * Converts degrees to radians.
 * 
 * Parameters: `angleInDegrees`.
 * Returns angle in radians in a `float`.
 */
inline float degreesToRadian(float angleInDegrees) {
    return (angleInDegrees * M_PI) / 180.0;
}

struct MotionXY {
    float newX;
    float newY;

    MotionXY(float newX, float newY) {
        this->newX = newX;
        this->newY= newY;
    }
};

/* 
 * Calculates the projectile motion using the basic formula in physics.
 * 
 * Parameters: `currentX`, `currentY`, `angleTheta` and `time`.
 * Returns the new position in the type `MotionXY`.
 */
inline MotionXY projectileMotion(float currentX, float currentY, float angleTheta, float time) {
    //float gHalf = -14.7; // Gravity and a half just for the animation purposes
    float g = -9.8f; // Gravity
    //float halfG = -4.9f; // Half of the gravity just for the animation purposes
    float power = 2.1f;

    float xVelocity = cosf(degreesToRadian(angleTheta)) * power;
    float yVelocity = sinf(degreesToRadian(angleTheta)) * power;

    float distanceX = xVelocity * time;
    float distanceY = (yVelocity * time) + ((g * (time * time)) / 2);

    float newX = distanceX + currentX;
    float newY = distanceY + currentY;
    //float newY = currentY - distanceY;
    
    MotionXY newPosition = MotionXY(newX, newY);

    return newPosition;
}

#endif // PHYSICS_H