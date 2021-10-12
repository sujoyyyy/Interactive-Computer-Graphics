#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
float k, h, focus;
void drawline(int X1, int Y1, int X2, int Y2)
{
	//This algorithm is the generalised DDA Algorithm
	glColor3f(0.875,0.875,0.875);
	glPointSize(1);
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
void general_parabola(float x0, float y0, float a, float r, float g, float b)
{
	glColor3f(r,g,b);
	glPointSize(3);
	float x = 0;
	float y = 0;
	int dy = 2*x;
	int dx = 4*a;

	while(y<=400 && x<=500)
	{
		glBegin(GL_POINTS);
		glVertex2i(x+x0, y+y0);
		glVertex2i(-x+x0, y+y0);
		glEnd();
		if(dx<dy)
		{
			y=y+1;
			x = sqrt(4*a*(y));
		}
		else
		{
			x=x+1;
			y=(x*x)/(4*a);
		}
		dy = 2*x;
		dx = 4*a;
	}

	glFlush();
}
void parametric_parabola(float x0, float y0, float a, float r, float g, float b)
{
	glColor3f(r, g, b);
	glPointSize(3);
	float t = 0;
	float x, y;
	while (t < 2.1)
	{
		y = y0 + (a * t * t);
		x = x0 + (2 * a * t);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		x = x0 - (2 * a * t);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		t = t + 0.01;
	}

	glFlush();

}
void mid_point_parabola(int x0, int y0, float a, float r, float g, float b)
{
	glColor3f(r, g, b);
	glPointSize(3);
	//region 1
	int  x = 0, y = 0;
	float pk = 1 - 2 * a;
	while (x <= 2 * a)
	{
		glBegin(GL_POINTS);
		glVertex2i(x + x0, y + y0);
		glVertex2i(-x + x0, y + y0);
		glEnd();

		
		if(pk>0)
		{
			pk = pk + 2 * x + 3 - 4 * a;
			x = x + 1;
			y = y + 1;
		}
		else
			{
				pk = pk + 2 * x + 3;
				x = x + 1;
			}
	}
	int i = 0;
	x = 2*a;
	y = a;
	pk = (x + 0.5) * (x + 0.5) - (4 * a * (y + 1));
	while (i < 300)
	{
		i = i + 1;
		glBegin(GL_POINTS);
		glVertex2i(x + x0, y + y0);
		glVertex2i(-x + x0, y + y0);
		glEnd();

		if (pk < 0)
		{
			pk = pk + 2 * x + 2 - 4 * a;
			y = y + 1;
			x = x + 1;
		}
		else
		{
			pk = pk - 4 * a;
			y = y + 1;
		}

	}


	glFlush();
}

void draw_parabola()
{
	srand(time(0));
	focus =rand() % 130;
	h = rand()%100;
	k= rand()%100;
	float r, g, b;
	r = (float)((rand() % 9)) / 8;
	g = (float)((rand() % 9)) / 8;
	b = (float)((rand() % 9)) / 8;
	drawline(0,-600,0,600);
	drawline(-600,0,600,0);
	//general_parabola(h, k,focus, r, g, b);
	//parametric_parabola(h, k, focus, r, g, b);
	mid_point_parabola(h, k, focus, r, g, b);
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
	glutCreateWindow("Parabola");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(draw_parabola);
	glFlush();
	glutMainLoop();
	return 0;
}
