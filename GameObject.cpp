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

#include "Headers/GameObject.h"

/* 
 * Constructor for GameObject.
 * 
 * Parameters: `enemy`, `model`, `initialPosition` and `color`.
 * Returns an instance of `GameObject`.
 */
GameObject::GameObject(bool enemy, Model model, Vec3 initialPosition, Color color) {
    this->enemy = enemy;
    this->model = model;
    position = initialPosition;
    this->color = color;
    boundingBox.center = position + ((model.maxVertex + model.minVertex) / 2.0f);
    boundingBox.halfSize = (model.maxVertex - model.minVertex) / 2.0f;
}

/* 
 * Draws a game object with its model read from a file.
 * 
 * No parameters.
 * No return.
 */
void GameObject::drawGameObject() {
    
    //glPolygonMode(GL_FRONT, GL_FILL);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glColor3ubv(color.rgb);
    std::vector<Vec3> v = model.vertices; // Vertices
    std::vector<VertexNormal> vn = model.verticesNormals; // Vertices normals

    for (int i = 0; i < model.faces.size(); i++) {
        Face f = model.faces.at(i); // Current face

        glBegin(GL_TRIANGLES);
            glNormal3f(vn.at(f.vn1 - 1).x, vn.at(f.vn1 - 1).y, vn.at(f.vn1 - 1).z); 
            glVertex3f(v.at(f.v1 - 1).x, v.at(f.v1 - 1).y, v.at(f.v1 - 1).z);

            glNormal3f(vn.at(f.vn2 - 1).x, vn.at(f.vn2 - 1).y, vn.at(f.vn2 - 1).z);
			glVertex3f(v.at(f.v2 - 1).x, v.at(f.v2 - 1).y, v.at(f.v2 - 1).z);

            glNormal3f(vn.at(f.vn3 - 1).x, vn.at(f.vn3 - 1).y, vn.at(f.vn3 - 1).z);
			glVertex3f(v.at(f.v3 - 1).x, v.at(f.v3 - 1).y, v.at(f.v3 - 1).z);
	    glEnd();
    }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

/* 
 * Draws a game object bounding box.
 * 
 * No parameters.
 * No return.
 */
void GameObject::drawBoundingBox() {
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
    glColor3ubv(pink.rgb);
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
 * Checks if the game object has been destroyed.
 * 
 * No parameters.
 * Returns `true` or `false`.
 */
bool GameObject::isDestroyed() {
	return destroyed;
}

/* 
 * Destroys the game object.
 * 
 * No parameters.
 * No return.
 */
void GameObject::destroy() {
	destroyed = true;
}

/* 
 * Draws a game object bounding box.
 * 
 * No parameters.
 * Returns the game object's bounding box of the type `BoundingBox`.
 */
BoundingBox GameObject::getBoundingBox() {
	return boundingBox;
}

/* 
 * Checks if a game object is an enemy or an ally.
 * 
 * No parameters.
 * Returns `true` or `false`.
 */
bool GameObject::isEnemy() {
	return enemy;
}