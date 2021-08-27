#include<Windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int xx1, xx2, yy1, yy2;
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
	x = (double)X1 + 0.5 * sign(X1);
	y = (double)Y1 + 0.5 * sign(Y1);
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
	glColor3f(1.0, 0.0, 0.0);
	drawline(350, 163, 250, 163);
	drawline(250, 163, 200, 250);
	drawline(200, 250, 250, 337);
	drawline(250, 337, 350, 337);
	drawline(350, 337, 400, 250);
	drawline(400, 250, 350, 163);
	/*
	drawline(100, 100, 220, 100);
	drawline(40, 200, 100, 100);
	drawline(40, 200, 100, 300);
	drawline(100, 300, 220, 300);
	drawline(220, 300, 280, 200);
	drawline(280, 200, 220, 100);
	*/
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
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DDA Line");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}