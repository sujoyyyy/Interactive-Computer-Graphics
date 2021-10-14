#include <GL/gl.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

typedef struct coordinate
{
    int x,y;
    char code[4];
}PT;

int xmin= -300;
int xmax=300;
int ymin=-200;
int ymax=200;


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
		if(x<=xmax && x>=xmin && y<=ymax && y>=ymin)
		{
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
	glEnd();
}



PT setcode(PT p) //for setting the 4 bit code
{
    PT ptemp;
    if(p.y<ymin)
        ptemp.code[0]='1'; //Top
    else
        ptemp.code[0]='0';
    if(p.y>ymax)
        ptemp.code[1]='1'; //Bottom
    else
        ptemp.code[1]='0';
    if(p.x>xmax)
        ptemp.code[2]='1'; //Right
    else
        ptemp.code[2]='0';
    if(p.x<xmin)
        ptemp.code[3]='1'; //Left
    else
        ptemp.code[3]='0';
    
    ptemp.x=p.x;
    ptemp.y=p.y;
    return(ptemp);
}

int visibility(PT p1,PT p2)
{
    int i,flag=0;
    for(i=0;i<4;i++)
    {
        if((p1.code[i]!='0') || (p2.code[i]!='0'))
            flag=1;
    }
    if(flag==0)
        return(0);
    for(i=0;i<4;i++)
    {
        if((p1.code[i]==p2.code[i]) && (p1.code[i]=='1'))
            flag=0;
    }
    if(flag==0)
        return(1);
    
    return(2);
}

PT resetendpt(PT p1,PT p2)
{
    PT temp;
    int x,y,i;
    float m,k;
    if(p1.code[3]=='1')
    x=xmin;
    if(p1.code[2]=='1')
    x=xmax;
    if((p1.code[3]=='1') || (p1.code[2]=='1'))
    {
        m=(float)(p2.y-p1.y)/(p2.x-p1.x);
        k=(p1.y+(m*(x-p1.x)));
        temp.y=k;
        temp.x=x;
        for(i=0;i<4;i++)
            temp.code[i]=p1.code[i];
        if(temp.y<=ymax && temp.y>=ymin)
            return (temp);
    }
    if(p1.code[0]=='1')
        y=ymin;
    if(p1.code[1]=='1')
        y=ymax;
    if((p1.code[0]=='1') || (p1.code[1]=='1'))
    {
        m=(float)(p2.y-p1.y)/(p2.x-p1.x);
        k=(float)p1.x+(float)(y-p1.y)/m;
        temp.x=k;
        temp.y=y;
        for(i=0;i<4;i++)
            temp.code[i]=p1.code[i];
        return(temp);
    }
    else
        return(p1);
}


void clip_lines()
{
	srand(time(0));
    glColor3f(1,1,1);
	drawline(-300,-200,300,-200);
	drawline(-300,200,300,200);
	drawline(-300,-200,-300,200);
	drawline(300,-200,300,200);
	glColor3f(0,1,0);
    int n=10;
    for (int i = 0; i < n; i++)
	{
        PT p1,p2,p3,p4;
        p1.x=rand()%900-455;
		p1.y=rand()%780-410;
        p2.x=rand()%900-455;
		p2.y=rand()%780-410;
        p1=setcode(p1);
        p2=setcode(p2);
        int v = visibility(p1,p2);
        switch(v)
        {
            case 0: drawline(p1.x,p1.y,p2.x,p2.y); break;
            case 2: 
                {
                    p3=resetendpt(p1,p2);
                    p4=resetendpt(p2,p1);
                    drawline(p3.x,p3.y,p4.x,p4.y);
                    break;
                }
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
	glutCreateWindow("Cohen Sutherland");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(clip_lines);
	glFlush();
	glutMainLoop();
	return 0;
}
