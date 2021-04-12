#pragma once
#define MAX_NUM_OF_FRAMES 10000
#define CAR_SIZE 3
#define NUM_OF_DIRECTIONS 4
#define NUM_OF_LANES 4
#define NUM_OF_ROADS 4
#define NUM_OF_LIGHTS 4
#define GAP 0.2*0.5
#define SMALL_GAP GAP/2
#define BACK_OF_ROAD 1.7
#define SPEED 0.0007
#define TURNS_GAP 1.0/6
#define LIGHTS_LOCATION 1.0/3
#define LENGTH 5
#define JUNCTION_SIZE 2
#define NUM_OF_JUNCTIONS LENGTH * LENGTH
#define NUM_OF_ROADS NUM_OF_JUNCTIONS * 4
#define MAX_CARS_PER_ROAD 12
#define NUM_OF_CARS LENGTH*20
#define FRAME_PER_CAR 1000
//#define NUM_OF_CARS 3

#define WHITE {1,1,1}
#define BLACK {0,0,0}
#define RED {1,0,0}
#define GREEN {0,1,0}
#define BLUE {0,0,1}

#include "vector"
#include <Windows.h>
using namespace std;

enum directions { UP, RIGHT, DOWN, LEFT };

struct point{
	double x;
	double y;
}typedef Point;

 struct pair{
	int row;
	int col;
}typedef Pair;

 struct color {
	 double r;
	 double g;
	 double b;
 }typedef Color;