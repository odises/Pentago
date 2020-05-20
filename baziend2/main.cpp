#include "windows.h"
#include <math.h>
#include <glut.h>
#include "iostream"
#include "game.h"
#include "render.h"


static status stats;

// Initializing the game board
board gameBoard;

// Initializing the Camera
static camera cam;


// Selection Buffer
#define SelBufferSize 512
static int mainWindow;
// Picking Stuff //
#define RENDER					1
#define SELECT					2
#define BUFSIZE 1024
GLuint selectBuf[BUFSIZE];
GLint hits;
int mode = RENDER;
int cursorX,cursorY;

//---------------
// Picking Stuff
//---------------


void startPicking() {


	GLint viewport[4];
	float ratio;

	glSelectBuffer(BUFSIZE,selectBuf);

	glGetIntegerv(GL_VIEWPORT,viewport);

	glRenderMode(GL_SELECT);

	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(cursorX,viewport[3]-cursorY,5,5,viewport);
	ratio = (viewport[2]+0.0) / viewport[3];
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}


void processHits2 (GLint hits, GLuint buffer[], int sw)
{
	GLint i, j, numberOfNames;
	GLuint names, *ptr, minZ,*ptrNames;

	ptr = (GLuint *) buffer;
	minZ = 0xffffffff;
	for (i = 0; i < hits; i++) {	
		names = *ptr;
		ptr++;
		if (*ptr < minZ) {
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr+2;
		}

		ptr += names+2;
	}
	if (numberOfNames > 0) {

		ptr = ptrNames;

		if(stats.firstMove && !stats.winner)
		{
			stats.firstMovePart = *ptr;
			stats.firstMoveIndex = *(ptr + 1);	
			if(gameBoard.isAccessible(stats.firstMovePart, stats.firstMoveIndex) && !stats.moving)
			{
				gameBoard.setParts(stats.firstMovePart, stats.firstMoveIndex, stats.turn);
				stats.firstMove = false;
				stats.secondMove = true;
			}
		}
		if(stats.secondMove && !stats.moving)
		{
			stats.secondMovePart = *ptr;
		}
	}
}

void stopPicking() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if (hits != 0){
		processHits2(hits,selectBuf,0);
	}
	mode = RENDER;
}
//-----------------
// Rendering
//-----------------

void renderSpacedBitmapString(float x, float y,int spacing ,void *font, char *string) 
{
	char *c;
	int x1=x;

	for (c=string; *c != '\0'; c++) {

		glRasterPos2f(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + 1.5;
	}
}

void renderScene() 
{

	//	glEnable(GL_LIGHTING);

	glutSetWindow(mainWindow);  

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (mode == SELECT) {
		startPicking();
	}
	glLoadIdentity();


	gluLookAt(cam.pos[0],
		cam.pos[1],
		cam.pos[2],   

		cam.lookAt[0],
		cam.lookAt[1],
		cam.lookAt[2],    

		cam.lookUp[0],
		cam.lookUp[1],
		cam.lookUp[2]);
		
	
	if(!stats.endMoving && stats.choosed)
	{
		if(stats.narrow == 1)
		{
			stats.endMoving = gameBoard.cw(stats.secondMovePart);
		}
		else if(stats.narrow == -1)
		{
			stats.endMoving = gameBoard.ccw(stats.secondMovePart);
		}

		stats.moving = true;
	}
	if(stats.endMoving && stats.secondMove)
	{
		stats.moving = false;
		//printf("%d\n", stats.turn);
		stats.firstMove = true;
		stats.secondMove = false;
		stats.endMoving = false;
		stats.choosed = false;
		stats.narrow = 7;
		stats.winner = gameBoard.winner();

		if(stats.turn == 1)
		{
			stats.turn = 2;
		}
		else
		{
			stats.turn = 1;
		}

	}
	if(stats.winner)
	{
		if(gameBoard.winner() == 1)
		{
			glColor3f(0.97,0.19,0.19);
			renderSpacedBitmapString(1.95, 6.2, 0.1, GLUT_BITMAP_HELVETICA_18, "WINNER!");
		}
		else if(gameBoard.winner() == 2)
		{
			glColor3f(0.0,0.63,0.90);
			renderSpacedBitmapString(1.95, 6.2, 0.1, GLUT_BITMAP_HELVETICA_18, "WINNER!");
		}
	}


	//drawing the board of the game
	gameBoard.draw();
	//specify the turn
	denoteTurn(stats);
	//specify the selected slice
	denoteSelectedSlice(stats);

	if (mode == SELECT) 
		stopPicking();
	else
		glutSwapBuffers();
}

//-------------------
// Keyboard and Mouse
//-------------------
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_F2)
	{
		quit();
		exit(0);
	}
	else if(key == GLUT_KEY_LEFT)
	{
		if(stats.secondMove && !stats.choosed)
		{
			stats.choosed = true;
			stats.narrow = -1;
		}
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		if(stats.secondMove && !stats.choosed)
		{
			stats.choosed = true;
			stats.narrow = 1;
		}
	}
}

void mouseStuff(int button, int state, int x, int y) {



	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	cursorX = x;
	cursorY = y;
	mode = SELECT;
}
//---------
// Main
//---------

int main(int argc, char **argv)
{

	stats.winner = false;
	stats.turn = 1;
	stats.firstMove = true;
	stats.moving = false;
	stats.secondMove = false;
	stats.endMoving = false;
	stats.secondMoveIndex = -1;
	stats.secondMovePart = -1;
	stats.choosed = false;
	stats.narrow = 0;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH  | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(w,h);
	mainWindow = glutCreateWindow("Galaxy");

	//glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(SpecialKeys);

	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutMouseFunc(mouseStuff);
	glutIdleFunc(renderScene);


	initScene(argc,argv);
	init(&cam);



	glutMainLoop();
	return(0);
}
