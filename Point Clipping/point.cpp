#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawline(int X1, int Y1, int X2, int Y2)
{
	//This algorithm is the generalised DDA Algorithm
	glColor3f(1,1,1);
	double x, y, dx, dy, length;
	int i;
	dx = (double)abs(X2 - X1);
	dy = (double)abs(Y2 - Y1);
	if (dx >= dy) //This condition is true implies that the slope of the line m<=1
		length = dx;
	else
		length = dy;

	//Please note that the value of length will be dx if m<=1 and dy if m>1
	dx = (X2 - X1) / length;
	dy = (Y2 - Y1) / length;
	x = (double)X1;
	y = (double)Y1; 
	i = 1;
	while (i <= length)
	{
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
	glEnd();
}

void clip_points()
{
	srand(time(0));
	int xmin= -300;
	int xmax=300;
	int ymin=-200;
	int ymax=200;
	drawline(-300,-200,300,-200);
	drawline(-300,200,300,200);
	drawline(-300,-200,-300,200);
	drawline(300,-200,300,200);
	glColor3f(1,0,0);
	int n=1000;
	int x,y;
	for (int i = 0; i < n; i++)
	{
	
		x=rand()%900-455;
		y=rand()%780-410;
		if(x<=xmax && x>=xmin && y<=ymax && y>=ymin)
		{
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
	}
	

	glFlush();
}


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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points Clipping");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(clip_points);
	glFlush();
	glutMainLoop();
	return 0;
}
