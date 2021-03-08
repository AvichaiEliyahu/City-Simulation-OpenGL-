#pragma once
#include "glut.h"
#include "Structs.h"
#include "Car.h"

class Road {

private:
	int id;
	Pair position;	//for position in matrix
	enum directions direction;
	vector<Car*> cars;

public:
	void setId(int roadId);
	int getId();

	void setPosition(Pair pos);
	Pair getPosition();

	int getNumOfCars();

	void setDirection(directions dir);
	directions getDirection();

	Car* removeFromTop();
	bool addToEnd(Car* car);
	bool addToEndWithoutAnim(Car* car);
	void refreshCarsPositions();
	void endAnimation();
	void MoveFirstCarAnimation();
	int checkCarsArrival();
	Car* getFirstCar();
	bool checkRoadAvailability(Car* car);
	void setInitialPositions();
	void moveCars();
	void drawCars();
	void drawRoad();
	void toString();
};