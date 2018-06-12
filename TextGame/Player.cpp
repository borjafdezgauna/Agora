#include "stdafx.h"
#include "Player.h"
#include <algorithm>
#include "World.h"

Player::Player(World& world, int id, int posX, int posY, char c)
	:m_world(world), m_id(id)
{
	m_posX = posX;
	m_posY = posY;

	m_world.set(posX, posY, c);
	

}


Player::~Player()
{
}

char Player::move(int destX, int destY)
{
	m_world.clamp(destX, destY);
	
	bool isMoney = m_world.move(m_id, m_posX,m_posY,destX,destY);
	this->m_posX = destX;
	this->m_posY = destY;
	return m_world.get(destX,destY);

}

char Player::moveUp()
{
	return move(m_posX, m_posY - 1);
}

char Player::moveDown()
{ 
	return move(m_posX, m_posY + 1);
}
char Player::moveRight()
{
	return move(m_posX+1, m_posY);
}
char Player::moveLeft()
{
	return move(m_posX -1, m_posY);
}