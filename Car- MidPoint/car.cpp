//#include<Windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;
int pntX1, pntY1;

void plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void midPointCircleAlgo(int xc, int yc, int r)
{
	//2nd octant
	int x = 0;
	int y = r;
	float decision = 5/4 - r;
	plot(x+xc, y+yc);

	while (y > x)
	{
		if (decision < 0)
		{
			x++; 
			decision += 2*x+1;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+1;
		}
		plot(x+xc, y+yc);
		plot(x+xc, -y+yc);
		plot(-x+xc, y+yc);
		plot(-x+xc, -y+yc);
		plot(y+xc, x+yc);
		plot(-y+xc, x+yc);
		plot(y+xc, -x+yc);
		plot(-y+xc, -x+yc);
	}
	glFlush();
}

double drawline(int x1, int y1, int x2, int y2)
{
	int n=0;
	double err=0;
	double m,c;
	m=(double)(y2-y1)/(x2-x1);
	c= y1- m*x1;
	//cout<<"Slope "<<m<<", Intercept "<<c<<endl;
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

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//Car Body
	//Rectangle
	drawline(700,100,-500,100);
	drawline(-500,100,-500,500);
	drawline(-500,500,700,500);
	drawline(700,500,700,100);
	//Trapezium
	drawline(-200,500,0,800);
	drawline(0,800,500,800);
	drawline(500,800,700,500);
	drawline(166,529,-143,529);
	//Trapezium Body
	drawline(-143,529,0,750);
	drawline(0,750,166,750);
	drawline(166,750,166,529);
	drawline(166,750,489,750);
	drawline(489,750,633,529);
	drawline(633,529,166,529);
	//Wheel Left
	midPointCircleAlgo(-200,100,100);
	//Wheel Right
	midPointCircleAlgo(400,100,100);

	
}
void init(void)
{
	glViewport(0, 0, 1600, 1000);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1600.0, 1600.0, -1000.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1600,1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Car");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}