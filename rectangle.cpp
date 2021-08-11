#include <Windows.h>  
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int x, y;

void display() {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.
	glBegin(GL_POLYGON);
	glVertex3f(0.3, 0.2, 0);
	glVertex3f(0.3, -0.2, 0);
	glVertex3f(-0.3,-0.2,0);
	glVertex3f(-0.3, 0.2, 0);
	glEnd();

	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Rectangle");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
