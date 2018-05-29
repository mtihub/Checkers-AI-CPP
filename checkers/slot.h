#ifndef __SLOT_H__
#define __SLOT_H__

#include "moveEvent.h"
#include <vector>
#include <stack>
#include <utility>

class Slot {
private:
	char sign;
	bool queenStatus;
	std::pair<int,int> position;
	std::vector<MoveEvent> possibleMoves;
	std::stack<MoveEvent> history;

public:
	Slot();
	Slot(char c);
	Slot(char c, int x, int y);
	Slot(char c, bool qs, int x, int y);
	Slot(char c, std::pair<int,int> slotPosition);

	void setSign(char c);
	void setQueenStatus(bool qs);
	void setPosition(std::pair<int,int> newPosition);
	
	void setAttributes(char c, bool qs, int x, int y);


	char getSign();
	bool isQueen();
	std::pair<int,int> getPosition();	

	std::vector<MoveEvent> getMoveEventTo(std::pair<int,int> requestedMove);

	void addToPossibleMoves(std::pair<int,int> from, std::pair<int,int> to);
	void addToPossibleMoves(std::pair<int,int> from, std::pair<int,int> to, std::vector<Jumped> jumpedList);
	void resetPossibleMoves();

	std::vector<MoveEvent> getPossibleMoves();
 
	//void addToHistory(std::pair<int,int> from, std::pair<int,int> to);
	void addToHistory(MoveEvent);
	MoveEvent popHistory();

	void clear();

	//void updateAfterMove(MoveEvent moveEvent);
	
	void printPossibleMoves();
};

#endif