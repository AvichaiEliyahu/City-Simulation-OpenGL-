#include "JunctionManager.h"

void JunctionManager::initJunctions() {
	int flip = -1;
	int iOffset, jOffset;
	int iIndex, jIndex;
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
	FILE* timesFile = fopen(TIMES_FILENAME, "r");
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
	for (int i = 0; i < NUM_OF_CARS; i++) {
		cars[i].setCarId(i);
		cars[i].calcPath();
	}
}

void JunctionManager::putCarsOnRoads() {
	FILE* infoFile = fopen(INFO_FILENAME, "r");
	if (!infoFile) {
		printf("\nerror opening info file!\n");
		return;
	}
	int i;
	int roadArrayX, roadArrayY, roadArrayZ;
	int targetX, targetY;
	for (i = 0; i < NUM_OF_CARS; i++) {
		fscanf(infoFile, "%d %d %d %d %d",
			&roadArrayX, &roadArrayY, &roadArrayZ, &targetX, &targetY);
		if (roads[roadArrayX][roadArrayY][roadArrayZ].addToEnd(&cars[i], true)) {
			cars[i].setExist(true);
			cars[i].setColor(BLACK);
			Pair currentJunc, target;
			currentJunc.row = roadArrayX;
			currentJunc.col = roadArrayY;
			target.row = targetX;
			target.col = targetY;
			cars[i].setJunction(currentJunc);
			cars[i].setFinalTarget(target);
			carsCounter++;
		}
	}
	fclose(infoFile);
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
}

void JunctionManager::writeToFile(int stuckCars) {
	FILE* timesFile = fopen(TIMES_FILENAME, "a");
	if (!timesFile) {
		printf("\nerror opening times file!\n");
		return;
	}
	fprintf(timesFile,"%d", stuckCars);
	fclose(timesFile);
}

bool JunctionManager::deadlockCheck() {
	for (int i = 1; i < LENGTH - 1; i++)
		for (int j = 1; j < LENGTH - 1; j++)
			for (int k = 0; k < 4; k++) 
				if (junctions[i][j].getInRoads()[k]->getFirstCar()!=NULL)
					if (junctions[i][j].getInRoads()[k]->getFirstCar()->getStuck() == false)
						return false;
	return true;


}

void JunctionManager::writeRoadsStuckToFile() {
	FILE* stuckFile = fopen(STUCK_FILENAME, "w");
	if (!stuckFile) {
		printf("\nerror opening times file!\n");
		return;
	}
	for (int i = 1; i < LENGTH - 1; i++) {
		for (int j = 1; j < LENGTH - 1; j++) {
			fprintf(stuckFile, "%d %d %d %d\n",
				junctions[i][j].getInRoads()[0]->getNumOfStuckCars(),
				junctions[i][j].getInRoads()[1]->getNumOfStuckCars(),
				junctions[i][j].getInRoads()[2]->getNumOfStuckCars(),
				junctions[i][j].getInRoads()[3]->getNumOfStuckCars());
		}
	}
	fclose(stuckFile);
}

bool JunctionManager::finish()
{
	if (carsCounter < MAX_CARS_PER_ROAD) {
		writeToFile(stuck);
		writeRoadsStuckToFile();
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
	
	if (from.row == to.row)
		roadToGo = (junctions[to.row][to.col].getInRoads()[from.col > to.col ? RIGHT : LEFT]);
	if (from.col == to.col)
		roadToGo = (junctions[to.row][to.col].getInRoads()[from.row > to.row ? UP : DOWN]);
	
	roadToGo->addToEnd(junction->getGreenRoad()->removeFromTop(),false);
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

void JunctionManager::carLeave(int i, int j)
{
	junctions[i][j].getFirstCarInGreenLight()->setStuck(false);
	if (junctions[i][j].getGreenRoad()->getCurrentFrames() < junctions[i][j].getTimeIntervals()[junctions[i][j].getGreenRoadNum()]) {
		move(&junctions[i][j]);
		junctions[i][j].getGreenRoad()->setCurrentFrames(junctions[i][j].getGreenRoad()->getCurrentFrames() + FRAME_PER_CAR);
	}
}

void JunctionManager::carStuck(int i, int j)
{
	junctions[i][j].getFirstCarInGreenLight()->setColor(RED);
	if (junctions[i][j].getFirstCarInGreenLight()->changeStuck()) {
		stuck++;
		junctions[i][j].getGreenRoad()->increaseNumOfStuckCars();
	}
	if (deadlockCheck()) {
		writeToFile(-1);
		exit(0);
	}
}

void JunctionManager::checkAndChangeGreenLight(int i, int j)
{
	if (frames % junctions[i][j].getTimeIntervals()[junctions[i][j].getGreenRoadNum()] == 0) {
		junctions[i][j].setNextGreenRoad();
		junctions[i][j].getGreenRoad()->setCurrentFrames(0);
	}
}

void JunctionManager::framesCheck()
{
	if (frames > MAX_NUM_OF_FRAMES) {
		framesRestarts++;
		frames = 0;
	}
}

void JunctionManager::moveAll() {
	for (int i = 1; i < LENGTH-1; i++)
		for (int j = 1; j < LENGTH-1; j++) {
			if (junctions[i][j].getFirstCarInGreenLight())
				if (checkIfCarCanLeave(&junctions[i][j]))
					carLeave(i, j);
				else
					carStuck(i, j);
			checkAndChangeGreenLight(i, j);
			framesCheck();
		}
	frames++;
}


