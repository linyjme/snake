#pragma once
#include <iostream>
#include "wall.h"

using namespace std;

class Food
{
public:
	// …Ë÷√ ≥ŒÔ
	Food(Wall& tempWall);

	void setFood();

	int foodX;
	int foodY;

	Wall& wall;
};