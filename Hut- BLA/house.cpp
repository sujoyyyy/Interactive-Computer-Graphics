//#include<Windows.h>
#include<stdio.h>
#include<bits/stdc++.h>
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
double drawline(int x1, int y1, int x2, int y2) {
	int n=0;
	double err=0;
	double m,c;
	if(x2==x1)
		m=INT_MAX;
	else
		m=(double)(y2-y1)/(x2-x1);
	c= y1- m*x1;
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		glBegin(GL_POINTS);
		double tempy= m*x+c;
		err+= (tempy-y)*(tempy-y);
		n++;
		glVertex2i(x, y);
		glEnd();
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			glBegin(GL_POINTS);
			double tempy= m*x+c;
			err+= (tempy-y)*(tempy-y);
			n++;	
			glVertex2i(x, y);
			glEnd();
		}

	} else {
		glBegin(GL_POINTS);
		double tempy= m*x+c;
		err+= (tempy-y)*(tempy-y);
		n++;
		glVertex2i(x, y);
		glEnd();
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			glBegin(GL_POINTS);
			double tempy= m*x+c;
			err+= (tempy-y)*(tempy-y);
			n++;
			glVertex2i(x, y);
			glEnd();
		}
	}
	double tot=err/n;
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
	glutCreateWindow("HUT- BLA");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}