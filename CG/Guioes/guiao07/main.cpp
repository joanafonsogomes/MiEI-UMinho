
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <tuple>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

unsigned char* imageData;

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

float alpha = 0.0f, beta = 0.5f, r = 100.0f;

int rc = 15, ri = 35, rr = 50;
float dimTeapot = 1.5;
vector<tuple<float, float>> trees;
float offsetInner = 0;
float offsetOutter = 0;
#define TREE_NUM 180

unsigned int scaleFactor = 80;
unsigned int imageHeight = 0;
unsigned int imageWidth = 0;


GLuint buffer[1];
std::vector<std::vector<int>> heights;
std::vector<float> points;
std::vector<float> cposition = { 7, 0, 7 };
std::vector<float> lookat = { 1.0, 0.0, 0.0 };


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45, ratio, 1, 1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

float h(int x, int z) {
	x += imageWidth / 2;
	z += imageHeight / 2;
	return ((((float)imageData[z * imageWidth + x]) / 255) * scaleFactor);
}

float hf(float px, float pz) {

	int x1 = floor(px); int x2 = x1 + 1;
	int z1 = floor(pz); int z2 = z1 + 1;

	float fz = pz - z1;
	float fx = px - x1;


	float h_x1_z = h(x1, z1) * (1 - fz) + h(x1, z2) * fz;
	float h_x2_z = h(x2, z1) * (1 - fz) + h(x2, z2) * fz;

	return h_x1_z * (1 - fx) + h_x2_z * fx;

}


void init() {
	ilInit();

	unsigned int t;

	ilGenImages(1, &t);
	ilBindImage(t);

	// 	Load the height map "terreno.jpg"
	ilLoadImage((ILstring)"terreno.jpg");
	// convert the image to single channel per pixel
	// with values ranging between 0 and 255
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

	imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
	imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);

	imageData = ilGetData();


	// 	Build the vertex arrays

	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			points.push_back(-(((float)imageWidth - 1) / 2) + j); points.push_back((((float)imageData[i * imageWidth + j]) / 255) * scaleFactor); points.push_back(-(((float)imageHeight - 1) / 2) + i);
			points.push_back(-(((float)imageWidth - 1) / 2) + j); points.push_back((((float)imageData[(i + 1) * imageWidth + j]) / 255) * scaleFactor); points.push_back(-(((float)imageHeight - 1) / 2) + i + 1);
		}
	}

	// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void drawTerrain() {
	// colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	
	for (int i = 0; i < imageHeight - 1; i++) {

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0, 0.5, 0.0);
		glDrawArrays(GL_TRIANGLE_STRIP, (imageWidth) * 2 * i, (imageWidth) * 2);
	}

}



void renderScene(void) {

	float pos[4] = { -1.0, 1.0, 1.0, 0.0 };
	float eyeheight = 1.8;
	float ly = hf(cposition[0], cposition[2]) + eyeheight;
	cposition[1] = ly;

	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(cposition[0],cposition[1],cposition[2],
		lookat[0], ly, lookat[2],
		0.0f, 1.0f, 0.0f);

	drawTerrain();


	//inner circle teapots
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glColor3f(0.137255, 0.137255, 0.556863);
		float ang = (((2 * M_PI) / 8) * i) + offsetInner;
		glTranslatef(rc * cos(ang), dimTeapot, rc * sin(ang));
		glRotatef(-((ang) * 360) / (2 * M_PI), 0, 1, 0);
		glutSolidTeapot(dimTeapot);
		glPopMatrix();
	}

	//outter circle teapots
	for (int i = 0; i < 16; i++) {
		glPushMatrix();
		glColor3f(1, 0, 0);
		float ang = (((2 * M_PI) / 16) * i) - offsetOutter;
		glTranslatef(ri * cos(ang), dimTeapot, ri * sin(ang));
		glRotatef(-((ang) * 360) / (2 * M_PI), 0, 1, 0);
		glRotatef((((9 * M_PI) / 16) * 360) / (2 * M_PI), 0, 1, 0);
		glutSolidTeapot(dimTeapot);
		glPopMatrix();
	}


	for (int i = 0; i < trees.size(); i++) {
		float r1 = get<0>(trees[i]);
		float r2 = get<1>(trees[i]);

		//tronco
		glPushMatrix();
		glTranslatef(r1, hf(r1, r2), r2);
		glColor3f(0.12f, 0.11f, 0.0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(0.4, 2, 40, 40);
		glPopMatrix();

		//"folhas"
		glPushMatrix();
		glTranslatef(r1, hf(r1, r2), r2);
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



void keysMove(unsigned char key, int x, int y) {

	std::vector<float> d = { lookat[0] - cposition[0], 0 , lookat[2] - cposition[2] };
	std::vector<float> up = { 0.0, 0.1, 0.0 };
	float k = 5;
	std::vector<float> kr = { k*(d[1] * up[2] - d[2] * up[1]), k*(d[2] * up[0] - d[0] * up[2]), k*(d[0] * up[1] - d[1] * up[0])};

	if (key == 'A' || key == 'a') {
		if ((sqrt(pow(cposition[0], 2) + pow(cposition[1], 2) + pow(cposition[2],2))) <= 250) {
			cposition = { cposition[0] + kr[0] , cposition[1] + kr[1] , cposition[2] + kr[2] };
			lookat = { lookat[0] + kr[0] , lookat[1] + kr[1] , lookat[2] + kr[2] };
			glutPostRedisplay();
		}
	}
	else if (key == 'S' || key == 's') {
		if ((sqrt(pow(cposition[0], 2) + pow(cposition[1], 2) + pow(cposition[2], 2))) <= 250) {
			cposition = { cposition[0] - d[0] , cposition[1] - d[1] , cposition[2] - d[2] };
			lookat = { lookat[0] - d[0] , lookat[1] - d[1] , lookat[2] - d[2] };
			glutPostRedisplay();
		}
	}
	else if (key == 'd' || key == 'D') {
		if ((sqrt(pow(cposition[0], 2) + pow(cposition[1], 2) + pow(cposition[2], 2))) <= 250) {
			cposition = { cposition[0] - kr[0] , cposition[1] - kr[1] , cposition[2] - kr[2] };
			lookat = { lookat[0] - kr[0] , lookat[1] - kr[1] , lookat[2] - kr[2] };
			glutPostRedisplay();
		}
	}
	else if (key == 'w' || key == 'W') {
		if ((sqrt(pow(cposition[0], 2) + pow(cposition[1], 2) + pow(cposition[2], 2))) <= 250) {
			cposition = { cposition[0] + d[0] , cposition[1] + d[1] , cposition[2] + d[2] };
			lookat = { lookat[0] + d[0] , lookat[1] + d[1] , lookat[2] + d[2] };
			glutPostRedisplay();
		}
	}
	else if (key == 'R' || key == 'r') {
		alpha += 0.1;
		lookat[0] = cposition[0] + sin(alpha);
		lookat[2] = cposition[2] + cos(alpha);
		glutPostRedisplay();
	}


}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alpha -= 0.1;
		lookat[0] = cposition[0] + sin(alpha);
		lookat[2] = cposition[2] + cos(alpha);
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		alpha += 0.1;
		lookat[0] = cposition[0] + sin(alpha);
		lookat[2] = cposition[2] + cos(alpha);
		glutPostRedisplay();
		break;
	default:
		break;
	}

}



void randomTree() {
	float r1, r2;
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < TREE_NUM; i++) {
		r1 = -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100 - (-100))));
		r2 = -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100 - (-100))));

		if (sqrt(pow(r1, 2) + pow(r2, 2)) <= 50)  i--;
		else {
			trees.push_back(make_tuple(r1, r2));
		}

	}
}

void animation(int value) {
	offsetInner += 0.05;
	offsetOutter += 0.05;
	glutPostRedisplay();
	glutTimerFunc(1, animation, 0);
}

int main(int argc, char** argv) {
	randomTree();
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keysMove);
	init();

#ifndef __APPLE__
	glewInit();
#endif

	glGenBuffers(1, buffer);
	glEnableClientState(GL_VERTEX_ARRAY);

	glutTimerFunc(1, animation, 0);

	// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}

