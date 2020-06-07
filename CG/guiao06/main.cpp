
#include <iostream>
#include<stdio.h>
#include<stdlib.h>

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


float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

unsigned int scaleFactor = 30;
unsigned int imageHeight = 0;
unsigned int imageWidth = 0;

GLuint buffer[1];
std::vector<std::vector<int>> heights;
std::vector<float> points;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void init() {
	ilInit();

	unsigned int t;
	unsigned char* imageData;
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
			points.push_back(-(((float)imageWidth - 1) / 2) + j);points.push_back((((float)imageData[i * imageWidth + j]) / 255) * scaleFactor); points.push_back(-(((float)imageHeight - 1) / 2) + i);
			points.push_back(-(((float)imageWidth - 1) / 2) + j);points.push_back((((float)imageData[(i + 1) * imageWidth + j]) / 255) * scaleFactor); points.push_back(-(((float)imageHeight - 1) / 2) + i + 1);
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

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0, 0, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, (imageWidth) * 2 * i, (imageWidth) * 2);
	}
	
}



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(1.0f,1.0f,1.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawTerrain();

// End of frame
	glutSwapBuffers();
}



void processSpecialKeys(int key, int xx, int yy) {


}

void processKeys(unsigned char key, int xx, int yy) {


}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}

}


void processMouseMotion(int xx, int yy) {
			
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * sin(betaAux * 3.14 / 180.0);
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		


// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	init();	

#ifndef __APPLE__
	glewInit();
#endif

	glGenBuffers(1, buffer);
	glEnableClientState(GL_VERTEX_ARRAY);

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

