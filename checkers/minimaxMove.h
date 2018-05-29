#ifndef __MINIMAX_MOVE_H__
#define __MINIMAX_MOVE_H__

#include "moveEvent.h"
#include <utility>

class MinimaxMove {
private:
	MoveEvent moveEvent;
	int score;

public:
	MinimaxMove(int sc);
	MinimaxMove(MoveEvent event, int sc);
	void setScore(int sc);
	MoveEvent getMoveEvent();
	int getScore();
};


#endif