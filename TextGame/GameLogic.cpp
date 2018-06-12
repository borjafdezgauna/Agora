#include "stdafx.h"
#include <iostream>
#include <conio.h>

#include "GameLogic.h"
#include "World.h"
#include "Player.h"

GameLogic::GameLogic(World& world, Player& player, Player& player2)
	:m_world(world), m_player(player), m_player2(player2)
{

}


GameLogic::~GameLogic()
{
}

bool GameLogic::processInput()
{
	if ((m_world.points1 + m_world.points2) == m_world.numCoins) {
		return true;
	}
	if (!_kbhit()) return false;
	while (_kbhit())
	{
		char c = _getch();
		switch (c)
		{

		case '8':
			m_player2.moveUp(); break;
		case '2':
			m_player2.moveDown(); break;
		case '6':
			m_player2.moveRight(); break;
		case '4':
			m_player2.moveLeft(); break;
		case 'w':
		case 'W':
			m_player.moveUp(); break;
		case 's':
		case 'S':
			m_player.moveDown(); break;
		case 'd':
		case 'D':
			m_player.moveRight(); break;
		case 'a':
		case 'A':
			m_player.moveLeft(); break;
		case 27:
			return true;
		}
	}
	return false;
}