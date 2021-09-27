//#include <Windows.h>
#include <GL/glut.h>
#include <cmath>
#include <time.h>

#define pi 3.1415

float rtod(float radians)
{
    return radians * 180.0 / pi;
}

void med(int rx, int ry, int xc, int yc, float r, float g, float b, int alpha, int beta)
{
    glPointSize(3);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);

    int s1 = 0, e1 = 0, s2 = 0, e2 = 0;
    int start, end;

    if (beta == 360) //full ellipse case
    {
        s1 = 0;
        e1 = 360;
    }
    else if (beta > 0)
    {

        start = (alpha + 360) % 360; //for negative alpha
        end = (alpha + beta + 360) % 360;

        if (end >= start)
        {
            s1 = start;
            e1 = end;
            s2 = start;
            e2 = end;
        }
        else
        {
            s1 = start;
            e1 = 360;
            s2 = 0;
            e2 = end;
        }
    }
    else if (beta < 0)
    {
        start = (alpha + beta + 720) % 360;
        end = (alpha + 360) % 360;

        if (start <= end)
        {
            s1 = start;
            e1 = end;
            s2 = start;
            e2 = end;
        }
        else
        {
            s1 = start;
            e1 = 360;
            s2 = 0;
            e2 = end;
        }
    }

    float a;

    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) +
        (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy)
    {

        // Print points based on 4-way symmetry
        a = rtod(atan((float)(y) / (float)(x))); // tan-1(y/x)
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(x + xc, y + yc);

        a = rtod(pi - atan((float)(y) / (float)(x)));
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(-x + xc, y + yc);

        a = rtod(2 * pi - atan((float)(y) / (float)(x)));
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(x + xc, -y + yc);

        a = rtod(pi + atan((float)(y) / (float)(x)));
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(-x + xc, -y + yc);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
        ((rx * rx) * ((y - 1) * (y - 1))) -
        (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0)
    {

        // Print points based on 4-way symmetry
        a = rtod(atan((float)(y) / (float)(x))); // tan-1(y/x)
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(x + xc, y + yc);

        a = rtod(pi - atan((float)(y) / (float)(x)));
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(-x + xc, y + yc);

        a = rtod(2 * pi - atan((float)(y) / (float)(x)));
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(x + xc, -y + yc);

        a = rtod(pi + atan((float)(y) / (float)(x)));
        if ((a >= s1 && a <= e1) || (a >= s2 && a <= e2))
            glVertex2f(-x + xc, -y + yc);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
    glEnd();
}

void arc()
{

    glClear(GL_COLOR_BUFFER_BIT);
    srand(time(0));
    float r = (float)((rand() % 2));
    float g = (float)((rand() % 2));
    float b = (float)((rand() % 2));
    int xc = 200, yc = 200, rx = 20, ry = 30; int alpha, beta;
    xc = (int)((rand() % 101));
    yc = (int)((rand() % 101));
    rx = (int)((rand() % 300));
    ry = (int)((rand() % 300));
    alpha = (int)(-360 + (rand() % 721));
    beta = (int)(-360 + (rand() % 721));
    //alpha=0;beta=90;
    med(rx, ry, xc, yc, r, g, b, alpha, beta);
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
	glutDisplayFunc(arc);
	glFlush();
	glutMainLoop();
	return 0;
}
