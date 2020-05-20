#include "windows.h"
#include "glut.h"
#include "game.h"
#include "iostream"


slice::slice()
{
	for(int i = 0; i < 9; i++)
	{
		elements[i] = -1;
	}
	y_transfer = 0.0f;
	z_rotate = 0.0f;
	angel = 0.0f;
	rotateStatus = 0;
	transferStatus = 0;
}
void slice::draw()
{
	for(int i = 0; i < 3; i++)
	{
		
		for(int j = 0; j < 3; j++)
		{
			glPushMatrix();
				glTranslatef(0.0, 0.0,-3.5);
				glPushMatrix();
					glTranslatef(1.5*j, 0.0, i*1.5);
						glPushName(i*3 + j);
						if(elements[i*3 + j] == -1)
						{
							glColor3f(0.0f, 1.0f, 0.0f); // white
						}
						else if(elements[i*3 + j] == 1)
						{
							glColor3f(1.0f, 0.0f, 0.0f); // red
						}
						else if(elements[i*3 + j] == 2)
						{
							glColor3f(0.0f, 0.0f, 1.0f); // blue
						}
					glutSolidSphere(0.5, 30.0, 30.0);
					glPopName();
				glPopMatrix();
			glPopMatrix();
		}
	}
}

bool slice::rotateCw(GLfloat upperbound, GLfloat increament)
{
	if(transferStatus == 0 && rotateStatus == 0)
	{
		transferStatus = 1;
		cw++;
		//printf("%d\n", cw);
	}
	if(transferStatus == 1)
	{
		y_transfer += increament;
		if(y_transfer >= upperbound)
		{
			//y_transfer = upperbound;
			transferStatus = 0;
			rotateStatus = 1;
		}
	}
	if(transferStatus == 0 && rotateStatus == 1)
	{
		angel -= increament * 10;
		if((angel - z_rotate) <= -90.0)
		{
			transferStatus = -1;
			rotateStatus = 0;
			z_rotate -= 90.0;
		}
	}
	if(transferStatus == -1)
	{
		y_transfer -= increament;
		if(y_transfer <= 0.0)
		{
			//y_transfer = upperbound;
			transferStatus = 0;
			rotateStatus = 0;
			return true;
		}
	}
	return false;
}

bool slice::rotateCcw(GLfloat upperbound, GLfloat increament)
{
	if(transferStatus == 0 && rotateStatus == 0)
	{
		transferStatus = 1;
		cw--;
	}

	if(transferStatus == 1)
	{
		y_transfer += increament;
		if(y_transfer >= upperbound)
		{
			//y_transfer = upperbound;
			transferStatus = 0;
			rotateStatus = -1;
		}
	}
	if(transferStatus == 0 && rotateStatus == -1)
	{
		angel += increament * 10;
		if((angel - z_rotate) >= 90.0)
		{
			transferStatus = -1;
			rotateStatus = 0;
			z_rotate += 90.0;
		}

	}
	if(transferStatus == -1)
	{
		y_transfer -= increament;
		if(y_transfer <= 0.0)
		{
			//y_transfer = upperbound;
			transferStatus = 0;
			rotateStatus = 0;
			return true;
		}
	}
	return false;
}

GLfloat slice::yTransfer()
{
	return y_transfer;
}

GLfloat slice::zRotate()
{
	return angel;
}

int slice::getValues(int index)
{
	int cw_temp = cw % 4;
	if(cw_temp < 0)
	{
		cw_temp = 4 + cw_temp;
	}


	int temp_values[9];
	int temp_rotated_Values[9];

	for(int i = 0; i < 9; i++)
	{
		temp_values[i] = elements[i];
	}
	
	for(int i = 0; i < 9; i++)
	{
		temp_rotated_Values[i] = temp_values[i];
	}

	for(int i = 0; i < cw_temp; i++)
	{
		temp_rotated_Values[2] = temp_values[0];
		temp_rotated_Values[5] = temp_values[1];
		temp_rotated_Values[8] = temp_values[2];
		temp_rotated_Values[1] = temp_values[3];
		temp_rotated_Values[4] = temp_values[4];
		temp_rotated_Values[7] = temp_values[5];
		temp_rotated_Values[0] = temp_values[6];
		temp_rotated_Values[3] = temp_values[7];
		temp_rotated_Values[6] = temp_values[8];

		for(int i = 0; i < 9; i++)
		{
			temp_values[i] = temp_rotated_Values[i];
		}
	}

	return temp_rotated_Values[index];
}

void slice::setValues(int index, int value)
{
	elements[index] = value;
}

bool slice::isFilled(int index)
{
	if(elements[index] != -1)
		return true;
	else 
		return false;
}

bool slice::isFullyFilled()
{
	int count = 0;
	for(int i = 0; i < 9; i++)
	{
		if(elements[i] == -1)
		{
			count++;
		}
	}
	if(count > 0)
		return false;
	else 
		return true;
}

board::board()
{
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			s[i][j] = 0;
		}
	}
}

void board::setParts(int part, int index, int value)
{
	switch(part)
	{
	case 1:
		p1.setValues(index, value);
		break;
	case 2:
		p2.setValues(index, value);
		break;
	case 3:
		p3.setValues(index, value);
		break;
	case 4:
		p4.setValues(index, value);
		break;
	}
}
void board::load()
{
	s[0][0] = p1.getValues(0);
	s[0][1] = p1.getValues(3);
	s[0][2] = p1.getValues(6);
	s[0][3] = p3.getValues(0);
	s[0][4] = p3.getValues(3);
	s[0][5] = p3.getValues(6);

	s[1][0] = p1.getValues(1);
	s[1][1] = p1.getValues(4);
	s[1][2] = p1.getValues(7);
	s[1][3] = p3.getValues(1);
	s[1][4] = p3.getValues(4);
	s[1][5] = p3.getValues(7);

	s[2][0] = p1.getValues(2);
	s[2][1] = p1.getValues(5);
	s[2][2] = p1.getValues(8);
	s[2][3] = p3.getValues(2);
	s[2][4] = p3.getValues(5);
	s[2][5] = p3.getValues(8);

	s[3][0] = p2.getValues(0);
	s[3][1] = p2.getValues(3);
	s[3][2] = p2.getValues(6);
	s[3][3] = p4.getValues(0);
	s[3][4] = p4.getValues(3);
	s[3][5] = p4.getValues(6);

	s[4][0] = p2.getValues(1);
	s[4][1] = p2.getValues(4);
	s[4][2] = p2.getValues(7);
	s[4][3] = p4.getValues(1);
	s[4][4] = p4.getValues(4);
	s[4][5] = p4.getValues(7);

	s[5][0] = p2.getValues(2);
	s[5][1] = p2.getValues(5);
	s[5][2] = p2.getValues(8);
	s[5][3] = p4.getValues(2);
	s[5][4] = p4.getValues(5);
	s[5][5] = p4.getValues(8);

	s[6][0] = p1.getValues(0);
	s[6][1] = p1.getValues(1);
	s[6][2] = p1.getValues(2);
	s[6][3] = p2.getValues(0);
	s[6][4] = p2.getValues(1);
	s[6][5] = p2.getValues(2);

	s[7][0] = p1.getValues(3);
	s[7][1] = p1.getValues(4);
	s[7][2] = p1.getValues(5);
	s[7][3] = p2.getValues(3);
	s[7][4] = p2.getValues(4);
	s[7][5] = p2.getValues(5);

	s[8][0] = p1.getValues(6);
	s[8][1] = p1.getValues(7);
	s[8][2] = p1.getValues(8);
	s[8][3] = p2.getValues(6);
	s[8][4] = p2.getValues(7);
	s[8][5] = p2.getValues(8);

	s[9][0] = p3.getValues(0);
	s[9][1] = p3.getValues(1);
	s[9][2] = p3.getValues(2);
	s[9][3] = p4.getValues(0);
	s[9][4] = p4.getValues(1);
	s[9][5] = p4.getValues(2);

	s[10][0] = p3.getValues(3);
	s[10][1] = p3.getValues(4);
	s[10][2] = p3.getValues(5);
	s[10][3] = p4.getValues(3);
	s[10][4] = p4.getValues(4);
	s[10][5] = p4.getValues(5);

	s[11][0] = p3.getValues(6);
	s[11][1] = p3.getValues(7);
	s[11][2] = p3.getValues(8);
	s[11][3] = p4.getValues(6);
	s[11][4] = p4.getValues(7);
	s[11][5] = p4.getValues(8);

	s[12][0] = p2.getValues(1);
	s[12][1] = p2.getValues(3);
	s[12][2] = p1.getValues(8);
	s[12][3] = p3.getValues(1);
	s[12][4] = p3.getValues(3);
	s[12][5] = 0;

	s[13][0] = p2.getValues(2);
	s[13][1] = p2.getValues(4);
	s[13][2] = p2.getValues(6);
	s[13][3] = p3.getValues(2);
	s[13][4] = p3.getValues(4);
	s[13][5] = p3.getValues(6);

	s[14][0] = p2.getValues(5);
	s[14][1] = p2.getValues(7);
	s[14][2] = p4.getValues(0);
	s[14][3] = p3.getValues(5);
	s[14][4] = p3.getValues(7);
	s[14][5] = 0;

	s[15][0] = p1.getValues(1);
	s[15][1] = p1.getValues(5);
	s[15][2] = p2.getValues(6);
	s[15][3] = p4.getValues(1);
	s[15][4] = p4.getValues(5);
	s[15][5] = 0;

	s[16][0] = p1.getValues(0);
	s[16][1] = p1.getValues(4);
	s[16][2] = p1.getValues(8);
	s[16][3] = p4.getValues(0);
	s[16][4] = p4.getValues(4);
	s[16][5] = p4.getValues(8);

	s[17][0] = p1.getValues(3);
	s[17][1] = p1.getValues(7);
	s[17][2] = p3.getValues(2);
	s[17][3] = p4.getValues(3);
	s[17][4] = p4.getValues(7);
	s[17][5] = 0;
}

int board::max_series(int x[], int number)
{
	int result = 0;

	int b[10] = {};
	int i = 0;
	int counter = 0;
	for(int j = 0; j < 6; j++)
	{
		if(x[j] == number)
		{
			counter++;
		}
		else
		{
			if(counter != 0)
			{
				b[i] = counter;
				counter = 0;
				i++;
			}
		}
	}
	if(counter != 0)
	{
		b[i] = counter;
	}

	bool swapped = true;
	int j = 0;
	int tmp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < 10 - j; i++) {
			if (b[i] < b[i + 1]) {
				tmp = b[i];
				b[i] = b[i + 1];
				b[i + 1] = tmp;
				swapped = true;
			}
		}
	}
	result = b[0];
	return result;
}

bool board::isFullyFilled()
{
	bool result = p1.isFullyFilled() && p2.isFullyFilled() && p3.isFullyFilled() && p4.isFullyFilled();

	return result;
}

int board::winner()
{
	load();
	int result = 0;
	for(int i = 0; i < 18; i++)
	{
		if(max_series(s[i], 1) >= 5)
		{
			result = 1;
			break;
		}
	}
	for(int i = 0; i < 18; i++)
	{
		if(max_series(s[i], 2) >= 5)
		{
			result = 2;
			break;
		}
	}

	return result;
}

void board::draw()
{
	/*for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			printf("  %d  ",p4.getValues(i*3 + j));
		}
		printf("\n");
	}*/
	//p1
	glPushMatrix();
	glTranslatef(0.0, p1.yTransfer(), 0.0);
		glPushMatrix();
			glTranslatef(1.5, 0.0, -7.5);
			glRotatef(p1.zRotate(), 0.0, 1.0, 0.0);
			glTranslatef(-1.5, 0.0, 7.5);
			glPushMatrix();
				glTranslatef(0.0, 0.0, -5.5);
				glPushName(1);

					p1.draw();

				glPopName();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//p2
	glPushMatrix();
	glTranslatef(0.0, p2.yTransfer(), 0.0);
		glPushMatrix();
			glTranslatef(7.0, 0.0, -7.5);
			glRotatef(p2.zRotate(), 0.0, 1.0, 0.0);
			glTranslatef(-7.0, 0.0, 7.5);
			glPushMatrix();
				glTranslatef(5.5, 0.0, -5.5);
				glPushName(2);
					p2.draw();
				glPopName();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//p3
	glPushMatrix();
	glTranslatef(0.0, p3.yTransfer(), 0.0);
		glPushMatrix();
			glTranslatef(1.5, 0.0, -2.0);
			glRotatef(p3.zRotate(), 0.0, 1.0, 0.0);
			glTranslatef(-1.5, 0.0, 2.0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.0);
				glPushName(3);
					p3.draw();
				glPopName();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//p4
	glPushMatrix();
	glTranslatef(0.0, p4.yTransfer(), 0.0);
		glPushMatrix();
			glTranslatef(7.0, 0.0, -2.0);
			glRotatef(p4.zRotate(), 0.0, 1.0, 0.0);
			glTranslatef(-7.0, 0.0, 2.0);
			glPushMatrix();
				glTranslatef(5.5, 0.0, 0.0);
				glPushName(4);
					p4.draw();
				glPopName();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0.7, 0.7, 0.5);
		glBegin(GL_QUADS);
			glVertex3f(20.0,-2.0,5.0);
			glVertex3f(20.0,-2.0,-20.0);
			glVertex3f(-20.0,-2.0,-20.0);
			glVertex3f(-20.0,-2.0,5.0);
		glEnd();

	glPopMatrix();
}
bool board::isAccessible(int part, int index)
{
	bool result = false;
	switch(part)
	{
	case 1:
		result = !p1.isFilled(index);
		break;
	case 2:
		result = !p2.isFilled(index);
		break;
	case 3:
		result = !p3.isFilled(index);
		break;
	case 4:
		result = !p4.isFilled(index);
		break;
	}

	return result;
}

bool board::ccw(int part)
{
	switch(part)
	{
	case 1:
		return p1.rotateCcw(1.0, 0.2);
		//break;
	case 2:
		return p2.rotateCcw(1.0, 0.2);
	case 3:
		return p3.rotateCcw(1.0, 0.2);
	case 4:
		return p4.rotateCcw(1.0, 0.2);
	}
}

bool board::cw(int part)
{
	switch(part)
	{
	case 1:
		return p1.rotateCw(1.0, 0.2);
		//break;
	case 2:
		return p2.rotateCw(1.0, 0.2);
	case 3:
		return p3.rotateCw(1.0, 0.2);
	case 4:
		return p4.rotateCw(1.0, 0.2);
	}
}
//
