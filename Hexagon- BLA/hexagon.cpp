//#include<Windows.h>
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
double drawline(int x1, int y1, int x2, int y2)
{
	int n=0;
	double err=0;
	double m,c;
	m=(double)(y2-y1)/(x2-x1);
	c= y1- m*x1;
	cout<<"Slope "<<m<<", Intercept "<<c<<endl;
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
void display(void)
{
	double Error=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	Error+= drawline(398, 112, 198, 112);
	Error+= drawline(198, 112, 98, 285);
	Error+= drawline(98, 285, 198, 459);
	Error+= drawline(198, 459, 398, 459);
	Error+= drawline(398, 459, 498, 285);
	Error+= drawline(498, 285, 398, 112);
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
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham Hexagon");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}