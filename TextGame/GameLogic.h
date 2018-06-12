#pragma once

class Player;
class World;

class GameLogic
{
	Player& m_player;
	Player& m_player2;
	World& m_world;
public:
	GameLogic(World& world, Player& player, Player& player2);
	~GameLogic();

	bool processInput();
};

