//#include <Windows.h>
#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <time.h>
using namespace std;
#define PI 3.141592

void drawArc(int cx, int cy, int r, int startAngle, int endAngle)
{   
    int d = 1 - r;
    int x = 0; int y = r;
    int ycal = floor(y/sqrt(2)) - 1;

    while(y != ycal)
    {
        	glBegin(GL_POINTS);
            glColor3ub( 100,100,112);
            int alpha;
            alpha = 90 - (atan( (float)y/x )*180)/PI;

            if(90 - alpha >= startAngle && 90 - alpha <= endAngle)
                glVertex2i(cx + x, cy + y);

            if(alpha >= startAngle && alpha <= endAngle)
                glVertex2i(cx + y, cy + x);

            if(360 - alpha >= startAngle && 360 - alpha <= endAngle)
                glVertex2i(cx + y, cy - x);

            if(270 + alpha >= startAngle && 270 + alpha <= endAngle)
                glVertex2i(cx + x, cy - y);
                
            if(270 - alpha >= startAngle && 270 - alpha <= endAngle)
                glVertex2i(cx - x, cy - y);
                
            if(180 + alpha >= startAngle && 180 + alpha <= endAngle)
                glVertex2i(cx - y, cy - x);

            if(180 - alpha >= startAngle && 180 - alpha <= endAngle)
                glVertex2i(cx - y, cy + x);
                
            if(90 + alpha >= startAngle && 90 + alpha <= endAngle)
                glVertex2i(cx - x, cy + y);
                
        glEnd();

        x = x + 1;
        if(d < 0)
        {
            d += (2*x) + 3;
            y = y;
        }
        else
        {   
            d += (2*(x-y)) + 5;
            y = y - 1;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	int alpha,beta;
	alpha =90;
	beta=180;
    drawArc(0,0,800, alpha, beta);
    glFlush();
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
	glutCreateWindow("Arc");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}