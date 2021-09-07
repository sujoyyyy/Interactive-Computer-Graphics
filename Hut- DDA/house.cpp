#include<bits/stdc++.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
using namespace std;
int xx1, xx2, yy1, yy2;
int sign(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}
double drawline(int X1, int Y1, int X2, int Y2)
{
	double err=0;
	double m,c;
	m=(double)(Y2-Y1)/(X2-X1);
	c= Y1- m*X1;
	//cout<<"Slope "<<m<<", Intercept "<<c<<endl;
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
		double tempy= m*round(x)+c;
		err+= (tempy-round(y))*(tempy-round(y));
		glVertex2i(x, y);
		glEnd();
		glFlush();
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
	double tot=err/length;
	glFlush();
	return tot;
}
void fill_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3, int r, int g, int b, int a)
{
	glColor4f(r, g, b, a);
	while (X1 <= X2)
	{
		drawline(X3, Y3, X1, Y1);
		X1++;
	}
}
void fill_rectangle(int X1, int Y1, int X2, int Y2, float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
	while (Y1 >=Y2)
	{
		drawline(X1, Y1, X2, Y1);
		Y1--;
	}
}
void display(void)
{
	clock_t start = clock();
	double Error=0;
	glClear(GL_COLOR_BUFFER_BIT);
	// Triangle
	Error+= drawline(200, 300, 400, 300);
	Error+= drawline(200, 300, 300, 473);
	Error+= drawline(300, 473, 400, 300);
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
	clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
	cout<<"Time taken-	"<<elapsed<<endl;
	cout<<"Total MSE-  "<<Error<<endl;
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