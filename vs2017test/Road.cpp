#include "Road.h"


void Road::setId(int roadId)
{
	id = roadId;
}

int Road::getId()
{
	return id;
}

void Road::setPosition(Pair pos) {
	position = pos;
}

Pair Road::getPosition() {
	return position;
}

int Road::getNumOfCars() {
	return cars.size();
}

void Road::setDirection(directions dir)
{
	direction = dir;
}

directions Road::getDirection()
{
	return direction;
}

Car* Road::removeFromTop()
{
	Car* c = cars[0];
	cars.erase(cars.begin());
	refreshCarsPositions();
	return c;
}



bool Road::addToEnd(Car* car, bool initial)
{	
	int max = initial ? int(MAX_CARS_PER_ROAD*0.66) : MAX_CARS_PER_ROAD;
	if (cars.size() < max) {
		cars.push_back(car);
		car->setJunction({position.row, position.col});
		//endAnimation();
		refreshCarsPositions();

		/*
		* add a function that puts the car at the end of the road and drives it as
		* far in the road as possible
		*/
		return true;
	}
	return false;
}

bool Road::addToEndWithoutAnim(Car* car)
{
	if (cars.size() < MAX_CARS_PER_ROAD) {
		cars.push_back(car);
		car->setJunction({ position.row, position.col });
		//endAnimation();
		refreshCarsPositions();

		/*
		* add a function that puts the car at the end of the road and drives it as
		* far in the road as possible
		*/
		return true;
	}
	return false;
}

void Road::refreshCarsPositions()
{
	for (int i = 0; i < cars.size(); i++)
		switch (direction) {
		case UP:
			// put on the back of road
			cars[i]->setCurrent(-(1.0 / 6.0), SMALL_GAP + (1.2 / 3.0) + i * GAP);
			break;
		case RIGHT:
			cars[i]->setCurrent(SMALL_GAP + (1.2 / 3.0) + i * GAP, (1.0 / 6.0));
			break;
		case DOWN:
			cars[i]->setCurrent(+(1.0 / 6.0), -SMALL_GAP - (1.2 / 3.0) - i * GAP);
			break;
		case LEFT:
			cars[i]->setCurrent(-SMALL_GAP - (1.2 / 3) - i * GAP, -(1.0 / 6.0));
			break;
		}
}

void Road::endAnimation()
{
	if (cars.size() == 0)
		return;
	for (int i = 0; i < cars.size(); i++)
	switch (direction) {
	case UP:
		//cars[i]->setCurrent(-(1.0 / 6.0), SMALL_GAP + (1.2 / 3.0) + i * GAP);
		if (!cars[i]->getIsMoving()) {
			cars[i]->setCurrent(-(1.0 / 6.0), BACK_OF_ROAD);
			cars[i]->setIsMoving(true);
		}
		if (cars[i]->getCurrent().y > SMALL_GAP + (1.2 / 3.0) + (getNumOfCars()-1) * GAP)
			cars[i]->moveCar(0, -SPEED);
	//	else cars[cars.size() - 1]->setIsMoving(false);
		break;
	case RIGHT:
		//cars[i]->setCurrent(SMALL_GAP + (1.2 / 3) + i * GAP, (1.0 / 6.0));
		if (!cars[i]->getIsMoving()) {
			cars[i]->setCurrent(BACK_OF_ROAD, (1.0 / 6.0));
			cars[i]->setIsMoving(true);
		}
		if (cars[i]->getCurrent().x > SMALL_GAP + (1.2 / 3) + (getNumOfCars() - 1) * GAP)
			cars[i]->moveCar(-SPEED,0);
		//else cars[cars.size() - 1]->setIsMoving(false);
		break;
	case DOWN:
		//cars[i]->setCurrent(+(1.0 / 6.0), -SMALL_GAP - (1.2 / 3.0) - i * GAP);
		if (!cars[i]->getIsMoving()) {
			cars[i]->setCurrent(+(1.0 / 6.0), -BACK_OF_ROAD);
			cars[i]->setIsMoving(true);
		}
		if (cars[i]->getCurrent().y < -SMALL_GAP - (1.2 / 3.0) - (getNumOfCars() - 1) * GAP)
			cars[i]->moveCar(0, SPEED);
		//else cars[cars.size() - 1]->setIsMoving(false);
		break;
	case LEFT:
		//cars[i]->setCurrent(-SMALL_GAP - (1.2 / 3) - i * GAP, -(1.0 / 6.0));
		if (!cars[i]->getIsMoving()) {
			cars[i]->setCurrent(-BACK_OF_ROAD, -(1.0 / 6.0));
			cars[i]->setIsMoving(true);
		}
		if (cars[i]->getCurrent().x < -SMALL_GAP - (1.2 / 3) - (getNumOfCars() - 1) * GAP)
			cars[i]->moveCar(SPEED,0);
		//else cars[cars.size() - 1]->setIsMoving(false);
		break;
	}
}

void Road::MoveFirstCarAnimation(/*Car* car*/)
{
	switch (direction) {
	case UP:
		//cars[0]->setCurrent(-(1.0 / 6.0), BACK_OF_ROAD);
		do {
			cars[0]->moveCar(0,-SPEED);
		} while (1);
		break;
	case RIGHT:
	//	car->setCurrent(BACK_OF_ROAD, (1.0 / 6.0));
		break;
	case DOWN:
	//	car->setCurrent(+(1.0 / 6.0), -BACK_OF_ROAD);
		break;
	case LEFT:
	//	car->setCurrent(-BACK_OF_ROAD, -(1.0 / 6.0));
		break;
	}
}

int Road::checkCarsArrival()
{
	int carsArrived=0;
	for(Car* c : cars)
		if (c->hasArrived()) {
			printf("car: id: %d, current junction: (%d,%d) has arrived it's destination: (%d, %d)\n",
				c->getCarId(), c->getJunction(), c->getFinalTarget());
			cars.erase(std::remove(cars.begin(), cars.end(), c), cars.end());
			c->setExist(false);
			//carsCounter--;
			carsArrived++;
			refreshCarsPositions();
		}
	return carsArrived;
}

Car* Road::getFirstCar()
{
	if (cars.size() == 0)
		return NULL;
	return cars[0];
}

bool Road::checkRoadAvailability(Car* car)
{
	if (cars.size() < MAX_CARS_PER_ROAD) {
		cars.push_back(car);
		car->setJunction({ position.row, position.col });
		return true;
	}
	return false;
}
void Road::setInitialPositions() {
	for (int i = 0; i < cars.size(); i++)
		switch (direction) {
		case UP:
			cars[i]->setCurrent(-(1.0 / 6.0), SMALL_GAP+(1.2 / 3.0)+i*GAP);
			break;
		case RIGHT:
			cars[i]->setCurrent(SMALL_GAP+(1.2 / 3) + i * GAP, (1.0 / 6.0));
			break;
		case DOWN:
			cars[i]->setCurrent(+(1.0 / 6.0),- SMALL_GAP -(1.2 / 3) - i * GAP);
			break;
		case LEFT:
			cars[i]->setCurrent(-SMALL_GAP-(1.2 / 3) - i * GAP, -(1.0 / 6.0));
			break;
		}
}
void Road::moveCars() {
	
	//move the car

}

void Road::drawCars()
{
	//if(position.row==4 && position.col==4 && direction==2)
	//printf("from display: %d\n", getNumOfCars());

	for (int i = 0; i < cars.size(); i++)
		cars[i]->drawCar();
}

void Road::drawRoad()
{
	glColor3d(1, 1, 1);
	switch (direction) {
	case LEFT:

		glBegin(GL_LINES);
		glColor3d(0, 0, 0);
		glVertex2d(-1, 0);
		glVertex2d(-LIGHTS_LOCATION, 0);
		glColor3d(1, 1, 1);
		glVertex2d(-1, -LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, -LIGHTS_LOCATION);
		glVertex2d(-1, LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, LIGHTS_LOCATION);

		//light

		glVertex2d(-LIGHTS_LOCATION, -LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, -0.1);

		glEnd();
		break;

	case RIGHT:
		glBegin(GL_LINES);
		glColor3d(0,0,0);
		glVertex2d(1, 0);
		glVertex2d(LIGHTS_LOCATION, 0);
		glColor3d(1, 1, 1);
		glVertex2d(1, LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION, LIGHTS_LOCATION);
		glVertex2d(1, -LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION,- LIGHTS_LOCATION);

		//light
		glVertex2d(LIGHTS_LOCATION, LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION, 0.1);

		glEnd();
		break;

	case UP:
		glBegin(GL_LINES);
		glColor3d(0,0,0);
		glVertex2d(0, 1);
		glVertex2d(0, LIGHTS_LOCATION);
		glColor3d(1, 1, 1);
		glVertex2d(-LIGHTS_LOCATION, 1);
		glVertex2d(-LIGHTS_LOCATION, LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION, 1);
		glVertex2d(LIGHTS_LOCATION, LIGHTS_LOCATION);

		//light
		glVertex2d(-0.1, LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, LIGHTS_LOCATION);

		glEnd();
		break;

	case DOWN:
		glBegin(GL_LINES);
		glColor3d(0, 0, 0);
		glVertex2d(0 , -1);
		glVertex2d(0, -LIGHTS_LOCATION);
		glColor3d(1, 1, 1);
		glVertex2d(LIGHTS_LOCATION, -1);
		glVertex2d(LIGHTS_LOCATION, -LIGHTS_LOCATION);
		glVertex2d(-LIGHTS_LOCATION, -1);
		glVertex2d(-LIGHTS_LOCATION, -LIGHTS_LOCATION);

		//light
		glVertex2d(0.1, -LIGHTS_LOCATION);
		glVertex2d(LIGHTS_LOCATION, -LIGHTS_LOCATION);


		glEnd();
		break;
	}
	drawCars();
}

void Road::toString()
{
	printf("road id: %d, position: (%d, %d), direction: %d, number of cars: %d, cars details:\n",
		id, position, direction, getNumOfCars());
	for (Car* c : cars)
		c->toString();
}
