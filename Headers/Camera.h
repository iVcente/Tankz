#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

/* 
 ? This header file defines a Camera. The player can move the camera in a great
 ? variety of ways.
 */

class Camera {
	private:
		Vec3 position;
		Vec3 direction;
		Vec3 left;
		Vec3 up;
		Vec3 speed;
		float scale = 0.75f;
		float yaw;

	public:
		Camera(Vec3 pos);
		void activate();
		void moveForward();
		void moveBackward();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void updateYaw(float dYaw);
		void update();
		void setCameraPosition(Vec3 newPosition, Vec3 newDirection);
};

#endif // CAMERA_H