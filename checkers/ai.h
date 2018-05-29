#ifndef __AI_H__
#define __AI_H__

#include "defines.h"
#include "board.h"
#include "minimaxMove.h"
#include "status.h"
#include <vector>
#include <utility>

class AI {
private:
	char aiSign;
	char humanSign;
	int  treeDepth;

	MinimaxMove getEndGameMove(char winner);
	MinimaxMove getRecursionCutoffMove(Board *currentGameBoard, Status initialStatus);
	MinimaxMove minimax(Board *gameBoard, Status initialStatus, char player, int currentDepth, int maxDepth);

public:
	AI(char ai, char human);
	MoveEvent makeMove(Board *gameBoard);
};

#endif