
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include "game.h"


#include <math.h>
#include "render.h"

//Initializing the light parameters
GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


void quit() {}

void init(camera *cam)
{
	cam->pos[0] = 3.5;
	cam->pos[1] = 14.75;
	cam->pos[2] = 6.0;

	cam->lookAt[0] = 3.5;
	cam->lookAt[1] = 4.75;
	cam->lookAt[2] = 0;

	cam->lookUp[0] = 0;
	cam->lookUp[1] = 1;
	cam->lookUp[2] = 0;
}

void initScene(int argc, char **argv) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	// Enable lighting
	glEnable(GL_LIGHTING);


	// Setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,128);
}

void denoteTurn(status stats)
{
	glPushMatrix();
	if(stats.turn == 1)	
	{
		glColor3f(1.0, 0.0, 0.0);
	}
	else if(stats.turn == 2)
	{
		glColor3f(0.0, 0.0, 1.0);
	}
	glTranslatef(4.3, 0.0, -11.7);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}

void denoteSelectedSlice(status stats)
{
	if(stats.secondMove == true)
	{
		glColor3f(1.0, 1.0, 0.0);

		glPushMatrix();
		if(stats.secondMovePart == 1)
		{
			glTranslatef(-2.5, -1.0, -12.0);
			glutSolidCube(0.5);
		}
		glPopMatrix();

		glPushMatrix();
		if(stats.secondMovePart == 2)
		{
			glTranslatef(11.0, -1.0, -12.0);
			glutSolidCube(0.5);
		}
		glPopMatrix();

		glPushMatrix();
		if(stats.secondMovePart == 4)
		{
			glTranslatef(11.0, -1.0, 0.5);
			glutSolidCube(0.5);
		}
		glPopMatrix();

		glPushMatrix();
		if(stats.secondMovePart == 3)
		{
			glTranslatef(-2.5, -1.0, 0.5);
			glutSolidCube(0.5);
		}
		glPopMatrix();
	}
}

void changeSize(int w1, int h1) {

	float ratio;

	h = h1;
	w = w1;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,ratio,0.1,1000);

	// setting the camera now
	glMatrixMode(GL_MODELVIEW);
}
