#pragma once
#include "glut.h"
#include "Structs.h"

class Car {
private:
	Point current; // for drawing
	Pair junction;
	int carID;
	bool exist = false;
	bool isStuck = false;
	bool isMoving=false;
	vector<Pair> path; //every pair marks next junction
	Pair finalTarget;
	Color color;
	//Point nextJunction;

public:
	void setIsMoving(bool moving);
	bool getIsMoving();

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
	//bool getPassed();
};