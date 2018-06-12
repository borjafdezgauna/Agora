#include "stdafx.h"
#include "RobotMind.h"
#include "World.h"

Direction RobotMind::TowardsGoal()
{
	if (GoalIsAbove())
	{
		if (!ThereIsWall(Up))
			return Up;

		return FindAlternative(Up);
	}

	if (GoalIsBelow())
	{
		if (!ThereIsWall(Down))
			return Down;

		return FindAlternative(Down);
	}

	if (GoalIsToTheRight())
	{
		if (!ThereIsWall(Right))
			return Right;

		return FindAlternative(Right);
	}

	if (GoalIsToTheLeft())
	{
		if (!ThereIsWall(Left))
			return Left;

		return FindAlternative(Left);
	}
}