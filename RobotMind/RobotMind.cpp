#include "stdafx.h"
#include "RobotMind.h"
#include "World.h"

RobotMind::RobotMind(World* pWorld)
{
	m_pWorld = pWorld;
	SetState(FollowingOrders);
}


RobotMind::~RobotMind()
{
}

Direction RobotMind::RandomDirection()
{
	return static_cast<Direction>(Direction::Up + rand() % 4);
}


bool RobotMind::GoalIsAbove()
{
	Position relPos = m_pWorld->getRobotRelPosToTarget();
	return relPos.x() > 0;
}
bool RobotMind::GoalIsBelow()
{
	Position relPos = m_pWorld->getRobotRelPosToTarget();
	return relPos.x() < 0;
}
bool RobotMind::GoalIsToTheRight()
{
	Position relPos = m_pWorld->getRobotRelPosToTarget();
	return relPos.y() > 0;
}
bool RobotMind::GoalIsToTheLeft()
{
	Position relPos = m_pWorld->getRobotRelPosToTarget();
	return relPos.y() < 0;
}


bool RobotMind::ThereIsWall(Direction dir)
{
	return m_pWorld->isThereWall(dir);
}


Position RobotMind::TakeStep()
{
	Position pos = m_pWorld->getRobotPos();
	Direction dir;

	if (!m_bLookingForAlternative)
		dir= ChooseDirection();
	else
	{
		if (ThereIsWall(m_targetDirection))
		{
			if (ThereIsWall(m_currentAlternative))
				m_currentAlternative = OppositeDirection(m_currentAlternative);
			dir= m_currentAlternative;
		}
		else
		{
			SetState(FollowingOrders);
			m_bLookingForAlternative = false;
			dir = m_targetDirection;
		}
	}

	Step step = Step(pos, dir);
	
	m_pWorld->tryMove(dir);

	Position newPos = m_pWorld->getRobotPos();

	return newPos-pos;
}

std::string AsString(Direction dir)
{
	if (dir == Up) return "Up";
	if (dir == Down) return "Down";
	if (dir == Left) return "Left";
	return "Right";
}

void RobotMind::SetState(State state)
{
	switch (state)
	{
	case FollowingOrders:
		m_state = "Robot following orders";
		break;
	case LookingForAlternative:
		m_state = "Robot looking for an alternative path";
		break;
	}
}

Direction RobotMind::OppositeDirection(Direction dir)
{
	if (dir == Up) return Down;
	if (dir == Down) return Up;
	if (dir == Left) return Right;
	return Left;
}

Direction RobotMind::FindAlternative(Direction dir)
{
	m_bLookingForAlternative = true;
	m_targetDirection = dir;
	Position relPos = m_pWorld->getRobotRelPosToTarget();
	SetState(LookingForAlternative);

	if (m_targetDirection == Up)
	{
		if (GoalIsToTheRight())
			m_currentAlternative = Right;
		else m_currentAlternative = Left;
	}
	else if (m_targetDirection == Down)
	{
		if (GoalIsToTheRight())
			m_currentAlternative = Right;
		else m_currentAlternative = Left;
	}
	else if (m_targetDirection == Left)
	{
		if (GoalIsAbove())
			m_currentAlternative = Up;
		else m_currentAlternative = Down;
	}
	else if (m_targetDirection == Right)
	{
		if (GoalIsBelow())
			m_currentAlternative = Up;
		else m_currentAlternative = Down;
	}

	return m_currentAlternative;
}


Direction RobotMind::ChooseDirection()
{
	Direction myDirection = TowardsGoal();

	m_lastMovement = AsString(myDirection);

	return myDirection;
}