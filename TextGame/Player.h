#pragma once

class World;

class Player
{
	World& m_world;
	int m_posX, m_posY;
	int m_id;

	//esta funci�n actualiza en el mundo d�nde est� el jugador
	char move(int destX, int destY);
public:
	Player() = default;
	Player(World& world, int id, int posX, int posY, char c);
	~Player();

	//estas funciones tienen que llamar a move()
	char moveUp();
	char moveDown();
	char moveRight();
	char moveLeft();
};

