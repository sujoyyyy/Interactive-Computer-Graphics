#include <Windows.h>  
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
int x, y;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	//Letter I
	glBegin(GL_POLYGON);
	glVertex2f(-0.4, 0.4);
	glVertex2f(-0.7, 0.4);
	glVertex2f(-0.7, 0.47);
	glVertex2f(-0.4, 0.47);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, 0.1);
	glVertex2f(-0.6, 0.1);
	glVertex2f(-0.6, 0.4);
	glVertex2f(-0.5, 0.4);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.4, 0.03);
	glVertex2f(-0.7, 0.03);
	glVertex2f(-0.7, 0.1);
	glVertex2f(-0.4, 0.1);
	glEnd();
	//Letter C
	glColor3d((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	glBegin(GL_POLYGON);
	glVertex2f(0.1,0.03);
	glVertex2f(-0.2, 0.03);
	glVertex2f(-0.2, 0.1);
	glVertex2f(0.1, 0.1);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.1,0.03);
	glVertex2f(-0.2, 0.03);
	glVertex2f(-0.2, 0.47);
	glVertex2f(-0.1, 0.47);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0.4);
	glVertex2f(-0.2, 0.4);
	glVertex2f(-0.2, 0.47);
	glVertex2f(0.1, 0.47);
	glEnd();
	//Letter G
	glColor3d((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	glBegin(GL_POLYGON);
	glVertex2f(0.6, 0.03);
	glVertex2f(0.5, 0.03);
	glVertex2f(0.5, 0.2);
	glVertex2f(0.6, 0.2);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.6, 0.03);
	glVertex2f(0.3, 0.03);
	glVertex2f(0.3, 0.1);
	glVertex2f(0.6, 0.1);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.4, 0.1);
	glVertex2f(0.3, 0.1);
	glVertex2f(0.3, 0.47);
	glVertex2f(0.4, 0.47);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.6, 0.4);
	glVertex2f(0.3, 0.4);
	glVertex2f(0.3, 0.47);
	glVertex2f(0.6, 0.47);
	glEnd();
	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();
}



int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000, 1280);
	glutCreateWindow("Letters");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}