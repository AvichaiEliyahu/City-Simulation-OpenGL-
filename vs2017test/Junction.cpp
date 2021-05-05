#include "Junction.h"

void Junction::showDetails() {
	for (int i = 0; i < numOfRoads; i++)
	printf("junction: (%d, %d), road: %d num of cars: %d\n",
		position.row, position.col, inRoads[i]->getDirection(), inRoads[i]->getNumOfCars());

}

void Junction::setId(int ID)
{
	id = ID;
}

int Junction::getId()
{
	return id;
	return 0;
}

void  Junction::setOffset(Point off) {
	offset = off;
}

Point Junction::getOffset() {
	return offset;
}

void Junction::setPosition(Pair pos) {
	position = pos;
}

Pair Junction::getPosition() {
	return position;
}


void Junction::setTimeIntervals(int road0, int road1, int road2, int road3)
{
	timeIntervals[0] = road0;
	timeIntervals[1] = road1;
	timeIntervals[2] = road2;
	timeIntervals[3] = road3;
}

int* Junction::getTimeIntervals()
{
	return timeIntervals;
}

void Junction::setNextGreenRoad()
{
	int currentGreenRoad = greenRoad;
	int nextGreenRoad = currentGreenRoad == 3 ? 0 : currentGreenRoad + 1;
	setGreenRoad(nextGreenRoad);
}

Car* Junction::getFirstCarInGreenLight()
{
	return inRoads[greenRoad]->getFirstCar();
}

void Junction::setInRoads(Road* myroads[4])
{
	for (int i = 0; i < numOfRoads; i++)
		inRoads[i] = myroads[i];
}

Road** Junction::getInRoads()
{
	return inRoads;
}

Road* Junction::getGreenRoad()
{
	return inRoads[greenRoad];
}

void Junction::switchLights(int inRoad)
{
	setGreenRoad(inRoad);
}

void Junction::paintLights() {
	for (int i = 0; i < 4; i++)
		if (i == greenRoad)
			paintLight(directions(i),0,1,0);
		else paintLight(directions(i), 1,0,0);
}

void Junction::paintLight(directions d, double r, double g, double b) {
	glBegin(GL_LINES);
	glColor3d(r, g, b);

	switch (d)
	{
	case UP:
		glVertex2d(0, LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, LIGHTS_LOCATION);
		break;
	case RIGHT:
		glVertex2d(LIGHTS_LOCATION, LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION, 0);
		break;
	case DOWN:
		glVertex2d(0, -LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION, -LIGHTS_LOCATION);
		break;
	case LEFT:
		glVertex2d(-LIGHTS_LOCATION, -LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, 0);
		break;
	}
	glEnd();
	//glColor3d(1,1,1);
}

void Junction::initGreen()
{
	switchLights(0);
}

void Junction::setGreenRoad(int roadNumber) {
	greenRoad = roadNumber;
}

int Junction::getGreenRoadNum()
{
	return greenRoad;
}

void Junction::drawJunction()
{
	/*if (position.row==4&&position.col==3) {
		glPointSize(10);
		glColor3d(1, 1, 1);
		glBegin(GL_POINTS);
		glVertex2d(0, 0);
		glEnd();
	}*/
	for (int i = 0; i < numOfRoads; i++) {
		inRoads[i]->drawRoad();
	//	inRoads[i]->drawCars();
	}

}
