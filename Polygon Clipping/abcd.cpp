#include <GL/glew.h>
#include <GL/freeglut.h>
#include<time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int p = 10;
int q = 6;
/*int px_cordinates[5] = {100,250,350,175,50};
int py_cordinates[5] = {250,250,350,600,350};*/
int px_cordinates[10] = { 100,350,350,270,270,200,200,300,350,100 };
int py_cordinates[10] = { 100,100,270,270,150,150,600,450,650,650 };
int qx_cordinates[6] = { 200,400,550,400,200,50 };
int qy_cordinates[6] = { 200,200,350,550,550,400 };
void point_position();
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutCreateWindow("point_posotion");
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(point_position);
	glutMainLoop();
	return 0;
}

void point_position()
{
	glColor3f(0, 0, 1);
	gluOrtho2D(0.0, 750.0, 0.0, 750.0);
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0;i < q;i++)
	{
		glVertex2f(qx_cordinates[i], qy_cordinates[i]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (i = 0;i < p;i++)
	{
		glVertex2f(px_cordinates[i], py_cordinates[i]);
	}
	glEnd();
	int j,p1x,p1y,p2x,p2y,q1x,q1y,q2x,q2y;
	int x_cordinates[20];
	int y_cordinates[20];
	for (i = 0;i < p;i++)
	{
		x_cordinates[i] = px_cordinates[i];
		y_cordinates[i] = py_cordinates[i];
	}
	int edges = p;
	int cnt;
	int tempx[20], tempy[20];
	for (i = 0;i < q;i++)
	{
		//printf("1\n");
		 cnt = 0;
		if (i == q - 1)
		{
			q1x = qx_cordinates[q - 1];
			q1y = qy_cordinates[q - 1];
			q2x = qx_cordinates[0];
			q2y = qy_cordinates[0];
		}
		else
		{
			q1x = qx_cordinates[i];
			q1y = qy_cordinates[i];
			q2x = qx_cordinates[i + 1];
			q2y = qy_cordinates[i + 1];
		}
		for (j = 0;j < edges;j++)
		{
			//printf("2\n");
			if (j == edges - 1)
			{
				p1x = x_cordinates[edges - 1];
				p1y = y_cordinates[edges - 1];
				p2x = x_cordinates[0];
				p2y = y_cordinates[0];
			}
			else
			{
				p1x = x_cordinates[j];
				p1y = y_cordinates[j];
				p2x = x_cordinates[j+1];
				p2y = y_cordinates[j+1];
			}

			int pos1, pos2;
			pos1 = ((q2x - q1x) * (p1y - q1y)) - ((q2y - q1y) * (p1x - q1x));
			pos2 = ((q2x - q1x) * (p2y - q1y)) - ((q2y - q1y) * (p2x - q1x));

			

			if (pos1 >= 0 && pos2 >= 0)
			{
				tempx[cnt] = p2x;
				tempy[cnt] = p2y;
				cnt += 1;
				//printf("a\n");
			}
			else if (pos1 >= 0 && pos2<=0)
			{
				int a1, b1, c1, a2, b2, c2;
				a1 = q2y - q1y;
				b1 = q1x - q2x;
				c1 = q1y * (q2x - q1x) - q1x * (q2y - q1y);
				a2 = p2y - p1y;
				b2 = p1x - p2x;
				c2 = p1y * (p2x - p1x) - p1x * (p2y - p1y);
				tempx[cnt] = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
				tempy[cnt] = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
				cnt = cnt + 1;
			}
			else if(pos1<=0 && pos2>=0)
			{
				int a1, b1, c1, a2, b2, c2;
				a1 = q2y - q1y;
				b1 = q1x - q2x;
				c1 = q1y * (q2x - q1x) - q1x * (q2y - q1y);
				a2 = p2y - p1y;
				b2 = p1x - p2x;
				c2 = p1y * (p2x - p1x) - p1x * (p2y - p1y);
				tempx[cnt] = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
				tempy[cnt] = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
				cnt = cnt + 1;
				tempx[cnt] = p2x;
				tempy[cnt] = p2y;
				cnt += 1;
			}


		}
		edges = cnt;
		//printf("edges = %d\n",edges);
		for (j = 0;j < cnt;j++)
		{
			x_cordinates[j] = tempx[j];
			y_cordinates[j] = tempy[j];
		}

	}

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (i = 0;i < edges;i++)
	{
		printf("%d %d\n", x_cordinates[i], y_cordinates[i]);
		glVertex2f(x_cordinates[i], y_cordinates[i]);
	}
	glEnd();

	glFlush();
}