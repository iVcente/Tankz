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

#include "Headers/Camera.h"
#include "Headers/Physics.h"

/* 
 * Constructor for Camera.
 * 
 * Parameters:`initialPosition`.
 * Returns an instance of `Camera`.
 */
Camera::Camera(Vec3 initialPosition) {
	position = Vec3(initialPosition);
	direction = Vec3(0, 0, -1);
	left = Vec3(-1, 0, 0);
	up = Vec3(0, 1, 0);
	speed = Vec3(0, 0, 0);
}

/* 
 * Activates the camera, setting the `gluLookAt` function to where the camera should be looking at.
 * 
 * No parameters.
 * No return.
 */
void Camera::activate() {
	Vec3 look = position + direction;
	gluLookAt(position.x, position.y, position.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

/* 
 * Moves the camera forward.
 * 
 * No parameters.
 * No return.
 */
void Camera::moveForward() {
	speed = direction * scale;
	position = position + speed;
}

/* 
 * Moves the camera backward.
 * 
 * No parameters.
 * No return.
 */
void Camera::moveBackward() {
	speed = direction * (-scale);
	position = position + speed;
}

/* 
 * Moves the camera left.
 * 
 * No parameters.
 * No return.
 */
void Camera::moveLeft() {
	speed = left * scale;
	position = position + speed;
}


/* 
 * Moves the camera right.
 * 
 * No parameters.
 * No return.
 */
void Camera::moveRight() {
	speed = left * (-scale);
	position = position + speed;
}

/* 
 * Moves the camera up.
 * 
 * No parameters.
 * No return.
 */
void Camera::moveUp() {
	speed = up * scale;
	position = position + speed;
}

/* 
 * Moves the camera down.
 * 
 * No parameters.
 * No return.
 */
void Camera::moveDown() {
	speed = up * (-scale);
	position = position + speed;
}

/* 
 * Updates yaw (the mouse movement implemented in this project).
 * 
 * Parameters: `dYaw`.
 * No return.
 */
void Camera::updateYaw(float dYaw) {
	yaw += dYaw;
}

/* 
 * Updates the camera direction.
 * 
 * No parameters.
 * No return.
 */
void Camera::update() {
	float angleInRadians = degreesToRadian(yaw);
	direction.x = sin(angleInRadians);
	direction.z = -cos(angleInRadians);
	direction.normalizeVector();
	left = up.crossProduct(direction);
}

/* 
 * Set a new camera position.
 * 
 * Parameters: `newPosition` and `newDirection`.
 * No return.
 */
void Camera::setCameraPosition(Vec3 newPosition, Vec3 newDirection){
	position = newPosition;
	direction = newDirection;
}