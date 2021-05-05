#pragma once
#include "glut.h"
#include "JunctionManager.h"
#pragma warning (disable:4996)
JunctionManager manager;

void init()
{
	glClearColor(0.6, 0.6, 0.6, 0);
	glOrtho(-LENGTH -1, LENGTH +1, -LENGTH -1, LENGTH +1, 1, -1);
	manager.initJunctions();
	manager.initRoads();
	manager.initCarsAndMatchRoads();
	manager.initGreens();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	manager.drawAll();
	glutSwapBuffers(); // show all
}

void idle()
{
	if (manager.finish()) {
		printf("\nexisting!\n");
		Sleep(1000);
		exit(0);
	}
	manager.moveAll();
	glutPostRedisplay();
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("City Simulation");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();

	glutMainLoop();
}