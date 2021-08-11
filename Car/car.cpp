#include <Windows.h>  
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 100;
	GLfloat twicePi = 2.0f * 3.142;
	glColor3d(0.1, 0.1111, 0.11);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void display() {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.
	glColor3d(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.4, 0);
	glVertex3f(-0.8, -0.4, 0);
	glVertex3f(-0.8, 0, 0);
	glVertex3f(0.5, 0, 0);
	glEnd();
	glColor3d(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0, 0);
	glVertex3f(-0.4, 0, 0);
	glVertex3f(-0.25, 0.4, 0);
	glVertex3f(0.35, 0.4, 0);
	glEnd();
	drawFilledCircle(-0.4, -0.4, 0.1);
	drawFilledCircle(0.25, -0.4, 0.1);
	glColor3d(0.1, 0.1111, 0.11);
	glBegin(GL_POLYGON);
	glVertex3f(-0.01, 0.01, 0);
	glVertex3f(-0.39, 0.01, 0);
	glVertex3f(-0.24, 0.39, 0);
	glVertex3f(-0.01, 0.39, 0);
	glEnd();
	glColor3d(0.1, 0.1111, 0.11);
	glBegin(GL_POLYGON);
	glVertex3f(0.49, 0.01, 0);
	glVertex3f(0.01, 0.01, 0);
	glVertex3f(0.01, 0.39, 0);
	glVertex3f(0.34, 0.39, 0);
	glEnd();
	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Car");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}