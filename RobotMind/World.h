#pragma once
#include "../WindowsUtils/Timer.h"
#include <string>
#include "DirPos.h"

class World
{
	//representation of the world's contents
	char* m_pContent;
	
	char m_emptyCharValue;
	char m_robotCharValue;
	char m_wallCharValue;
	char m_targetCharValue;

	int m_sizeX, m_sizeY;

	int m_numCells;

	int m_robotX, m_robotY;
	int m_targetX, m_targetY;
	
	int getPosInArray(int m_x, int m_y) const;
	char get(Position pos) const;
	void set(Position pos, char newContent);
	void swapContent(Position p1, Position p2);

	void addRobot(int m_x, int m_y);
	void addBox(int m_x, int m_y);
	void addTarget(int m_x, int m_y);
public:

	World(std::string nameFile);
	~World();

	Position getRobotPos() { return Position(m_robotX, m_robotY); }
	int getRobotX() { return m_robotX; }
	int getRobotY() { return m_robotY; }
	int getSizeX() const { return m_sizeX; }
	int getSizeY() const { return m_sizeY; }

	Position getRobotRelPosToTarget();

	bool robotOverTarget()
	{
		return m_robotX == m_targetX && m_robotY == m_targetY;
	}

	bool tryMove(Direction dir);
	bool isThereWall(Direction dir);
};