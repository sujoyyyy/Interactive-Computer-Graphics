#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <time.h>
using namespace std;
#define PI 3.14159265359

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
            glVertex2f(cx + rx*(1/cos(theta)),cy + ry*(sin(theta)/cos(theta)));
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
            y = y - 1;
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
    int cx = 0;
    int cy = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    
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
