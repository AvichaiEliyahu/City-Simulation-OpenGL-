#pragma once
#include "Junction.h"
#include "glut.h"
#define INFOFILENAME "info.txt"
#define TIMESFILENAME "times.txt"
#pragma warning (disable:4996)

class JunctionManager
{
private:
	int frames = 0;
	int framesRestarts = 0;
	int carsCounter = 0;
	Junction junctions[LENGTH][LENGTH];
	Road roads[LENGTH][LENGTH][4];
	Car cars[NUM_OF_CARS];

public:
	void initJunctions();
	void readLightsTimes();
	void initRoads();
	void initCarsAndMatchRoads();
	void putCarsOnRoads();
	void setInitialPositionOnRoads();
	void initGreens();
	void carsCheck();
	void JunctionsCheck();
	void roadsCheck();
	void generalCheck();
	bool finish();
	void move(Junction* junction);
	bool checkIfCarCanLeave(Junction* current);
	void drawAll();
	void writeFramesToFile(int frames);
	// a function taht moves on all junctions and checks where the first car in the green light need to leave
	void moveAll();
};

