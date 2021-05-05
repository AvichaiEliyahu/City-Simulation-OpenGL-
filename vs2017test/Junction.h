#pragma once
#include "glut.h"
#include "Structs.h"
#include "Road.h"

class Junction {
private:
	int id;
	Point offset;	//for drawing
	Pair position;	//for position in matrix
	int timeIntervals[4] = {};
	int greenRoad;
	int numOfRoads = 4;
	Road* inRoads[4] = {}; //0-UP, 3-LEFT

public:
	void showDetails();
	void setId(int ID);
	int getId();

	void setOffset(Point off);
	Point getOffset();

	void setPosition(Pair pos);
	Pair getPosition();

	void setTimeIntervals(int road0, int road1, int road2, int road3);
	int* getTimeIntervals();
	void setNextGreenRoad();

	Car* getFirstCarInGreenLight();

	void setInRoads(Road* myroads[4]);
	Road** getInRoads();
	Road* getGreenRoad();

	void setGreenRoad(int roadNumber);
	int getGreenRoadNum();
	
	void switchLights(int inRoad);
	void paintLights();
	void paintLight(directions d, double r, double g, double b);
	void initGreen();
	void drawJunction();
};