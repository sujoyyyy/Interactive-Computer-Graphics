#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawline(int X1, int Y1, int X2, int Y2)
{
	//This algorithm is the generalised DDA Algorithm
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

void clip_points()
{
	srand(time(0));
	int xmin= -300;
	int xmax= 300;
	int ymin= -200;
	int ymax= 200;
    glColor3f(1,1,1);
	drawline(-300,-200,300,-200);
	drawline(-300,200,300,200);
	drawline(-300,-200,-300,200);
	drawline(300,-200,300,200);
	glColor3f(0,1,0);
	int n=10;int i;
	for (int j = 0; j < n; j++)
	{
        int x1,y1,x2,y2,xx1,xx2,yy1,yy2,dx,dy;
        float t1,t2,p[4],q[4],temp;
        x1=rand()%900-455;
		y1=rand()%780-410;
        x2=rand()%900-455;
		y2=rand()%780-410;
        dx=x2-x1;
        dy=y2-y1;
        p[0]=-dx;
        p[1]=dx;
        p[2]=-dy;
        p[3]=dy;
        q[0]=x1-xmin;
        q[1]=xmax-x1;
        q[2]=y1-ymin;
        q[3]=ymax-y1;
        for(i=0;i<4;i++)
        {
            if(p[i]==0)
            {
                if(q[i]>=0)
                {
                    if(i<2)
                    {
                        if(y1<ymin)
                        {
                            y1=ymin;
                        }
                        if(y2>ymax)
                        {
                            y2=ymax;
                        }
                        drawline(x1,y1,x2,y2);
                    }
                    if(i>1)
                    {
                        if(x1<xmin)
                        {
                            x1=xmin;
                        }
                        if(x2>xmax)
                        {
                            x2=xmax;
                        }
                        drawline(x1,y1,x2,y2);
                    }
                }
            }
        }
        t1=0;
        t2=1;
        for(i=0;i<4;i++)
        {
            temp=q[i]/p[i];
            if(p[i]<0)
            {
                if(t1<=temp)
                t1=temp;
            }
            else
            {
                if(t2>temp)
                t2=temp;
            }
        }
        if(t1<t2)
        {
            xx1 = x1 + t1 * p[1];
            xx2 = x1 + t2 * p[1];
            yy1 = y1 + t1 * p[3];
            yy2 = y1 + t2 * p[3];
            drawline(xx1,yy1,xx2,yy2);
        }
	}
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
	glutCreateWindow("Liang Barsky");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(clip_points);
	glFlush();
	glutMainLoop();
	return 0;
}
