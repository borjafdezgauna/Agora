#pragma once

#include <vector>
#include "DirPos.h"

class Step
{
	Position pos;
	Direction dir;
public:
	Step(Position p, Direction d)
	{
		pos = p;
		dir = d;
	}
	bool operator==(Step& s)
	{
		return pos == s.pos && dir == s.dir;
	}
};

class World;

enum State {FollowingOrders,LookingForAlternative};

class RobotMind
{
	std::string m_state;
	std::string m_lastMovement;
	World* m_pWorld;

	Direction RandomDirection();
	Direction TowardsGoal();

	bool ThereIsWall(Direction dir);

	bool GoalIsAbove();
	bool GoalIsBelow();
	bool GoalIsToTheRight();
	bool GoalIsToTheLeft();

	bool m_bLookingForAlternative = false;
	Direction m_targetDirection;
	Direction m_currentAlternative;

	Direction FindAlternative(Direction dir);
	Direction ChooseDirection();
	Direction OppositeDirection(Direction dir);
	void SetState(State state);
public:
	RobotMind(World* pWorld);
	virtual ~RobotMind();

	Position TakeStep();
	std::string GetLastDirection() { return m_lastMovement; }
	std::string GetState() { return m_state; }
};

