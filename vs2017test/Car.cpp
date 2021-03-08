#include "Car.h"

void Car::setIsMoving(bool moving)
{
	isMoving = moving;
}

bool Car::getIsMoving()
{
	return isMoving;
}

void Car::setCurrent(double x, double y)
{
	current.x = x;
	current.y = y;
}

Point Car::getCurrent()
{
	return current;
}

void Car::setColor(Color newColor)
{
	color.r = newColor.r;
	color.g = newColor.g;
	color.b = newColor.b;
}

void Car::setJunction(Pair junc) {
	junction = junc;
}

Pair Car::getJunction() {
	return junction;
}

void Car::setCarId(int carId)
{
	carID = carId;
}

int Car::getCarId()
{
	return carID;
}

void Car::setExist(bool isExist) {
	exist = isExist;
}

bool Car::getExist() {
	return exist;
}

void Car::setFinalTarget(Pair t) {
	finalTarget = t;
}

Pair Car::getFinalTarget() {
	return finalTarget;
}

Pair Car::getNextJunction()
{
	if (path.size() == 0)
		return { NULL,NULL };
	return path.front();
}

void Car::calcPath()
{
	bool stop=false;
	path.push_back(junction);
	do {
	Pair lastJunc = path.back();
	Pair next = lastJunc;
	if (lastJunc.row != finalTarget.row) {
		next.row = finalTarget.row > lastJunc.row ? lastJunc.row + 1 : lastJunc.row - 1;
		path.push_back(next);
	}
	else if (lastJunc.col != finalTarget.col) {
		next.col = finalTarget.col > lastJunc.col ? lastJunc.col + 1 : lastJunc.col - 1;
		path.push_back(next);
	}
	else { stop = true; }
	} while (!stop);
	path.erase(path.begin());
}

void Car::showPath()
{
	printf("start: (%d,%d), target: (%d, %d)\npath:",
		junction.row, junction.col,finalTarget.row, finalTarget.col);
	for (Pair p : path) {
		printf("(%d,%d) -> ",p.row,p.col);
	}
	printf("\n");
}

void Car::removeTopJunctionFromPath()
{
	path.erase(path.begin());
}

bool Car::hasArrived()
{
	if (junction.row == finalTarget.row && junction.col == finalTarget.col) {
		//setColor(GREEN);
		return true;
	}
	return false;
}



void Car::moveCar(double dx, double dy)
{
	current.x += dx;
	current.y += dy;
}

void Car::drawCar()
{
	glPointSize(CAR_SIZE);
	glColor3d(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2d(current.x, current.y);
	glEnd();
}

void Car::toString()
{
	printf("car id: %d, current position: (%d, %d), path:\n",
		carID, junction);
	showPath();
	printf("\n");
}
