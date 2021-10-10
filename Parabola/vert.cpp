#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float h,k,focus;

void general_parabola(float x0, float y0, float a, float r, float g, float b)
{
	glColor3f(r,g,b);
	glPointSize(3);
	float x = 0;
	float y = 0;
	int dy = 4*a;
	int dx = 2*y;
	while(x<=400)
	{
		glBegin(GL_POINTS);
		glVertex2i(x+x0, y+y0);
		glVertex2i(x+x0,-y+y0);
		glEnd();
		if(dx>dy)
		{
			x=x+1;
			y = sqrt(4*a*(x));
		}
		else
		{
			y=y+1;
			x=(y*y)/(4*a);
		}
		dy = 2*a;
		dx = 2*y;
	}
}

void parametric_parabola(float x0, float y0, float a, float r, float g, float b)
{
	glColor3f(r, g, b);
	glPointSize(3);
	float t = 0;
	float x, y;
	while (t < 2.2)
	{
		x = x0 + (a * t * t);
		y = y0 + (2 * a * t);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		y = y0 - (2 * a * t);
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
	while (y <= 2 * a)
	{
		glBegin(GL_POINTS);
		glVertex2i(x+x0, y+y0);
		glVertex2i(x+x0, -y+y0);
		glEnd();

		if (pk < 0)
		{
			pk = pk + 2 * y + 3;
			y = y + 1;
		}
		else 
		{
			pk = pk + 2 * y + 3 - 4*a;
			x = x + 1;
			y = y + 1;
		}
	}
	int i=0;
	x = a;
	y = 2*a;
	pk = (y + 0.5) * (y + 0.5) - (4 * a * (x + 1));
	while (i < 100)
	{
		i = i + 1;
		glBegin(GL_POINTS);
		glVertex2i(x + x0, y + y0);
		glVertex2i(x + x0, -y + y0);
		glEnd();

		if (pk < 0)
		{
			pk = pk + 2 * y + 2 - 4*a;
			y = y + 1;
			x = x + 1;
		}
		else
		{
			pk = pk  - 4 * a;
			x = x + 1;
		}

	}


	glFlush();
}


void draw_parabola()
{
	srand(time(0));
	focus =rand() % 230;
	h = rand()%100;
	k= rand()%100;
	float r, g, b;
	r = (float)((rand() % 9)) / 8;
	g = (float)((rand() % 9)) / 8;
	b = (float)((rand() % 9)) / 8;
	general_parabola(h, k,focus, r, g, b);
	parametric_parabola(h, k, focus, r, g, b);
	//mid_point_parabola(h, k, focus, r, g, b);
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
