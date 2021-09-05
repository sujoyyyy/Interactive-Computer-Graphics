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
double drawline(int X1, int Y1, int X2, int Y2)
{
	double err=0;
	double m,c;
	m=(double)(Y2-Y1)/(X2-X1);
	c= Y1- m*X1;
	cout<<"Slope "<<m<<", Intercept "<<c<<endl;
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
	glutCreateWindow("DDA Line");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}