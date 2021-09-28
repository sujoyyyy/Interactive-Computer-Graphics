//#include<Windows.h>
#include <time.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;

int sign(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}
void drawline(int X1, int Y1, int X2, int Y2)
{
	double x, y, dx, dy, length;
	int i;
	dx = (double)abs(X2 - X1);
	dy = (double)abs(Y2 - Y1);
	if (dx >= dy)
		length = dx;
	else
		length = dy;
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
		glFlush();
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
	glFlush();
}
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	drawline(398, 112, 198, 112);
	glEnd();
}
void init(void)
{
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DDA Hexagon");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}