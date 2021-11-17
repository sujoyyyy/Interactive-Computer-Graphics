#include<stdio.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
int left_edge[500], right_edge[500];
int xfirst[11]={-500,-300,-300,-500,-500};
int yfirst[11]={300,300,200,200,300};

void myDisplay();
void scanline_Filling(int xfirst[11], int yfirst[11]);
void edge_Detect(int x1, int y1, int x2, int y2);
void draw_pixel(int x, int y);


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    scanline_Filling(xfirst,yfirst);
    glFlush();
}

void scanline_Filling(int xfirst[11], int yfirst[11])
{
    for (int i = 0; i < 400; i++)
    {
        left_edge[i] = 300;     // Intial value
        right_edge[i] = 0;
    }
    int count = 0,x1,y1,x2,y2;
    int i=0;
	while(i<4)
	{
		x1=xfirst[i];
		x2=xfirst[i+1];
		y1=yfirst[i];
		y2=yfirst[i+1];
		glBegin(GL_LINES);
		glVertex2i( x1, y1);
		glVertex2i( x2, y2);
		glEnd();
        edge_Detect(x1,y1,x2,y2);
		//glFlush();
		i++;
	}
    edge_Detect(xfirst[4],yfirst[4],xfirst[0],yfirst[0]);
    int xsecond[5]={-200,-100,-100,-200,-200};
	int ysecond[5]={300,300,-200,-200,300};
    i=0;
    while(i<4)
	{
		x1=xsecond[i];
		x2=xsecond[i+1];
		y1=ysecond[i];
		y2=ysecond[i+1];
		glBegin(GL_LINES);
		glVertex2i( x1, y1);
		glVertex2i( x2, y2);
		glEnd();
        edge_Detect(x1,y1,x2,y2);
		glFlush();
		i++;
	}
    edge_Detect(xsecond[4],ysecond[4],xsecond[0],ysecond[0]);
    
  
    
    // Printing polygon
    for (int y = 0; y < 500; y++)
    {
        if (left_edge[y] <= right_edge[y])
        {
            for (int x = left_edge[y]; x < right_edge[y]; x++)
            {
                draw_pixel(x, y);
            }
        }
    }
    
}

void edge_Detect(int x1, int y1, int x2, int y2)
{
    // Slope shouldnt be in Negative
    if (y2 < y1)    // Swap the lines
    {
        int temp;
        
        temp = x1;
        x1 = x2;
        x2 = temp;
        
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    
    // Calculate Increment of X if line is parallel or.. find reciprocol of slope
    double increment_x = (y2 == y1)? (x2 - x1) : (x2 - x1) / (y2 - y1);
    
    double x = x1;  // Initial value of x
    for (int y = y1; y < y2; y++)   // while y stays in the line
    {
        left_edge[y] = (x < left_edge[y])? x : left_edge[y];
        right_edge[y] = (x > right_edge[y])? x : right_edge[y];
        x += increment_x;
    }
}

void draw_pixel(int x, int y)   // Plot a point at (x, y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-480, 480, -600, 600);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 480);
    glutCreateWindow("Scanline Polyfill");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}