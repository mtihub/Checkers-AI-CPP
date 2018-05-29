#include "moveEvent.h"

MoveEvent::MoveEvent() {}

MoveEvent::MoveEvent(char c, bool isQueenMoving, std::pair<int,int> moveFrom, std::pair<int,int> moveTo) 
					: sign(c), from(moveFrom), to(moveTo) { checkQueenConversion(c, isQueenMoving, moveTo); }

MoveEvent::MoveEvent(char c, bool isQueenMoving, std::pair<int,int> moveFrom, std::pair<int,int> moveTo, std::vector<Jumped> jumpedList) 
					: sign(c), from(moveFrom), to(moveTo), jumped(jumpedList) { checkQueenConversion(c, isQueenMoving, moveTo); }

void MoveEvent::checkQueenConversion(char c, bool isQueenMoving, std::pair<int,int> moveTo) {
	if (!isQueenMoving) {
		if (moveTo.first == 0 && c == O_SIGN) {
			queenConversionStatus = true;
		}
		else if (moveTo.first == BOARD_HEIGHT-1 && c == X_SIGN) {
			queenConversionStatus = true;
		} 
		else {
			queenConversionStatus = false;
		}
	} 
	else {
		queenConversionStatus = false;
	}
}

void MoveEvent::setSign(char c) {
	sign = c;
}

char MoveEvent::getSign() {
	return sign;
}

void MoveEvent::setQueenConversionStatus(bool queenStatus) {
	queenConversionStatus = queenStatus;
}

bool MoveEvent::hasBecomeQueen() {
	return queenConversionStatus;
}

std::pair<int,int> MoveEvent::getFrom() {
	return from;
}

std::pair<int,int> MoveEvent::getTo() {
	return to;
}

std::vector<Jumped> MoveEvent::getJumpedList() {
	return jumped;
}

void MoveEvent::addToJumpedList(char jumpedPieceSign, bool jumpedPieceQueenStatus, std::pair<int,int> jumpedPosition) {
	Jumped jumpedPiece(jumpedPieceSign, jumpedPieceQueenStatus, jumpedPosition);
	jumped.push_back(jumpedPiece);
}

void MoveEvent::resetJumpedList() {
	jumped.clear();
}