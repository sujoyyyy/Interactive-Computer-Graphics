#include<Windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;
#define PI 3.141592

double rtod(float radians)
{
    return radians * 180.0 / PI;
}

void draw_general_circle(double cx, double cy, double r, double startAngle, double endAngle)
{
    glPointSize(15);
    double x = 0; double y = r;
    double ycal = floor(y / sqrt(2)) - 1;

    while (y > ycal)
    {
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        double alpha;
        alpha = 90 - (atan((float)y / x) * 180) / PI;
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
}

double draw_general_line(double x1, double y1, double x2, double y2)
{
    glPointSize(15);
    if (x1 == x2)
    {
        while (y1 != y2)
        {
            if (y1 > y2)
            {
                glBegin(GL_POINTS);
                glVertex2i(x1, y1);
                y1 -= 1;
                glEnd();

            }
            else
            {
                glBegin(GL_POINTS);
                glVertex2i(x1, y1);
                y1 += 1;
                glEnd();

            }
        }
    }

    double slope = (y2 - y1) / (x2 - x1);

    while (x1 < x2)
    {
        glBegin(GL_POINTS);

        glVertex2i(x1, y1);
        x1 += 1;
        y1 += slope;
        y1 = round(y1);
        glEnd();


    }
    return 0;
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // Code for P
    draw_general_line(-200, 200, -200, 600);
    draw_general_circle(-200, 500, 100, 0, 90);
    draw_general_circle(-200, 500, 100, 270, 360);
    // Code for R
    glColor3f(1.0, 1.0, 1.0);
    draw_general_line(0, 200, 0, 600);
    draw_general_circle(0, 500, 100, 0, 90);
    draw_general_circle(0, 500, 100, 270, 360);
    draw_general_line(0, 400, 100, 200);
    glColor3f(1.0, 1.0, 1.0);
    // Code for A
    draw_general_line(250, 408, 350, 408);
    draw_general_line(200, 200, 300, 600);
    draw_general_line(300, 600, 400, 200);
    // Code for T
    glColor3f(1.0, 1.0, 1.0);
    draw_general_line(450, 600, 650, 600);
    draw_general_line(550, 600, 550, 200);
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
    glutInitWindowSize(1600, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Car");
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glFlush();
    glutMainLoop();
    return 0;
}