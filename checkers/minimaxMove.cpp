#include "minimaxMove.h"

MinimaxMove::MinimaxMove(int sc) : score(sc) {}
MinimaxMove::MinimaxMove(MoveEvent event, int sc) : moveEvent(event), score(sc) {}

void MinimaxMove::setScore(int sc) {
	score = sc;
}

int MinimaxMove::getScore() {
	return score;
}

MoveEvent MinimaxMove::getMoveEvent() {
	return moveEvent;
}