#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <time.h>

using namespace std;

#define PI 3.14159265359

void MidpointEllipseAlgo(int cx, int cy, int rx, int ry, int rr, int rg, int rb)
{
    // decision parameter for region 1
    float d1 = (ry*ry) - (rx*rx*ry) + (0.25*rx*rx);
    int x = 0;
    int y = ry;
    int dy = 2 * rx * rx * y;
    int dx = 2 * ry * ry * x;

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

        x = x + 1;
        if(d1 < 0)
        {
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry*ry);
            y = y;
        }
        else
        {   
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
            y = y - 1;
        }
    }
    
    // decision parameter for region 2
    float d2 = ((ry * ry) * ((x + 0.5)*(x + 0.5))) + ((rx * rx) * ((y-1)*(y-1))) - (rx * rx * ry * ry);
    
    //region 2
    while(y >= 0)
    {
        glBegin(GL_POINTS);
            glColor3ub( rr, rg, rb);
            glVertex2i(cx + x, cy + y);
            glVertex2i(cx - x, cy + y);
            glVertex2i(cx - x, cy - y);
            glVertex2i(cx + x, cy - y);
        glEnd();

        y = y - 1;
        if(d2 > 0)
        {
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            x = x + 1;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void ParametricEllipseAlgo(int cx, int cy, int rx, int ry, int rr, int rg, int rb)
{
    GLfloat theta;
    glBegin(GL_POINTS);
    glColor3ub(rr, rg, rb);
        for(int i = 0; i <= 360; i++)
        {
            theta = i*PI/180;
            glVertex2f(cx + rx*cos(theta),cy + ry*sin(theta));
        }
    glEnd();
}

void GeneralEllipseAlgo(int cx, int cy, int rx, int ry, int rr, int rg, int rb)
{
    int x = 0;
    int y = ry;
    int dy = 2 * rx * rx * y;
    int dx = 2 * ry * ry * x;

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
            y = round(sqrt(((rx*rx*ry*ry) - (ry*ry*(x)*(x)))/(rx*rx)));
        }
        else
        {
            y = y - 1;
            x = round(sqrt(((rx*rx*ry*ry) - (rx*rx*(y)*(y)))/(ry*ry)));
        }
        dy = 2 * rx * rx * y;
        dx = 2 * ry * ry * x;
    }
}

void drawEllipse()
{
    srand(time(0));
    int rr = rand()%256;
    int rg = rand()%256;
    int rb = rand()%256;
    int rx = (rand()%300);
    int ry = (rand()%300);
    int cx = (rand()%100);
    int cy = (rand()%100);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // midpoint
    //MidpointEllipseAlgo(cx,cy,rx,ry,rr,rg,rb);

    // using parametric form
    //ParametricEllipseAlgo(cx,cy,rx,ry,rr,rg,rb);

    // using general equation
    GeneralEllipseAlgo(cx,cy,rx,ry,rr,rg,rb);

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
	glutCreateWindow("Ellipse");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(drawEllipse);
	glFlush();
	glutMainLoop();
	return 0;
}
