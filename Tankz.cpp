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
#include <vector>

#include "Headers/Camera.h"
#include "Headers/GameObject.h"
#include "Headers/Physics.h"
#include "Headers/Player.h"
#include "Headers/ScenarioObjects.h"
#include "Headers/stb_image.h"

Camera camera(Vec3(20, 10, 8)); // Camera initial coordinates
std::vector<WallBlock> blocks;
std::vector<GameObject> gameObjects;
std::vector<Model> models;
Player player = Player();
Projectile projectile = Projectile();
GLuint texturesIDs[6]; // Textures identifiers
int score = 0;
int enemies = 0;
int allies = 0;
static float lastMousePos = 0.0f;
static bool firstTimeMouse = true;

/* 
 * Defines the scenario's lighting.
 * 
 * No parameters.
 * No return.  
 */
void defineLighting() {
	// Define the colors for a golden object
	GLfloat ambientLighting[] = {0.24725f, 0.1995f, 0.07f};
	GLfloat diffuseLighting[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
	GLfloat specularLighting[] = {0.626281f, 0.555802f, 0.366065f, 1.0f};
	GLfloat lightingPosition0[] = {3.0f, 3.0f, 0.0f, 1.0f};
	GLfloat lightingPosition1[] = {-3.0f, -3.0f, 0.0f, 1.0f};
  	GLfloat specularity[] = {1.0f, 1.0f, 1.0f, 1.0f};

	// ! Lighting source 0
	glEnable(GL_COLOR_MATERIAL);

	// Enables the use of lighting
  	glEnable(GL_LIGHTING);
	// Activates the use of ambient lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLighting);
	// Define de parameters of lighting 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLighting);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLighting);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLighting);
	glLightfv(GL_LIGHT0, GL_POSITION, lightingPosition0);
	glEnable(GL_LIGHT0);

	// Enables the "color tracking"
	glEnable(GL_COLOR_MATERIAL);

	// Define the material's reflectance
	glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);

	// Defines the brightness concentration

	// Larger the value of the second parameter, more concentrated its brightness will be. Values accepted: from 0 to 128.
	glMateriali(GL_FRONT,GL_SHININESS, 51);

	// ! Lighting source 1

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLighting);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLighting);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLighting);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLighting);
	glLightfv(GL_LIGHT1, GL_POSITION, lightingPosition1);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);

	glMateriali(GL_FRONT, GL_SHININESS, 20);
}

/* 
 * Auxiliary function that loads a single texture.
 * 
 * Parameters: `textureID` and `filePath`.
 * No return.
 */
void loadTexture(GLuint textureID, std::string filePath) {
	unsigned char* imageData;
	int width, heigth, channels;

	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load(filePath.c_str(), &width, &heigth, &channels, 4);
	if (imageData) {
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		stbi_image_free(imageData);
	}
	else {
		std::cout << "ERROR: It wasnt possible to load the texture!" << filePath.c_str() << std::endl;
		exit(EXIT_FAILURE);
	}
}

/* 
 * Load all textures.
 * 
 * No parameters.
 * No return.
 */
void loadTextures() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glGenTextures(6, texturesIDs);

	loadTexture(texturesIDs[0], "Images/FloorTexture2.png");
	loadTexture(texturesIDs[1], "Images/WallTexture3.png");
	loadTexture(texturesIDs[2], "Images/DivisionWallTexture2.png");
	loadTexture(texturesIDs[3], "Images/Camouflage7.png");
	loadTexture(texturesIDs[4], "Images/Camouflage8.png");
	loadTexture(texturesIDs[5], "Images/Camouflage9.png");
}

/* 
 * Load all 3D models.
 * 
 * No parameters.
 * No return.
 */
void loadModels() {
	loadModel("3DObjects/Tree1.obj", models);
	loadModel("3DObjects/Tree2.obj", models);
}

/* 
 * Generates a random bool used for distributing allies and enemies on the scenario.
 * 
 * No parameters.
 * Returns `true` or `false`.
 */
bool randomBool() {
	return rand() % 2 == 0;
}

/* 
 * Load all game objects (3D objects from the .obj files).
 * 
 * No parameters.
 * No return.
 */
void loadGameObjects() {
	const int gameObjectsAmount = 20; // Number of game objects to be created
	float initialZ = -23.0f;
	Vec3 initialPosition = Vec3(48.0f, 0.0f, initialZ);

	for (int i = 0; i < gameObjectsAmount; i++) {
		bool enemy = randomBool();

		// This IF has the purpose of determining the position of the game objects
		if (initialPosition.z > -2.0f) {
			initialPosition.z = initialZ;
			initialPosition.x -= 5.0f;
		}
 
		if (!enemy) {
			GameObject object = GameObject(enemy, models.at(0), initialPosition, blue);
			gameObjects.push_back(object);
		}
		else {
			GameObject object = GameObject(enemy, models.at(1), initialPosition, red);
			gameObjects.push_back(object);
		}

		initialPosition.z += 5.0f;
	}
}

/* 
 * Checks if there's collision between the projectile and the wall blocks, enemies or allies.
 * 
 * No parameters.
 * No return.
 */
void checkObjectsCollisions() {
	for (WallBlock& block : blocks) {
		if (block.destroyed)
			continue;

		if (checkCollision(block.box, projectile.getBoundingBox())) {
			block.destroyed = true;
			projectile.gotDestroyed();
			score -= 5;
			std::cout << "Wall block destroyed: -5 points!" << "\n";
			break; // We break because there's no need to check another block or game object. The projectile can only destroy one object at a time.
		}
	}
	
	for (GameObject& object : gameObjects) {
		if (object.isDestroyed())
			continue;

		if (checkCollision(object.getBoundingBox(), projectile.getBoundingBox())) {
			if (object.isEnemy()) {
				score += 10;
				std::cout << "Enemy destroyed: +10 points!" << "\n";
			}
			else {
				score -= 10;
				std::cout << "Ally destroyed: -10 points!" << "\n";
			}
			object.destroy();
			projectile.gotDestroyed();
			break;
		}
	}
}

/* 
 * Draws every game object previously loaded in case the game object hasnt been destroyed yet.
 * 
 * No parameters.
 * No return.
 */
void drawGameObjects() {
	for (GameObject object : gameObjects) {
		if (!object.isDestroyed())
			object.drawGameObject();
	}
}

/* 
 * Draws the bounding boxes (used for checking collision) for every game object previously loaded.
 * 
 * No parameters.
 * No return.
 */
void drawGameObjectsBoundingBoxes() {
	for (GameObject object : gameObjects)
		object.drawBoundingBox();
}

/* 
 * Counts the number of allies and enemies created in the match. This function helps `gameIsOver` indirectly.
 * 
 * No parameters.
 * No return.
 */
void countEnemiesAllies() {
	for (GameObject& obj : gameObjects) {
		if (obj.isEnemy())
			enemies++;
		else
			allies++;
	}
}

/* 
 * Checks if the game is over.
 * 
 * No parameters.
 * Returns `true` or `false`.
 */
bool gameIsOver() {
	int countDeadEnemies = 0;
	int countDeadAllies = 0;

	for (GameObject& obj : gameObjects) {
		if (obj.isDestroyed() && obj.isEnemy())
			countDeadEnemies++;
		else if (obj.isDestroyed() && !obj.isEnemy())
			countDeadAllies++;
	}

	if ((countDeadEnemies == enemies) && enemies > 0)
		return true;

	if ((countDeadEnemies + countDeadAllies) == (enemies + allies))
		return true;

	return false;
}

/* 
 * Initializes stuff only once.
 * 
 * No parameters.
 * No return.
 */
void init() {
	glClearColor(0.0, 0.15, 0.25, 1.0); // Background color

	glShadeModel(GL_SMOOTH);						
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	loadModels();
	loadGameObjects();
	countEnemiesAllies();
	createDivisionWall(blocks);
	loadTextures();
}

/* 
 * This is called every time the window must be resized.
 * 
 * No parameters.
 * No return.
 */
void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	// Ajust the ration between width and height in order avoid image distortion
	GLfloat aspectRatio = (1.0f * w) / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(90, aspectRatio, 0.01, 100); // Perspective projection
}

/* 
 * This function draws everything that needs to be draw on the screnn. `display` is called every frame.
 * 
 * No parameters.
 * No return.
 */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.activate();
	defineLighting();
	drawScenario(texturesIDs, blocks);
	//drawDivisionWallBB(blocks);
	player.drawTank(texturesIDs);
	//player.drawBoundingBox();
	drawGameObjects();

	if (projectile.isLaunched()) {
		projectile.drawProjectile();
		checkObjectsCollisions();
		//projectile.drawBoundingBox();	
	}
	//drawGameObjectsBoundingBoxes();

	if (gameIsOver()) {
		std::cout << "<--- GAME OVER! --->" << "\n";
		std::cout << "Your score: " << score << " points!" << "\n";
		exit(0);
	}

	glutSwapBuffers();
}

/* 
 * Responsible for moving the camera with the mouse.
 * 
 * Parameters: `xPos` and `yPos`.
 * No return.
 */
void mouse(int xPos, int yPos) {
	GLfloat deltaX;

	if (firstTimeMouse) {
		deltaX = 0;
		lastMousePos = xPos;
		firstTimeMouse = false;
	}
	deltaX = xPos - lastMousePos;
	lastMousePos = xPos;
	camera.updateYaw(deltaX);
	camera.update();
}

/* 
 * Responsible for capturing the "common" keys pressed in the keyboard and by giving meaning to them.
 * 
 * Parameters: `key`, `x` and `y`.
 * No return.
 */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			player.moveForward(); // Moves the tank forward
			break;
		case 's': 
			player.moveBackward(); // Moves the tank backward
			break;
		case 'a':
			player.rotateLeft(); // Rotates the tank to the left
			break;
		case ' ': // Shoots
			if (!projectile.isLaunched())
				player.shoot(projectile);
			break;
		case 'd':
			player.rotateRight(); // Rotates the tank to the right
			break;
		case 'i':
            camera.moveForward(); // Moves the camera forward
			break;
		case 'k':
            camera.moveBackward(); // Moves the camera backward
			break;
		case 'l':
            camera.moveUp(); // Moves the camera up
			break;
        case 'j':
			camera.moveDown(); // Moves the camera down
			break;
		case '1': // Sets the camera position looking to the center of the scenario while being at the left side
			camera.setCameraPosition(Vec3(-5.0f, 8.0f, -12.0f), Vec3(1.0f, 0.0f, 0.0f));
			break;
		case '2': // Sets the camera position looking to the center of the scenario while being at the top side
			camera.setCameraPosition(Vec3(25.0f, 8.0f, -30.0f), Vec3(0.0f, 0.0f, 1.0f));
			break;
		case '3': // Sets the camera position looking to the center of the scenario while being at the right side
			camera.setCameraPosition(Vec3(55.0f, 8.0f, -12.0f), Vec3(-1.0f, 0.0f, 0.0f));
			break;
		case '4': // Sets the camera position looking to the center of the scenario while being at the bottom side
			camera.setCameraPosition(Vec3(25.0f, 8.0f, 5.0f), Vec3(0.0f, 0.0f, -1.0f));
			break;
		case '5': // Sets the camera position looking to the center of the scenario while being at the left side and with a higher Y
			camera.setCameraPosition(Vec3(-5.0f, 15.0f, -12.0f), Vec3(1.0f, 0.0f, 0.0f));
			break;
    	case 'f':
            glutFullScreen();   
			break;
		// TODO: Crashing the program at the moment.
        case 'g':
			glutPositionWindow(50,50);
			glutReshapeWindow(700, 500);
		case 27: // Esc
			exit(0);
			break;      
    	default:        
      		break;
  	}
}

/* 
 * Responsible for capturing the arrow keys pressed in the keyboard and by giving meaning to them.
 * 
 * Parameters: `aKeys`, `x` and `y`.
 * No return.
 */
void arrowKeys(int aKeys, int x, int y)  {
	switch(aKeys) {
		case GLUT_KEY_UP:
			player.rotateCannonUp(); // Rotates the tank cannon up
			break;
	    case GLUT_KEY_DOWN:
			player.rotateCannonDown(); // Rotates the tank cannon down
			break;
		case GLUT_KEY_LEFT:
			player.rotateAxisLeft(); // Rotates the tank axis to the left
			break;
		case GLUT_KEY_RIGHT:
			player.rotateAxisRight(); // Rotates the tank axis to the right
			break;
		default:
			break;
	}
}

/* 
 * Disables the texture by the end of the program execution.
 * 
 * No parameter.
 * No return.
 */
void disableTextures() {
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(6, texturesIDs);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 500); 
	glutCreateWindow("Tankz"); 
		
	init();
	
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glutSpecialFunc(arrowKeys);
	glutIdleFunc(glutPostRedisplay);
	glutMainLoop();
	disableTextures();
	return 0; 
	//return EXIT_SUCCESS;
}
