#include "stdafx.h"
#include "RobotMind.h"
#include "World.h"


//Mapa aldatzeko, zenbakia aldatu: 1, 2, 3, 4, 5, 7 edo 8
int RobotMind::Map = 1;

Direction RobotMind::TowardsGoal()
{
	return Up;
}