#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "board.h"
#include "moveEvent.h"
#include "human.h"
#include "ai.h"

class Game {
private:
	Board *gameBoard;
	Human *human;
	AI *ai;
	char currentTurn;
	char winner;

public:
	Game();
	~Game();
	void play();
	void toggleTurn();
};

#endif