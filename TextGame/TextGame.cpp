// TextGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include "World.h"
#include "GameLogic.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <windows.h>


int main()
{
	World ourWorld("file.csv");
	Player player(ourWorld, 1, ourWorld.getP1X(), ourWorld.getP1Y(), ourWorld.getCharPlayer1());
	Player player2(ourWorld, 2, ourWorld.getP2X(), ourWorld.getP2Y(), ourWorld.getCharPlayer2());
	GameLogic game(ourWorld, player,player2);

	bool gameEnded = false;

	while (!gameEnded)
	{
		ourWorld.draw();

		gameEnded= game.processInput();
	}

    return 0;
}

