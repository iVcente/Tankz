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

#include <iostream>

#include "Headers/BasePolygons.h"
#include "Headers/Colors.h"
#include "Headers/Physics.h"
#include "Headers/Projectile.h"

/* 
 * Constructor for Projectile.
 * 
 * No parameters.
 * Returns an instance of `Projectile`.
 */
Projectile::Projectile(){
    position = Vec3(0.0f, 0.0f, 0.0f);
    direction = Vec3(0.0f, 0.0f, 0.0f);
    launchAngle = 0.0f;
    box.center = position;
    box.halfSize = dimensions / 2.0f;
}

/* 
 * Sets projectile's position.
 * 
 * Parameters: `pos`.
 * No return.
 */
void Projectile::setPosition(Vec3 pos) {
    position = pos;
}

/* 
 * Sets projectile's direction.
 * 
 * Parameters: `dir`.
 * No return.
 */
void Projectile::setDirection(Vec3 dir) {
    direction = dir;
}

/* 
 * Sets projectile's launch angle.
 * 
 * Parameters: `angle`.
 * No return.
 */
void Projectile::setLaunchAngle(float angle) {
    launchAngle = angle;
}

/* 
 * Launches the projectile.
 * 
 * No parameters.
 * No return.
 */
void Projectile::launch() {
    launched = true;
}

/* 
 * Destroys the projectile.
 * 
 * No parameters.
 * No return.
 */
void Projectile::gotDestroyed() {
    time = 0.0f;
    launched = false;
}

/* 
 * Checks if the projectile has already been launched.
 * 
 * No parameters.
 * Return `true` or `false`.
 */
bool Projectile::isLaunched() {
    return launched;
}

/* 
 * Updates de projectile position.
 * 
 * No parameters.
 * No return.
 */
void Projectile::updatePosition() {
    //Vec3 newPosition = position + (direction * speed);
    //float newZ = position.z + (direction.z * speed); 
    //time += 0.003f;
    //time += 0.004f;
    //time += 0.0045f;
    time += 0.005f;
    //time += 0.0055f;
    //time += 0.006f;
    //time += 0.010f;
    MotionXY newXY = projectileMotion(position.x, position.y, launchAngle, time);
    //Vec3 newPosition = Vec3(newXY.newX, newXY.newY, newZ);
    Vec3 newPosition = Vec3(newXY.newX, newXY.newY, position.z);
    BoundingBox newBox = BoundingBox(newPosition, box.halfSize);

    if (insideBoundariesProjectile(newBox, newPosition)) {
        position = newPosition;
        box.center = position;
    }
    else {
        launched = false;
        time = 0.0f;
    }
}

/* 
 * Draws the projectile.
 * 
 * No parameters.
 * No return.
 */
void Projectile::drawProjectile() {
    float size = dimensions.x;

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glColor3ubv(purple.rgb);
        drawCube(0, size);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

    updatePosition();
}

/* 
 * Draws the projectile's bounding box.
 * 
 * No parameters.
 * No return.
 */
void Projectile::drawBoundingBox() {
    Vec3 center = box.center;
    Vec3 halfSize = box.halfSize;

    float v1[3] = {center.x - halfSize.x, center.y + halfSize.y, center.z + halfSize.z};
	float v2[3] = {center.x - halfSize.x, center.y - halfSize.y, center.z + halfSize.z};
	float v3[3] = {center.x + halfSize.x, center.y - halfSize.y, center.z + halfSize.z};
	float v4[3] = {center.x + halfSize.x, center.y + halfSize.y, center.z + halfSize.z};

	float v5[3] = {center.x + halfSize.x, center.y + halfSize.y, center.z - halfSize.z};
	float v6[3] = {center.x + halfSize.x, center.y - halfSize.y, center.z - halfSize.z};
	float v7[3] = {center.x - halfSize.x, center.y - halfSize.y, center.z - halfSize.z};
	float v8[3] = {center.x - halfSize.x, center.y + halfSize.y, center.z - halfSize.z};

    glDisable(GL_TEXTURE_2D);
    glLineWidth(2);
    glColor3ubv(yellow.rgb);
    glBegin(GL_LINE_LOOP);
        // Front face
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glVertex3fv(v4);
		// Back face
		glVertex3fv(v5);
		glVertex3fv(v6);
		glVertex3fv(v7);
		glVertex3fv(v8);
		// Up face
		glVertex3fv(v8);
		glVertex3fv(v1);
		glVertex3fv(v4);
		glVertex3fv(v5);
		// Down face
		glVertex3fv(v6);
		glVertex3fv(v3);
		glVertex3fv(v2);
		glVertex3fv(v7);
		// Right face
		glVertex3fv(v4);
		glVertex3fv(v3);
		glVertex3fv(v6);
		glVertex3fv(v5);
		// Left face
		glVertex3fv(v8);
		glVertex3fv(v7);
		glVertex3fv(v2);
		glVertex3fv(v1);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

/* 
 * Obtain the projectile's bounding box.
 * 
 * No parameters.
 * Returns the `box` of type `BoundingBox`.
 */
BoundingBox Projectile::getBoundingBox() {
    return box;
}