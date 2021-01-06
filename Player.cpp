#include "Headers/Colors.h"
#include "Headers/Physics.h"
#include "Headers/Player.h"

/* 
 * Constructor for Player.
 * 
 * No parameters.
 * Returns an instance of `PLayer`.
 */
Player::Player() {
    boundingBox.center = base.position;
    boundingBox.halfSize = base.dimensions / 2.0f;
}

/* 
 * Moves the tank's base forward.
 * 
 * No parameters.
 * No return.
 */
void Player::moveForward() {
    float newX = base.direction.x * speed;
    float newZ = base.direction.z * speed;
    Vec3 newBasePosition = base.position + Vec3(newX, 0, newZ); 

    if (insideBoundariesTank(boundingBox, newBasePosition)) {
        base.position = newBasePosition;
        axis.position = axis.position + Vec3(newX, 0, newZ);
        cannon.position = cannon.position + Vec3(newX, 0, newZ);
        boundingBox.center = base.position;
    }
}

/* 
 * Moves the tank's base backward.
 * 
 * No parameters.
 * No return.
 */
void Player::moveBackward() {
    float newX = base.direction.x * speed;
    float newZ = base.direction.z * speed;
    Vec3 newBasePosition = base.position - Vec3(newX, 0, newZ); 

    if (insideBoundariesTank(boundingBox, newBasePosition)) {
        base.position = newBasePosition;
        axis.position = axis.position - Vec3(newX, 0, newZ);
        cannon.position = cannon.position - Vec3(newX, 0, newZ);
        boundingBox.center = base.position;
    }
}

/* 
 * Rotates the tank's base left.
 * 
 * No parameters.
 * No return.
 */
void Player::rotateLeft() {
    float rotationAngleRadians = degreesToRadian(rotationAngleBase);
    float newX = (cosf(rotationAngleRadians) * base.direction.x) + (sinf(rotationAngleRadians) * base.direction.z);
    float newZ = (-sinf(rotationAngleRadians) * base.direction.x) + (cosf(rotationAngleRadians) * base.direction.z);

    base.direction = Vec3(newX, base.direction.y, newZ);

    currentBaseRotation += rotationAngleBase;
}

/* 
 * Rotates the tank's base right.
 * 
 * No parameters.
 * No return.
 */
void Player::rotateRight() {
    float rotationAngleRadians = degreesToRadian(rotationAngleBase);
    float newX = (cosf(rotationAngleRadians) * base.direction.x) - (sinf(rotationAngleRadians) * base.direction.z);
    float newZ = (sinf(rotationAngleRadians) * base.direction.x) + (cosf(rotationAngleRadians) * base.direction.z);

    base.direction = Vec3(newX, base.direction.y, newZ);

    currentBaseRotation -= rotationAngleBase;
}

/* 
 * Rotates the tank's axis left.
 * 
 * No parameters.
 * No return.
 */
void Player::rotateAxisLeft() {
    float rotationAngleRadians = degreesToRadian(rotationAngleAxis);
    float newX = (cosf(rotationAngleRadians) * axis.direction.x) + (sinf(rotationAngleRadians) * axis.direction.z);
    float newZ = (-sinf(rotationAngleRadians) * axis.direction.x) + (cosf(rotationAngleRadians) * axis.direction.z);

    axis.direction = Vec3(newX, axis.direction.y, newZ);

    currentAxisRotation += rotationAngleAxis;
}

/* 
 * Rotates the tank's axis right.
 * 
 * No parameters.
 * No return.
 */
void Player::rotateAxisRight() {
    float rotationAngleRadians = degreesToRadian(rotationAngleAxis);
    float newX = (cosf(rotationAngleRadians) * axis.direction.x) - (sinf(rotationAngleRadians) * axis.direction.z);
    float newZ = (sinf(rotationAngleRadians) * axis.direction.x) + (cosf(rotationAngleRadians) * axis.direction.z);

    axis.direction = Vec3(newX, axis.direction.y, newZ);

    currentAxisRotation -= rotationAngleAxis;
}

/* 
 * Rotates the tank's cannon up to a max of 55 degrees.
 * 
 * No parameters.
 * No return.
 */
void Player::rotateCannonUp() {
    if (currentCannonRotation < 55.0f)
        currentCannonRotation += rotationAngleCannon;
}

/* 
 * Rotates the tank's cannon down to a min of 0 degrees.
 * 
 * No parameters.
 * No return.
 */
void Player::rotateCannonDown() {
    if (currentCannonRotation > 0.0f)
        currentCannonRotation -= rotationAngleCannon;
}

/* 
 * Draw the tank's base bounding box.
 * 
 * No parameters.
 * No return.
 */
void Player::drawBoundingBox() {
    Vec3 center = boundingBox.center;
    Vec3 halfSize = boundingBox.halfSize;

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
    glColor3ubv(orange.rgb);
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
 * Auxiliary function to `drawTank()` thats draws the tank's cannon.
 * 
 * Parameters: `textureID`.
 * No return.
 */
void Player::drawCannon(GLuint textureID) {
    glPushMatrix();
        glTranslatef(cannon.position.x, cannon.position.y, cannon.position.z);
        glRotatef(currentAxisRotation, 0.0f, 1.0f, 0.0f);
        glRotatef(currentCannonRotation, 0.0f, 0.0f, 1.0f);
        glScalef(cannon.dimensions.x, cannon.dimensions.y, cannon.dimensions.z);
        glColor3ub(17, 191, 182);
        drawCube(textureID, 1.0f);
    glPopMatrix();
};

/* 
 * Auxiliary function to `drawTank()` thats draws the tank's axis.
 * 
 * Parameters: `textureID`.
 * No return.
 */
void Player::drawAxis(GLuint textureID) {
    glPushMatrix();
        glTranslatef(axis.position.x, axis.position.y, axis.position.z);
        glRotatef(currentAxisRotation, 0.0f, 1.0f, 0.0f);
        glScalef(axis.dimensions.x, axis.dimensions.y, axis.dimensions.z);
        glColor3ub(232, 77, 0);
        drawCube(textureID, 1.0f);
    glPopMatrix();
};

/* 
 * Auxiliary function to `drawTank()` thats draws the tank's base.
 * 
 * Parameters: `textureID`.
 * No return.
 */
void Player::drawBase(GLuint textureID) {
    glPushMatrix();
        glTranslatef(base.position.x, base.position.y, base.position.z);
        glRotatef(currentBaseRotation, 0.0f, 1.0f, 0.0f);
        glScalef(base.dimensions.x, base.dimensions.y, base.dimensions.z);
        glColor3ub(167, 66, 245);
        drawCube(textureID, 1.0f);
    glPopMatrix();
};

/* 
 * Draws the tank.
 * 
 * Parameters: `texturesIDs`.
 * No return.
 */
void Player::drawTank(GLuint texturesIDs[]) {
    drawBase(texturesIDs[3]);
    drawAxis(texturesIDs[4]);
    drawCannon(texturesIDs[5]);
};

/* 
 * Obtain the tank's cannon position.
 * 
 * Parameters: `projectile`.
 * No return.
 */
void Player::shoot(Projectile& projectile) {
    projectile.setPosition(cannon.position);
    projectile.setDirection(axis.direction);
    projectile.setLaunchAngle(currentCannonRotation);
    projectile.launch();
}