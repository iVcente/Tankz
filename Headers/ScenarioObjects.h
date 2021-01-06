#ifndef SCENARIO_OBJECTS_H
#define SCENARIO_OBJECTS_H

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

/*
 ? This header file is responsible for drawing the game scenario. It also 
 ? defines a struct WallBlock that is used to construct the division wall.
 */

struct WallBlock {
	Vec3 position;
	Vec3 dimensions = Vec3(1.0f, 1.0f, 1.0f);
	BoundingBox box;
	bool destroyed = false;

	WallBlock(Vec3 position){
        this->position = position;
		box.center = position;
		box.halfSize = dimensions / 2.0f;
    }
};

/* 
 * Auxiliary function that draws the scenario's walls.
 * 
 * Parameters: `textureID`.
 * No return.
 */
void drawWalls(GLuint textureID) {
	// Front wall
	glPushMatrix();
		glTranslatef(1.0f, -0.5f, 0.0f);
		glScalef(MAX_WIDTH, MAX_HEIGHT, MIN_HEIGHT);
		glColor3ub(220, 0, 0);
		drawSquare(textureID);
	glPopMatrix();

	// Back wall
	glPushMatrix();
		glTranslatef(1.0f, -0.5f, -25.0);
		glScalef(MAX_WIDTH, MAX_HEIGHT, MIN_HEIGHT);
		glColor3ub(220, 0, 0);
		drawSquare(textureID);
	glPopMatrix();
	
	// Left wall
	glPushMatrix();
		glTranslatef(1.0f, -0.5f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(MAX_DEPTH, MAX_HEIGHT, 0.0f);
		glColor3ub(220, 0, 0);
		drawSquare(textureID);
	glPopMatrix();
	
	// Right wall
	glPushMatrix();
		glTranslatef(51.0f, -0.5f, 0.0);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(MAX_DEPTH, MAX_HEIGHT, 0.0f);
		glColor3ub(220, 0, 0);
		drawSquare(textureID);
	glPopMatrix();
}

/* 
 * Create the blocks from the division wall.
 * 
 * Parameters: `blocks`.
 * No return.
 */
void createDivisionWall(std::vector<WallBlock>& blocks) {
	float y = MIN_HEIGHT;

	for (int line = 0; line < DIV_WALL_HEIGHT; line++) {
		float z = -0.5f;
		for (int column = 0; column < MAX_DEPTH; column++) {
			Vec3 position = Vec3(25.0f, y, z);
			WallBlock block = WallBlock(position);

			blocks.push_back(block);

			z -= 1.0;
		}
		y += 1.0f;
	}
}

/* 
 * Auxiliary function that draws the division wall.
 * 
 * Parameters: `textureID` and `blocks`.
 * No return.
 */
void drawDivisionWall(GLuint textureID, std::vector<WallBlock>& blocks) {
		
	for (WallBlock b : blocks) {
		if (b.destroyed)
			continue;
		
		glPushMatrix();
			glTranslatef(b.position.x, b.position.y, b.position.z);
			glColor3ubv(blue.rgb);
			drawCube(textureID, b.dimensions.x);
		glPopMatrix();
	}
}

/* 
 * Draws the division wall blocks' bounding boxes.
 * 
 * Parameters: `blocks`.
 * No return.
 */
void drawDivisionWallBB(std::vector<WallBlock>& blocks) {
	for (WallBlock b : blocks) {
		if (b.destroyed)
			continue;
		Vec3 center = b.box.center;
		Vec3 halfSize = b.box.halfSize;

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
		glColor3ubv(lightBlue.rgb);
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
}

/* 
 * Auxiliary function that draws the scenario's floor.
 * 
 * Parameters: `textureID`.
 * No return.
 */
void drawFloor(GLuint textureID) {
	glPushMatrix();
		glTranslatef(1.0f, -0.5f, 0.0f);
		glScalef(MAX_WIDTH, 0.0f, -MAX_DEPTH);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glColor3ub(0, 250, 60);
		drawSquare(textureID);
	glPopMatrix();
}

/* 
 * Draws the scenario's walls.
 * 
 * Parameters: `textureID`.
 * No return.
 */
void drawScenario(GLuint texturesIDs[], std::vector<WallBlock>& blocks) {
	drawFloor(texturesIDs[0]);
	drawWalls(texturesIDs[1]);
	drawDivisionWall(texturesIDs[2], blocks);
}

#endif // SCENARIO_OBJECTS_H