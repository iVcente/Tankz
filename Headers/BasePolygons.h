#ifndef BASE_POLYGONS_H
#define BASE_POLYGONS_H

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

/*
 ? This header file provides two base functions for drawing polygons:
 ? a cube and a square.
 */

/* 
 * Draws a cube.
 * 
 * Parameters: `textureID` and `size`.
 * No return.
 */
inline void drawCube(GLuint textureID, float size) {	
	
	float halfSize = size / 2.0;

	float v1[3] = {-halfSize,  halfSize, halfSize};
	float v2[3] = {-halfSize, -halfSize, halfSize};
	float v3[3] = { halfSize, -halfSize, halfSize};
	float v4[3] = { halfSize,  halfSize, halfSize};

	float v5[3] = { halfSize,  halfSize, -halfSize};
	float v6[3] = { halfSize, -halfSize, -halfSize};
	float v7[3] = {-halfSize, -halfSize, -halfSize};
	float v8[3] = {-halfSize,  halfSize, -halfSize};

	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
		// Front face
		glNormal3f(0, 0, 1);
			glTexCoord2f(0.0, 1.0); glVertex3fv(v1);
			glTexCoord2f(0.0, 0.0); glVertex3fv(v2);
			glTexCoord2f(1.0, 0.0); glVertex3fv(v3);
			glTexCoord2f(1.0, 1.0); glVertex3fv(v4);
		// Back face
		glNormal3f(0, 0, -1);
			glTexCoord2f(0.0, 1.0); glVertex3fv(v5);
			glTexCoord2f(0.0, 0.0); glVertex3fv(v8);
			glTexCoord2f(1.0, 0.0); glVertex3fv(v7);
			glTexCoord2f(1.0, 1.0); glVertex3fv(v6);
		// Up face
		glNormal3f(0, 1, 0);
			glTexCoord2f(0.0, 1.0); glVertex3fv(v8);
			glTexCoord2f(0.0, 0.0); glVertex3fv(v1);
			glTexCoord2f(1.0, 0.0); glVertex3fv(v4);
			glTexCoord2f(1.0, 1.0); glVertex3fv(v5);
		// Down face
		glNormal3f(0, -1, 0);
			glTexCoord2f(0.0, 1.0); glVertex3fv(v6);
			glTexCoord2f(0.0, 0.0); glVertex3fv(v3);
			glTexCoord2f(1.0, 0.0); glVertex3fv(v2);
			glTexCoord2f(1.0, 1.0); glVertex3fv(v7);
		// Right face
		glNormal3f(1, 0, 0);
			glTexCoord2f(0.0, 1.0); glVertex3fv(v4);
			glTexCoord2f(0.0, 0.0); glVertex3fv(v3);
			glTexCoord2f(1.0, 0.0); glVertex3fv(v6);
			glTexCoord2f(1.0, 1.0); glVertex3fv(v5);
		// Left face
		glNormal3f(-1, 0, 0);
			glTexCoord2f(0.0, 1.0); glVertex3fv(v8);
			glTexCoord2f(0.0, 0.0); glVertex3fv(v7);
			glTexCoord2f(1.0, 0.0); glVertex3fv(v2);
			glTexCoord2f(1.0, 1.0); glVertex3fv(v1);
	glEnd();
}

/* 
 * Draws a 1x1 square.
 * 
 * Parameters: `textureID`.
 * No return.
 */
inline void drawSquare(GLuint textureID) {
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
			glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();
}

#endif // BASE_POLYGONS_H