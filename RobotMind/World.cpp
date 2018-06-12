#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>

#include "stdafx.h"
#include <stdio.h>
#include <istream>
#include "../OpenGLRenderer/renderer.h"
#include "../OpenGLRenderer/collada-model.h"
#include "../OpenGLRenderer/basic-shapes.h"
#include "../OpenGLRenderer/material.h"
#include "../OpenGLRenderer/mesh.h"

World::World(std::string nameFile)
{
	std::ifstream file(nameFile);
	char firstline[512];

	file.getline(firstline,512);
	sscanf_s(firstline,  "%d,%d,%c,%c,%c,%c"
		, &m_sizeX, &m_sizeY
		, &m_emptyCharValue, 1
		, &m_robotCharValue, 1
		, &m_targetCharValue, 1
		, &m_wallCharValue, 1);

	m_numCells = m_sizeX*m_sizeY;
	m_pContent = new char[m_numCells];
	
	int i = 0;

		for (int m_y = 0; m_y < m_sizeY; m_y++) 
		{
			file.getline(firstline, 512);
			for (int m_x = 0; m_x < m_sizeX; m_x++)
			{
				m_pContent[i]= firstline[m_x];

				if (m_pContent[i] == m_robotCharValue)
				{
					addRobot(m_x, m_y);
				}
				else if (m_pContent[i] == m_wallCharValue)
				{
					addBox(m_x, m_y);
				}
				else if (m_pContent[i] == m_targetCharValue)
				{
					addTarget(m_x, m_y);
				}

				i++;
			}
		}
}

World::~World()
{
	delete[] m_pContent;
}

int World::getPosInArray(int m_x, int m_y) const
{
	int result = m_x + (m_y*m_sizeX);
	result = std::max(0, std::min(m_sizeX*m_sizeY, result));
	return result;
}

char World::get(Position pos) const
{
	return m_pContent[getPosInArray(pos.x(),pos.y())];
}
void World::set(Position pos, char newContent)
{
	m_pContent[getPosInArray(pos.x(), pos.y())] = newContent;
}

void World::swapContent(Position p1, Position p2)
{
	char c1 = get(p1);
	set(p1, get(p2));
	set(p2, c1);
}


void World::addRobot(int x, int y)
{
	m_robotX = x;
	m_robotY = y;
	CGraphicObject* pRobot = new CColladaModel("Robot","../scenes/R2D2/R2D2.dae");
	if (pRobot)
	{
		pRobot->addLocalOffset(Vector3D((double)m_robotX, 0.0, (double)m_robotY));
		CRenderer::get()->addGraphicObject(pRobot);
	}
}

void World::addTarget(int x, int y)
{
	m_targetX = x;
	m_targetY = y;
	static int boxCount = 0;
	CBox* pBox = new CBox(string("target"));
	CMaterial* pBoxMaterial = new CTranslucentMaterial(string("translucent-green.tga"));
	vector<CMesh*>& meshes = pBox->getMeshes();
	for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
	{
		(*mesh)->setMaterial(pBoxMaterial);
	}
	pBox->addLocalOffset(Vector3D((double)x, 0.0, (double)y));
	CRenderer::get()->addGraphicObject(pBox);
}

void World::addBox(int x, int y)
{
	static int boxCount = 0;
	CBox* pBox = new CBox(string("wall")+std::to_string(boxCount));
	CMaterial* pBoxMaterial = new CSimpleTLMaterial(string("box.png"));
	vector<CMesh*>& meshes= pBox->getMeshes();
	for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
	{
		(*mesh)->setMaterial(pBoxMaterial);
	}
	pBox->addLocalOffset(Vector3D((double)x, 0.0, (double)y));
	CRenderer::get()->addGraphicObject(pBox);
}

bool World::isThereWall(Direction dir)
{
	int robotX = m_robotX;
	int robotY = m_robotY;
	switch (dir)
	{
	case Up: robotX++; break;
	case Down: robotX--; break;
	case Left: robotY--; break;
	case Right: robotY++; break;
	}

	return get(Position(robotX, robotY))==m_wallCharValue;
}

bool World::tryMove(Direction dir)
{
	int robotX = m_robotX;
	int robotY = m_robotY;
	switch (dir)
	{
		case Up: robotX++; break;
		case Down: robotX--; break;
		case Left: robotY--; break;
		case Right: robotY++; break;
	}

	if (get(Position(robotX,robotY)) != m_wallCharValue)
	{
		swapContent(Position(robotX, robotY), Position(m_robotX, m_robotY));
		m_robotX = robotX;
		m_robotY = robotY;
		return true;
	}
	return false;
}

Position World::getRobotRelPosToTarget()
{
	return Position(m_targetX - m_robotX, m_targetY - m_robotY);
}