#include "stdafx.h"
#include "RobotMind.h"
#include "World.h"

Direction RobotMind::TowardsGoal()
{
	//if (GoalIsAbove())
	//	return Up;

	return RandomDirection();
}