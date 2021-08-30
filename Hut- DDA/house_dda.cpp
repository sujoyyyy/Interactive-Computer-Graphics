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
	dx = (double)((X2 - X1) / length);
	dy = (double)((Y2 - Y1) / length);
	x = (double)X1 + 0.5 * sign(X1);
	y = (double)Y1 + 0.5 * sign(Y1);
	for (int i = 1; i < length; i++)
	{
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		x += dx;
		y += dy;
	}
	glFlush();
}
void fill_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3, int r, int g, int b, int a)
{
	glColor4f(r, g, b, a);
	float i = Y3;
	float j = 0;
	while (i >= Y2)
	{
		drawline(X3 - j, i, X3 + j, i);
		i--;
		j += 0.566;
	}
}
void fill_rectangle(int X1, int Y1, int X2, int Y2, float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
	int i = Y1;
	while (i >=Y2)
	{
		drawline(X1, i, X2, i);
		i--;
	}
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Triangle
	drawline(200, 300, 400, 300);
	drawline(200, 300, 300, 473);
	drawline(300, 473, 400, 300);
	// Big Rectangle
	drawline(200, 300, 400, 300);
	drawline(200, 300, 200, 100);
	drawline(200, 100, 400, 100);
	drawline(400, 100, 400, 300);
	// Door
	drawline(275, 100, 325, 100);
	drawline(325, 100, 325, 200);
	drawline(325, 200, 275, 200);
	drawline(275, 200, 275, 100);
	// Left Window Rectangle
	drawline(220, 220, 255, 220);
	drawline(255, 220, 255, 255);
	drawline(255, 255, 220, 255);
	drawline(220, 255, 220, 220);
	// Right Window Rectangle
	drawline(380, 220, 345, 220);
	drawline(345, 220, 345, 255);
	drawline(345, 255, 380, 255);
	drawline(380, 255, 380, 220);

	//coloring
	fill_triangle(200, 300, 400, 300, 300, 473, 1, 0, 1, 0);
	fill_rectangle(200, 300, 400, 100, 1, 0.4, 0, 0);
	fill_rectangle(275, 200, 325, 100, 1, 1, 1, 1);
	fill_rectangle(220, 255, 255, 220, 1, 1, 1, 1);
	fill_rectangle(345, 255, 380, 220, 1, 1, 1, 1);
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
	glutCreateWindow("HUT- DDA");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}