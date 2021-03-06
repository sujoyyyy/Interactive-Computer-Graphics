#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <time.h>
using namespace std;
#define PI 3.14159265359
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
void MidpointAlgo(int cx, int cy, int rx, int ry, int rr, int rg, int rb)
{
    // decision parameter for region 1
    float d1 = -(rx*rx) + (ry*ry*rx) + (0.25*ry*ry);
    int x = rx;
    int y = 0;
    int dy = 2 * ry * ry * x;
    int dx = 2 * rx * rx * y;
    glPointSize(3);
    // region 1
    while(dx <= dy)
    {
        glBegin(GL_POINTS);
            glColor3ub( rr, rg, rb);
            glVertex2i(cx + x, cy + y);
            glVertex2i(cx - x, cy + y);
            glVertex2i(cx - x, cy - y);
            glVertex2i(cx + x, cy - y);
        glEnd();

        y = y + 1;
        if(d1 < 0)
        {
            x = x+1;
            d1 = d1 - 2*y*rx*rx - (rx*rx) + 2*x*ry*ry;
        }
        else
        {   
            d1 = d1 - 2*y*rx*rx - rx*rx;
        }
        dy = 2 * ry * ry * x; dx = 2 * rx * rx * y;
    }
    
    // decision parameter for region 2
    float d2 = ((ry * ry) * ((x + 0.5)*(x + 0.5))) - ((rx * rx) * ((y-1)*(y-1))) - (rx * rx * ry * ry);
    
    //region 2
    while(y <=100)
    {
        glBegin(GL_POINTS);
            glColor3ub( rr, rg, rb);
            glVertex2i(cx + x, cy + y);
            glVertex2i(cx - x, cy + y);
            glVertex2i(cx - x, cy - y);
            glVertex2i(cx + x, cy - y);
        glEnd();

        x = x + 1;
        if(d2 > 0)
        {
            d2 = d2 + 2*x*(ry * ry) + ry*ry;
        }
        else
        {
            y = y + 1;
            d2 = d2 + 2*x*(ry * ry) + ry*ry - 2*y*(rx * rx);
        }
    }
}

void ParametricAlgo(int cx, int cy, int rx, int ry, int rr, int rg, int rb)
{
    glPointSize(3);
    GLfloat theta;
    glBegin(GL_POINTS);
    glColor3ub(rr, rg, rb);
        for(int i = 0; i <= 360; i++)
        {
            theta = i*PI/180;
            glVertex2i(cx + rx*(1/cos(theta)),cy + ry*(sin(theta)/cos(theta)));
        }
    glEnd();
}

void GeneralAlgo(int cx, int cy, int rx, int ry, int rr, int rg, int rb)
{
    int x = rx;
    int y = 0;
    int dy = 2 * ry * ry * x;
    int dx = 2 * rx * rx * y;
    glPointSize(3);

    while(y >= 0)
    {
        glBegin(GL_POINTS);
        glColor3ub( rr, rg, rb);
        glVertex2i(cx + x, cy + y);
        glVertex2i(cx - x, cy + y);
        glVertex2i(cx - x, cy - y);
        glVertex2i(cx + x, cy - y);
        glEnd();

        if(dx < dy)
        {
            x = x + 1;
            y = round(sqrt((-(rx*rx*ry*ry) + (ry*ry*(x)*(x)))/(rx*rx)));
        }
        else
        {
            y = y + 1;
            x = round(sqrt((-(rx*rx*ry*ry) + (rx*rx*(y)*(y)))/(ry*ry)));
        }
        dy = 2 * ry * ry * x;
        dx = 2 * rx * rx * y;
    }
}

void drawEllipse()
{
    srand(time(0));
    int rr = rand()%256;
    int rg = rand()%256;
    int rb = rand()%256;
    int rx = rand()%150+200;
    int ry = rand()%150+200;
    int cx = rand()%60;
    int cy = rand()%40;
    glClear(GL_COLOR_BUFFER_BIT);
    drawline(0,-600,0,600);
	drawline(-600,0,600,0);
    // midpoint
    MidpointAlgo(cx,cy,rx,ry,rr,rg,rb);

    // using parametric form
    //ParametricAlgo(cx,cy,rx,ry,rr,rg,rb);

    // using general equation
    //GeneralAlgo(cx,cy,rx,ry,rr,rg,rb);

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
	glutCreateWindow("Hyperbola");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(drawEllipse);
	glFlush();
	glutMainLoop();
	return 0;
}
