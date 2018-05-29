#include "jumped.h"

Jumped::Jumped(char c, bool qs, std::pair<int,int> jumpedPosition) : sign(c), queenStatus(qs), position(jumpedPosition) {}

char Jumped::getSign() {
	return sign;
}

bool Jumped::isQueen() {
	return queenStatus;
}

std::pair<int,int> Jumped::getPosition() {
	return position;
}