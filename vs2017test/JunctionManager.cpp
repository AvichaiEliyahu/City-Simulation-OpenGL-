#include "JunctionManager.h"

void JunctionManager::initJunctions() {
	int flip = -1;
	int iOffset, jOffset;	//-LENGTH -> LENGTH (+2)
	int iIndex, jIndex;		//0 -> LENGTH-1 (+1)
	for (iOffset = -LENGTH + 1, jIndex = 0; iOffset <= LENGTH - 1; iOffset += JUNCTION_SIZE, jIndex++) {
		for (jOffset = -LENGTH + 1, iIndex = 0; jOffset <= LENGTH - 1; jOffset += JUNCTION_SIZE, iIndex++) {
			junctions[iIndex][jIndex].setId(iIndex * (LENGTH)+jIndex);
			Point offset;
			offset.x = iOffset;
			offset.y = jOffset;
			junctions[iIndex][jIndex].setOffset(offset);

			Pair position;
			position.row = iIndex;
			position.col = jIndex;
			junctions[iIndex][jIndex].setPosition(position);

			Road* in[4] = {
				&roads[iIndex][jIndex][0],
				&roads[iIndex][jIndex][1],
				&roads[iIndex][jIndex][2],
				&roads[iIndex][jIndex][3]
			};

			junctions[iIndex][jIndex].setInRoads(in);
		}
	}
	readLightsTimes();
}

void JunctionManager::readLightsTimes()
{
	FILE* timesFile = fopen("C://Users//aviha//Desktop//final project//new//vs2017test//times.txt", "r");
	if (!timesFile) {
		printf("\nerror opening times file!\n");
		return;
	}
	int road0, road1, road2, road3;
	int counter = 0;
	for (int i = 1; i < LENGTH-1; i++) {
		for (int j = 1; j < LENGTH-1; j++) {
			fscanf(timesFile,"%d %d %d %d", &road0, &road1, &road2, &road3);
			junctions[i][j].setTimeIntervals(road0, road1, road2, road3);
		}
	}
	fclose(timesFile);
	/*for (int i = 1; i < LENGTH -1; i++)
		for (int j = 1; j < LENGTH -1; j++) {
			printf("(%d %d) %d %d %d %d\n",i,j,
				junctions[i][j].getTimeIntervals()[0],
				junctions[i][j].getTimeIntervals()[1],
				junctions[i][j].getTimeIntervals()[2],
				junctions[i][j].getTimeIntervals()[3]);
		}
			*/
}

void JunctionManager::initRoads() {
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			for (int k = 0; k < 4; k++) {
				Pair position;
				position.row = i;
				position.col = j;
				roads[i][j][k].setPosition(position);
				roads[i][j][k].setDirection(directions(k));
				roads[i][j][k].setId(i * (LENGTH) * 4 + j * 4 + k);

			}
}

void JunctionManager::initCarsAndMatchRoads() {
	putCarsOnRoads();
	/*roads[1][1][0].addToEndWithoutAnim(&cars[0]);
	cars[0].setExist(true);
	cars[0].setColor(BLACK);
	Pair currentJunc, target;
	currentJunc.row = 1;///------------------ rows and cols
	currentJunc.col = 1;
	target.row = 3;
	target.col = 3;
	cars[0].setJunction(currentJunc);
	cars[0].setFinalTarget(target);
	carsCounter++;*/
	for (int i = 0; i < NUM_OF_CARS; i++) {
		cars[i].setCarId(i);
		cars[i].calcPath();
	}
}

void JunctionManager::putCarsOnRoads() {
	FILE* infoFile = fopen("C://Users//aviha//Desktop//final project//new//vs2017test//info.txt", "r");
	if (!infoFile) {
		printf("\nerror opening info file!\n");
		return;
	}
	int i;
	int roadArrayX, roadArrayY, roadArrayZ;
	int targetX, targetY;
	//carsCounter = 0;
	for (i = 0; i < NUM_OF_CARS; i++) {
		fscanf(infoFile, "%d %d %d %d %d",
			&roadArrayX, &roadArrayY, &roadArrayZ, &targetX, &targetY);
		if (roads[roadArrayX][roadArrayY][roadArrayZ].addToEnd(&cars[i])) {
			cars[i].setExist(true);
			cars[i].setColor(BLACK);
			Pair currentJunc, target;
			currentJunc.row = roadArrayX;///------------------ rows and cols
			currentJunc.col = roadArrayY;
			target.row = targetX;
			target.col = targetY;
			cars[i].setJunction(currentJunc);
			cars[i].setFinalTarget(target);
			carsCounter++;
		}
	}
	fclose(infoFile);
	//setInitialPositionOnRoads();
}

void JunctionManager::setInitialPositionOnRoads() {
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			for (int k = 0; k < 4; k++)
				roads[i][j][k].setInitialPositions();
}

void JunctionManager::initGreens()
{
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			junctions[i][j].setGreenRoad(0);
	/*
	int col = 3;
	int row = 4;
	printf("first car next junc: %d %d\n", 
		junctions[col][row].getInRoads()[junctions[col][row].getGreenRoad()]->getFirstCarNextJunc().row,
		junctions[col][row].getInRoads()[junctions[col][row].getGreenRoad()]->getFirstCarNextJunc().col);
	printf("%d", checkIfCarCanLeave(&junctions[col][row]));*/
}

void JunctionManager::carsCheck()
{
	int counter1 = 0, counter2 = 0;
	for (int i = 0; i < NUM_OF_CARS; i++)// counts only the cars from the cars array that exist in the program
		if (cars[i].getExist())
			counter1++;

	for (int i = 0; i < LENGTH; i++)// counts all cars from all roads
		for (int j = 0; j < LENGTH; j++)
			for (int k = 0; k < 4; k++)
				counter2+=junctions[i][j].getInRoads()[k]->getNumOfCars();

	printf("counter1 = %d counter2 = %d",counter1,counter2);// counter1 and counter2 should be equal
	/*junctions[3][4].getFirstCarInGreenLight()->showPath();
	printf("\n%d", checkIfCarCanLeave(&junctions[3][4]));*/
}

void JunctionManager::JunctionsCheck()
{
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			printf("(%d,%d) <-> (%d,%d) (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n",
				i,j,junctions[i][j].getPosition().row, junctions[i][j].getPosition().col,
				junctions[i][j].getInRoads()[0]->getPosition(),
				junctions[i][j].getInRoads()[1]->getPosition(),
				junctions[i][j].getInRoads()[2]->getPosition(),
				junctions[i][j].getInRoads()[3]->getPosition());
}

void JunctionManager::roadsCheck()
{
	printf("\n%d",roads[3][4][0].getNumOfCars());
}

void JunctionManager::generalCheck()
{
	for (Car c : cars)
		if (c.getExist())
			c.showPath();
}

bool JunctionManager::finish()
{
	if (carsCounter == 0) {
		printf("\nframes: %d\n",framesRestarts*MAX_NUM_OF_FRAMES+frames);
		return true;
	}
	return false;
}

void JunctionManager::move(Junction* junction)
{
	Pair from, to;
	Road* roadToGo = nullptr;
	Car* firstCarInGreenLight = junction->getFirstCarInGreenLight();
	firstCarInGreenLight->setColor(BLACK);
	from = junction->getPosition();
	to = firstCarInGreenLight->getNextJunction();
	/*printf("\n=======================\n");
	firstCarInGreenLight->showPath();
	printf("\ncurrent: (%d, %d) -> next: (%d %d)\n",
		firstCarInGreenLight->getJunction(), firstCarInGreenLight->getNextJunction());
	printf("\n=======================\n");*/
	if (from.row == to.row)
		roadToGo = (junctions[to.row][to.col].getInRoads()[from.col > to.col ? RIGHT : LEFT]);
	if (from.col == to.col)
		roadToGo = (junctions[to.row][to.col].getInRoads()[from.row > to.row ? UP : DOWN]);
	//firstCarInGreenLight->setColor(BLUE);
	
	roadToGo->addToEnd(junction->getGreenRoad()->removeFromTop());
//	firstCarInGreenLight->setIsMoving(false);
	firstCarInGreenLight->removeTopJunctionFromPath();
	carsCounter -= roadToGo->checkCarsArrival();
}

bool JunctionManager::checkIfCarCanLeave(Junction* current)
{// change this function so that it will return Car* if found, if not - NULL
	Pair from, to;
	Car* c = current->getFirstCarInGreenLight();
	
	from = current->getPosition();
	to = c->getNextJunction();
	
	if (from.row == to.row)
		if (junctions[to.row][to.col].getInRoads()[from.col > to.col ? RIGHT : LEFT]->getNumOfCars() < MAX_CARS_PER_ROAD)
			return true;
	
	if (from.col == to.col)
		if (junctions[to.row][to.col].getInRoads()[from.row > to.row ? UP : DOWN]->getNumOfCars() < MAX_CARS_PER_ROAD)
			return true;
	//printf("%d", junctions[to.row][to.col].getInRoads()[from.col > to.col ? RIGHT : LEFT]->getNumOfCars());
	
	return false;
}

void JunctionManager::drawAll() {
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			glPushMatrix();
			glTranslated(junctions[i][j].getOffset().x, junctions[i][j].getOffset().y, 0);
			junctions[i][j].drawJunction();
			junctions[i][j].paintLights();
			glPopMatrix();
		}
	}
}

void JunctionManager::moveAll() {
	for (int i = 1; i < LENGTH-1; i++) {
		for (int j = 1; j < LENGTH-1; j++) {
			if (junctions[i][j].getFirstCarInGreenLight())
				if (checkIfCarCanLeave(&junctions[i][j]))
					move(&junctions[i][j]);
				else junctions[i][j].getFirstCarInGreenLight()->setColor(RED);
			if (frames % junctions[i][j].getTimeIntervals()[junctions[i][j].getGreenRoadNum()] == 0)
				junctions[i][j].setNextGreenRoad();
			if (frames > 10000) {
				framesRestarts++;
				frames = 0;
			}
			/*for (int k = 0; k < 4; k++)
				junctions[i][j].getInRoads()[k]->endAnimation();*/
		}
	}
	frames++;
}


