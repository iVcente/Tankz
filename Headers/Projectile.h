#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector.h"

/* 
 ? This header file defines a Projectile. The player shoots a projectile with
 ? the space bar and can shoot only one projectile at at time.
 ? The projectile motion is defined as a parabola. A projectile will be destroyed
 ? if it hits a wall block, an ally or an enemy. Moving outside the scenario boundaries
 ? will also cause its destruction.
 */

class Projectile {
    private:
        float speed = 0.20f;
        float time = 0.0f;
        bool launched = false;
        float launchAngle;
        Vec3 position;
        Vec3 direction;
        Vec3 dimensions = Vec3(0.5f, 0.5f, 0.5f);
        BoundingBox box;
        void updatePosition();
    public:
        Projectile();
        void setPosition(Vec3 pos);
        void setDirection(Vec3 dir);
        void setLaunchAngle(float angle);
        void drawProjectile();
        void drawBoundingBox();
        void launch();
        void gotDestroyed();
        bool isLaunched();
        BoundingBox getBoundingBox();
};

#endif