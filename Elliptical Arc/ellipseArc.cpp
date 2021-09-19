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

void fillEllipse(int cx, int cy, int rx, int ry, int startAngle, int endAngle, int rr, int rg, int rb)
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

            int angle[4] = {0};
            int alpha;
            alpha = (atan2( (y - cy),(x - cx) )*180)/PI;
            angle[0] = alpha;
            angle[1] = 180 - alpha;
            angle[2] = 180 + alpha;
            angle[3] = 360 - alpha;

            if(angle[0] >= startAngle && angle[0] <= endAngle)
                glVertex2i(cx + x, cy + y);

            if(angle[1] >= startAngle && angle[1] <= endAngle)
                glVertex2i(cx - x, cy + y);

            if(angle[2] >= startAngle && angle[2] <= endAngle)
                glVertex2i(cx - x, cy - y);

            if(angle[3] >= startAngle && angle[3] <= endAngle)
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

            int angle[4] = {0};
            int alpha;
            alpha = (atan2( (y - cy),(x - cx) )*180)/PI;
            angle[0] = alpha;
            angle[1] = 180 - alpha;
            angle[2] = 180 + alpha;
            angle[3] = 360 - alpha;

            if(angle[0] >= startAngle && angle[0] <= endAngle)
                glVertex2i(cx + x, cy + y);

            if(angle[1] >= startAngle && angle[1] <= endAngle)
                glVertex2i(cx - x, cy + y);

            if(angle[2] >= startAngle && angle[2] <= endAngle)
                glVertex2i(cx - x, cy - y);

            if(angle[3] >= startAngle && angle[3] <= endAngle)
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

void InvertedfillEllipse(int cx, int cy, int rx, int ry, int startAngle, int endAngle, int rr, int rg, int rb)
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

            int angle[4] = {0};
            int alpha;
            alpha = (atan2( (y - cy),(x - cx) )*180)/PI;
            angle[0] = alpha;
            angle[1] = 180 - alpha;
            angle[2] = 180 + alpha;
            angle[3] = 360 - alpha;

            if((angle[0] <= startAngle || angle[0] >= endAngle))
                glVertex2i(cx + x, cy + y);

            if((angle[1] <= startAngle || angle[1] >= endAngle))
                glVertex2i(cx - x, cy + y);

            if((angle[2] <= startAngle || angle[2] >= endAngle))
                glVertex2i(cx - x, cy - y);

            if((angle[3] <= startAngle || angle[3] >= endAngle))
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

            int angle[4] = {0};
            int alpha;
            alpha = (atan2( (y - cy),(x - cx) )*180)/PI;
            angle[0] = alpha;
            angle[1] = 180 - alpha;
            angle[2] = 180 + alpha;
            angle[3] = 360 - alpha;

            if((angle[0] <= startAngle || angle[0] >= endAngle))
                glVertex2i(cx + x, cy + y);

            if((angle[1] <= startAngle || angle[1] >= endAngle))
                glVertex2i(cx - x, cy + y);

            if((angle[2] <= startAngle || angle[2] >= endAngle))
                glVertex2i(cx - x, cy - y);

            if((angle[3] <= startAngle || angle[3] >= endAngle))
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

void MidpointPartialEllipseAlgo(int cx, int cy, int rx, int ry, int startAngle, int endAngle, int rr, int rg, int rb)
{
    // Angle correction
    if((endAngle - startAngle) >= 360 || (endAngle - startAngle) <= (-360))
    {
        startAngle = 0; 
        endAngle = 360;
        MidpointEllipseAlgo(cx,cy,rx,ry,rr,rg,rb);
    }
    else
    {
        if(startAngle >= 0 && endAngle >= 0)
        {
            if(endAngle >= startAngle)
            {
                fillEllipse(cx,cy,rx,ry,startAngle,endAngle,rr,rg,rb);
            }
            else
            {
                fillEllipse(cx,cy,rx,ry,endAngle,startAngle,rr,rg,rb);
            }
        }
        else if(startAngle >= 0 && endAngle <= 0)
        {
            endAngle = 360 + endAngle;
            InvertedfillEllipse(cx,cy,rx,ry,startAngle,endAngle,rr,rg,rb);
        }
        else if(startAngle <= 0 && endAngle <= 0)
        {
            startAngle = 360 + startAngle;
            endAngle = 360 + endAngle;
            if(endAngle >= startAngle)
            {
                fillEllipse(cx,cy,rx,ry,startAngle,endAngle,rr,rg,rb);
            }
            else
            {
                fillEllipse(cx,cy,rx,ry,endAngle,startAngle,rr,rg,rb);
            }
        }
        else if(startAngle <= 0 && endAngle >= 0)
        {
            startAngle = 360 + startAngle;
            InvertedfillEllipse(cx,cy,rx,ry,endAngle,startAngle,rr,rg,rb);
        }
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
    int startAngle = (rand()%721) - 360;
    int endAngle = (rand()%721) - 360;

    glClear(GL_COLOR_BUFFER_BIT);
    MidpointPartialEllipseAlgo(cx,cy,rx,ry, startAngle, endAngle, rr,rg,rb);

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
	glutCreateWindow("Car");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(drawEllipse);
	glFlush();
	glutMainLoop();
	return 0;
}