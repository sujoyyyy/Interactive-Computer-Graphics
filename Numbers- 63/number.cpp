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
	glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	//Number 6
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.2, 0.1);
	glVertex2f(-0.2, 0.5);
	glVertex2f(-0.1, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.5, 0.1);
	glVertex2f(-0.5, 0.2);
	glVertex2f(-0.1, 0.2);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.4, 0.1);
	glVertex2f(-0.5, 0.1);
	glVertex2f(-0.5, 0.8);
	glVertex2f(-0.4, 0.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.4);
	glVertex2f(-0.5, 0.4);
	glVertex2f(-0.5, 0.5);
	glVertex2f(-0.1, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.7);
	glVertex2f(-0.5, 0.7);
	glVertex2f(-0.5, 0.8);
	glVertex2f(-0.1, 0.8);
	glEnd();
	//Number 3
	glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0.1);
	glVertex2f(0.4, 0.1);
	glVertex2f(0.4, 0.8);
	glVertex2f(0.5, 0.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0.1);
	glVertex2f(0.1, 0.1);
	glVertex2f(0.1, 0.2);
	glVertex2f(0.5, 0.2);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0.4);
	glVertex2f(0.1, 0.4);
	glVertex2f(0.1, 0.5);
	glVertex2f(0.5, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0.7);
	glVertex2f(0.1, 0.7);
	glVertex2f(0.1, 0.8);
	glVertex2f(0.5, 0.8);
	glEnd();
	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();
}



int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Letters");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}