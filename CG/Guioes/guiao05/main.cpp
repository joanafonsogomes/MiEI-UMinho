#include <stdio.h>
#include <iostream>
#include <time.h>
#include <tuple>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

int rc=15, ri=35, r =50;
float dimTeapot = 1.5;
vector<tuple<float, float>> trees;
float offsetInner = 0;
float offsetOutter = 0;
#define TREE_NUM 180


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();

	//inner circle teapots
	for (int i = 0;i < 8;i++) {
		glPushMatrix();
		glColor3f(0.137255, 0.137255, 0.556863);
		float ang = (((2 * M_PI) / 8) * i) + offsetInner;
		glTranslatef(rc * cos(ang), dimTeapot, rc * sin(ang ));
		glRotatef(-((ang)*360)/(2*M_PI), 0, 1, 0);
		glutSolidTeapot(dimTeapot);
		glPopMatrix();
	}

	//outter circle teapots
	for (int i = 0;i < 16;i++) {
		glPushMatrix();
		glColor3f(1,0,0);
		float ang = (((2 * M_PI) / 16) * i) - offsetOutter;
		glTranslatef(ri * cos(ang), dimTeapot, ri * sin(ang));
		glRotatef(-((ang) * 360) / (2 * M_PI), 0, 1, 0);
		glRotatef((((9 * M_PI) / 16) * 360) / (2 * M_PI), 0, 1, 0);
		glutSolidTeapot(dimTeapot);
		glPopMatrix();
	}

	
	for (int i = 0; i < trees.size();i++) {
		float r1 = get<0>(trees[i]);
		float r2 = get<1>(trees[i]);

			//tronco
			glPushMatrix();
				glTranslatef(r1,0,r2);
				glColor3f(0.12f, 0.11f, 0.0);
				glRotatef(-90, 1, 0, 0);
				glutSolidCone(0.4, 2, 40, 40);
			glPopMatrix();

			//"folhas"
			glPushMatrix();
				glTranslatef(r1, 0, r2);
				glTranslatef(0, 1.5, 0);
				glRotatef(-90, 1, 0, 0);
				glColor3f(0.0f, 1.0f, 0.0);
				glutSolidCone(2, 5, 40, 40);
			glPopMatrix();

	}
	//torus
	glColor3f(1.0f, 0.11f, 0.68f);
	glTranslatef(0, 0.5f, 0);
	glutSolidTorus(1, 3, 20, 20);
	// End of frame
	glutSwapBuffers();
}

void randomTree() {
	float r1, r2;
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < TREE_NUM ;i++) {
		r1 = -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100 - (-100))));
		r2 = -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100 - (-100))));

		if (sqrt(pow(r1, 2) + pow(r2, 2)) <= 50)  i--;
		else {
			trees.push_back(make_tuple(r1,r2));
		}

	}
}

void animation(int value) {
	offsetInner += 0.02;
	offsetOutter += 0.02;
	glutPostRedisplay();
	glutTimerFunc(25, animation, 0);
}

void processKeys(unsigned char c, int xx, int yy) {

	switch (c)
	{
	case 'o':
		offsetInner+=0.1;
		offsetOutter += 0.1;
		glutPostRedisplay();

	default:
		break;
	}

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}



void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {
	randomTree();
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();
	glutTimerFunc(25, animation, 0);
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
