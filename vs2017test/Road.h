#pragma once
#include "glut.h"
#include "Structs.h"
#include "Car.h"

class Road {

private:
	int id;
	int currentFrames = 0;
	int numOfStuckCars = 0;
	Pair position;	//for position in matrix
	enum directions direction;
	vector<Car*> cars;

public:
	void setId(int roadId);
	int getId();

	void increaseNumOfStuckCars();
	int getNumOfStuckCars();

	void setCurrentFrames(int frames);
	int getCurrentFrames();

	void setPosition(Pair pos);
	Pair getPosition();

	int getNumOfCars();

	void setDirection(directions dir);
	directions getDirection();

	Car* removeFromTop();
	bool addToEnd(Car* car, bool initial);
	bool addToEndWithoutAnim(Car* car);
	void refreshCarsPositions();
	int checkCarsArrival();
	Car* getFirstCar();
	bool checkRoadAvailability(Car* car);
	void setInitialPositions();
	void drawCars();
	void drawRoad();
	void toString();
};