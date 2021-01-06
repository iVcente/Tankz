#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Colors.h"
#include "Model.h"
#include "Physics.h"
#include "Vector.h"

/* 
 ? This header file defines a GameObject. A GameObject can be an ally or an enemy.
 ? The GameObject is a 3D object read from a .obj file.
 */

class GameObject {
    private:
        Model model;
        Vec3 position;
        BoundingBox boundingBox;
        Color color;
        bool enemy;
        bool destroyed = false;

    public:
        GameObject(bool enemy, Model model, Vec3 initialPosition, Color color);
        void drawGameObject();
        void drawBoundingBox();
        bool isDestroyed();
        void destroy();
        BoundingBox getBoundingBox();
        bool isEnemy();
};

#endif