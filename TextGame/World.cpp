#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include "System.h"
#include "stdafx.h"
#include <stdio.h>
#include <istream>


World::World(int sizeX, int sizeY, char defaultValue, char coinDefaultValue, char player1DefaultValue, char player2DefaultValue)
{
	System::HideCursor();

	//set the random seed
	int seed = (time(NULL)) % 100;
	srand(seed);

	m_sizeX = sizeX;
	m_sizeY = sizeY;
	numCeldas = sizeX*sizeY;
	numCoins = numCeldas / 10;
	m_pContent = new char[numCeldas];

	for (int i = 0; i < numCeldas; i++) {
		m_pContent[i] = defaultValue;
	}

	m_defaultValue = defaultValue;
	m_coinDefaultValue = coinDefaultValue;
	playerDefaultValue1 = player1DefaultValue;
	playerDefaultValue2 = player2DefaultValue;

	addCoins(numCoins);
	m_timer.start();
	points1 = 0;
	points2 = 0;
	
}

World::World(std::string nameFile)
{
	System::HideCursor();

	std::ifstream file(nameFile);
	char firstline[512];
	int x, y;
	char c, s, v, b, w;

	int nCoin = 0;

	file.getline(firstline,512);
	sscanf_s(firstline,  "%d,%d,%c,%c,%c,%c,%c", &x, &y, &c, 1, &s, 1, &v, 1, &b, 1, &w, 1);

	playerDefaultValue1 = v;
	playerDefaultValue2= b;
	wallChar = w;

	m_defaultValue = c;
	m_coinDefaultValue = s;

	numCeldas = x*y;
	m_pContent = new char[numCeldas];
	
	int i = 0;

		for (int m = 0; m < x; m++) 
		{
			file.getline(firstline, 512);
			for (int n = 0; n < y; n++)
			{
				m_pContent[i]= firstline[n];

				if (m_pContent[i]==m_coinDefaultValue) {
					nCoin++;
				}
				
				if (m_pContent[i] == playerDefaultValue1) {
					p1x = n;
					p1y = m;
				}

				if (m_pContent[i] == playerDefaultValue2) {
					p2x = n;
					p2y = m;
				}


				i++;
			}
		}

	m_sizeX = x;
	m_sizeY = y;



	numCoins = nCoin;
	
	m_timer.start();
	points1 = 0;	
	points2 = 0;
}

World::~World()
{
	delete[] m_pContent;
}

int World::getP1X() const
{
	return p1x;
}

int World::getP1Y() const
{
	return p1y;
}



int World::getP2X() const
{
	return p2x;
}

int World::getP2Y() const 
{
	return p2y;
}


int World::getOldP1X() const
{
	return oldP1X;
}

int World::getOldP1Y() const
{
	return oldP1Y;
}



int World::getOldP2X() const
{
	return oldP2X;
}

int World::getOldP2Y() const
{
	return oldP2Y;
}

char World::getWallChar() const 
{
	return wallChar;
}


int World::getPosInArray(int x, int y) const
{
	int result = x + (y*m_sizeX);
	return result;
}


int World::getSizeX() const
{
	return m_sizeX;
}

int World::getSizeY() const
{
	return m_sizeY;
}

void World::addCoins(int n)
{
	double pos=0;

	for (int i = 0; i < n; i++)
	{
		int posEntera = rand() % (m_sizeX*m_sizeY);
		if (m_pContent[posEntera] == m_defaultValue)
		{
			m_pContent[posEntera] = m_coinDefaultValue;
		}
		else
		{
			i--;
		}
	}
}

char World::get(int x, int y) const
{
	int pos = getPosInArray(x, y);
	return m_pContent[pos];
}

void World::set(int x, int y, char value)
{
	int pos = getPosInArray(x, y);
	m_pContent[pos] = value;
}

void World::clamp(int& x, int& y) const
{
	if (x >m_sizeX-1) x = m_sizeX-1;
	else if (x < 0) x = 0;
	if (y > m_sizeY-1) y = m_sizeY-1;
	else if (y < 0) y = 0;
}

bool World::move(int playerId, int originX, int originY, int& destX, int& destY)
{
	bool isMoney = false;
	char originValue= get(originX, originY);	
	char destValue = get(destX, destY);
	
	if ((originX != destX || originY != destY) 
		&& (destValue != playerDefaultValue1 
			&& destValue != playerDefaultValue2)&& (destValue != wallChar))
	{
		if (destValue == m_coinDefaultValue)
		{
			if (originValue == playerDefaultValue1)
			{
				points1 ++;
			}
			else if (originValue == playerDefaultValue2)
			{
				points2++;
			}
		}
		set(destX, destY, originValue);
		set(originX, originY, m_defaultValue);
	}
	else
	{
		destX = originX;
		destY = originY;
	}
	switch (playerId)
	{
	case 1:
		oldP1X = p1x; oldP1Y = p1y;
		p1x = destX; p1y = destY;
		break;
	case 2:
	default:
		oldP2X = p2x; oldP2Y = p2y;
		p2x = destX; p2y = destY;
		break;
	}

	return isMoney;
}

void World::draw()
{
	if (points1 + points2 == numCoins)
	{
		ShowEnd();
	}
	else
	{
		if (!m_bMazeAlreadyDrawn)
		{
			DrawMaze();
			m_bMazeAlreadyDrawn = true;
		}
		else
		{
			int x, y;
			x = getP1X(); y = getP1Y();
			DrawMazePos(x, y);
			x = getOldP1X(); y = getOldP1Y();
			DrawMazePos(x, y);
			x = getP2X(); y = getP2Y();
			DrawMazePos(x, y);
			x = getOldP2X(); y = getOldP2Y();
			DrawMazePos(x, y);

			//Points
			System::SetTextColor(ConsoleColor::Black, ConsoleColor::White);
			System::SetCursorPos(10, m_sizeY + 3);
			std::cout << "  " << points1 << "  ";
			System::SetCursorPos(10, m_sizeY + 4);
			std::cout << "  " << points2 << "  ";

			//Time
			System::SetTextColor(ConsoleColor::Black, ConsoleColor::White);
			System::SetCursorPos(7, m_sizeY + 2);
			std::cout << m_timer.getElapsedTime() << "   ";
		}
	}
}

void World::DrawMazePos(int x, int y)
{
	System::SetCursorPos(x+1, y+1);
	char c= get(x, y);
	if (c == m_coinDefaultValue)
		System::SetTextColor(ConsoleColor::Yellow);
	else if (c == wallChar)
		System::SetTextColor(ConsoleColor::Red,ConsoleColor::Red);
	else if (c == playerDefaultValue1)
		System::SetTextColor(ConsoleColor::White,ConsoleColor::Blue);
	else if (c == playerDefaultValue2)
		System::SetTextColor(ConsoleColor::White, ConsoleColor::Green);
	else System::SetTextColor(ConsoleColor::Black);

	std::cout << c;
}

void World::DrawMazeLine(int y)
{
	System::SetTextColor(ConsoleColor::Red, ConsoleColor::Red);
	std::cout << "*";
	for (int x = 0; x < m_sizeX; x++)
	{
		DrawMazePos(x, y);
	}
	System::SetTextColor(ConsoleColor::Red, ConsoleColor::Red);
	std::cout << "*\n";
}

void World::DrawMaze()
{
	System::Cls();
	System::SetTextColor(ConsoleColor::Red, ConsoleColor::Red);
	for (int a = 0; a < m_sizeX + 2; a++)
	{
		std::cout << "*";
	}
	std::cout << "\n";
	for (int j = 0; j < m_sizeY; j++)
	{
		DrawMazeLine(j);
	}
	System::SetTextColor(ConsoleColor::Red, ConsoleColor::Red);
	for (int b = 0; b < m_sizeX + 2; b++)
	{
		std::cout << "*";
	}
	System::SetTextColor(ConsoleColor::White);
	std::cout << std::fixed;
	std::cout.precision(2);
	std::cout << "\nTime = " << m_timer.getElapsedTime() << " \n";
	System::SetTextColor(ConsoleColor::Blue);
	std::cout << "Player1 =   ";
	System::SetTextColor(ConsoleColor::White, ConsoleColor::White);
	std::cout << points1;
	System::SetTextColor(ConsoleColor::Green);
	std::cout << "\nPlayer2 =   ";
	System::SetTextColor(ConsoleColor::Black, ConsoleColor::White);
	std::cout << points2;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void World::ShowEnd()
{
	double time = m_timer.getElapsedTime();
	int aux;
	if (points1 < points2) aux = 2;
	else if (points1> points2) aux = 1;
	else aux = 0;

	System::Cls();

	if (aux == 0)
	{
		std::cout << "\nEmpate!!!!!! \nTiempo final: " << time;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
	else
	{
		std::cout << "\nEnhorabuena ha ganado el Player " << aux << "!!!!!!! \nTiempo final: " << time;
		std::cout << "\nTotal monedas Player1: " << points1;
		std::cout << "\nTotal monedas Player2: " << points2;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

char World::getCharPlayer1() const
{
	return playerDefaultValue1;
}
char World::getCharPlayer2() const
{
	return playerDefaultValue2;
}
char World::getCharDefault() const
{
	return m_defaultValue;
}