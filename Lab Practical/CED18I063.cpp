#include <GL/glut.h>
#include <cmath>
#include <time.h>
#define pi 3.1415
int sign(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}
void drawline(int X1, int Y1, int X2, int Y2)
{
	//This algorithm is the generalised DDA Algorithm
	glPointSize(10);
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
		glFlush();
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
	glEnd();
}

void para(int rx, int ry, int xc, int yc, float r, float g, float b)
{
    glPointSize(10);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    float x, y;
    for (int i = 0; i < 360; i++)
    {
        double radian = i * 3.141592653589 / 180;
        glVertex2f((xc + 1.0 * rx * cos(radian)), (yc + 1.0 * ry * sin(radian)));
    }
    glEnd();
}

void draw_general_circle(double cx, double cy, double r, double startAngle, double endAngle)
{
    glPointSize(10);
    double x = 0; double y = r;
    double ycal = floor(y / sqrt(2)) - 1;

    while (y > ycal)
    {
        glBegin(GL_POINTS);
        double alpha;
        alpha = 90 - (atan((float)y / x) * 180) / pi;
        // First Octant
        if (90 - alpha >= startAngle && 90 - alpha <= endAngle)
            glVertex2i(cx + x, cy + y);
        // Second Octant
        if (alpha >= startAngle && alpha <= endAngle)
            glVertex2i(cx + y, cy + x);
        // Third Octant
        if (180 - alpha >= startAngle && 180 - alpha <= endAngle)
            glVertex2i(cx - y, cy + x);
        // Fourth Octant
        if (90 + alpha >= startAngle && 90 + alpha <= endAngle)
            glVertex2i(cx - x, cy + y);
        // Fifth Octant
        if (270 - alpha >= startAngle && 270 - alpha <= endAngle)
            glVertex2i(cx - x, cy - y);
        // Sixth Octant
        if (180 + alpha >= startAngle && 180 + alpha <= endAngle)
            glVertex2i(cx - y, cy - x);
        // Seventh Octant
        if (360 - alpha >= startAngle && 360 - alpha <= endAngle)
            glVertex2i(cx + y, cy - x);
        // Eight Octant
        if (270 + alpha >= startAngle && 270 + alpha <= endAngle)
            glVertex2i(cx + x, cy - y);
        glEnd();
        x = x + 1;
        y = sqrt(((r * r) - (x * x)));
    }
	glEnd();
}
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	//Letter S
	drawline(-244, 231, -394, 231);
	draw_general_circle(-374,165,65,90,270);
	drawline(-394, 95, -244, 95);
	draw_general_circle(-280,0,90,270,360);
	draw_general_circle(-280,0,90,0,90);
	drawline(-244, -89, -394, -89);
	//Letter U
	drawline(-140, 231, -140, -89);
	drawline(-140, -89, 41, -89);
	drawline(41,-89, 41,231);
	//Letter J
	drawline(121, 231, 280, 231);
	drawline(240, 231, 240, -89);
	drawline(240, -89, 120, -89);
	drawline(120, -89, 120, 50);
	//Letter O- Using Ellipse Drawing Algorithm(Parametric)
	para(100,170,400,70,1,1,0);	
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
	glutCreateWindow("Lab Exam");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();
	return 0;
}
