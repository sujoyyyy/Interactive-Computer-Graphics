#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int x;
int y;
int n = 4;
// int x_cordinates[4] = {-300,300,300,-300};
// int y_cordinates[4] = {-200,-200,200,200};
int x_cordinates[4] = {-300,300,300,-300};
int y_cordinates[4] = {200,200,-200,-200};
void point_position();

void init(void)
{
	glViewport(0, 0, 600, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-600.0, 600.0, -480.0, 480.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	srand(time(0));
	int i;
	x = rand() % 400;
	y = rand() % 200;
	printf(" (%d,%d)", x, y);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Point Test");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(point_position);
	glFlush();
	glutMainLoop();
	return 0;
}


void point_position()
{
	glColor3f(0, 0, 1);
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0;i < n;i++)
	{
		glVertex2f(x_cordinates[i], y_cordinates[i]);
	}
	glEnd();
	int p[20];
	for (i = 0;i < n-1;i++)
	{
		p[i] = ((x_cordinates[i + 1] - x_cordinates[i]) * (y - y_cordinates[i])) - ((y_cordinates[i + 1] - y_cordinates[i]) * (x - x_cordinates[i]));
	}
	p[i]= ((x_cordinates[0] - x_cordinates[n-1]) * (y - y_cordinates[n-1])) - ((y_cordinates[0] - y_cordinates[n-1]) * (x - x_cordinates[n-1]));
	
	int flag = 0;
	int pos = 1;
	for (i = 0;i < n;i++)
	{
		if (i == 0)
		{
			if (p[0] < 0)
				flag = -1;
			else
				flag = +1;
		}
		else
		{
			if (flag == -1 && p[i] < 0)
				flag = -1;
			else if (flag == 1 && p[i] > 0)
				flag = 1;
			else
			{
				pos = 0;
				break;
			}
		}
	}
	glPointSize(4);
	if (pos == 1)
	{
		glColor3f(0, 1, 0);
		printf("Point lies inside the window.\n");
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x, y + 1);
		glVertex2f(x - 1, y);
		glVertex2f(x, y - 1);
		glEnd();
	}
	else
	{
		glColor3f(1, 0, 0);
		printf("Point lies outside the window.\n");
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x, y + 1);
		glVertex2f(x - 1, y);
		glVertex2f(x, y - 1);
		glEnd();
	}

	glFlush();
}