#ifndef __MOVE_EVENT_H__
#define __MOVE_EVENT_H__

#include "defines.h"
#include "jumped.h"
#include <vector>
#include <utility>

class MoveEvent {
private:
	char sign;
	bool queenConversionStatus;
	std::pair<int,int> from;
	std::pair<int,int> to;
	std::vector<Jumped> jumped;

	void checkQueenConversion(char c, bool isQueenMoving, std::pair<int,int> moveTo);

public:
	MoveEvent();
	MoveEvent(char c, bool isQueenMoving, std::pair<int,int> moveFrom, std::pair<int,int> moveTo);
	MoveEvent(char c, bool isQueenMoving, std::pair<int,int> moveFrom, std::pair<int,int> moveTo, std::vector<Jumped> jumpedList);

	void setSign(char c);
	char getSign();
	void setQueenConversionStatus(bool queenStatus);
	bool hasBecomeQueen();
	std::pair<int,int> getFrom();
	std::pair<int,int> getTo();
	std::vector<Jumped> getJumpedList();
	void addToJumpedList(char jumpedPieceSign, bool jumpedPieceQueenStatus, std::pair<int,int> jumpedPiece);
	void resetJumpedList();
};

#endif