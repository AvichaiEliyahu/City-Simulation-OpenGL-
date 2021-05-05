#pragma once
#include "glut.h"
#include "Structs.h"

class Car {
private:
	Point current;
	Pair junction;
	int carID;
	bool exist = false;
	bool isStuck = false;
	vector<Pair> path;
	Pair finalTarget;
	Color color;

public:
	void setStuck(bool stuck);
	bool getStuck();
	bool changeStuck();

	void setCurrent(double x, double y);
	Point getCurrent();

	void setColor(Color newColor);
	void setJunction(Pair junc);
	Pair getJunction();

	void setCarId(int carId);
	int getCarId();

	void setExist(bool isExist);
	bool getExist();

	void setFinalTarget(Pair t);
	Pair getFinalTarget();
	Pair getNextJunction();

	void calcPath();
	void showPath();
	void removeTopJunctionFromPath();
	bool hasArrived();

	void moveCar(double dx, double dy);
	void drawCar();
	void toString();
};