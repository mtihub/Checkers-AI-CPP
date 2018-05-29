#ifndef __BOARD_H__
#define __BOARD_H__

#include "defines.h"
#include "moveEvent.h"
#include "slot.h"
#include "jumped.h"
#include "status.h"
#include "boardPrinter.h"
#include <utility>

class Board {
private:
	Slot board[BOARD_HEIGHT][BOARD_WIDTH];
	Status boardStatus;
	BoardPrinter printer;
	
	void updateCount();

	void updatePossibleMovesDownwards(Slot& piece);
	void updatePossibleMovesUpwards(Slot& piece);
	void updatePossibleMovesQueen(Slot& piece);
	
	void recurseDownwards(Slot& piece, std::pair<int,int> currentPosition, std::vector<Jumped> jumpedPieces, bool hasJumped);
	void recurseUpwards(Slot& piece, std::pair<int,int> currentPosition, std::vector<Jumped> jumpedPieces, bool hasJumped);
	
public:
	Board();

	void placePieces();
		
	char getSign(std::pair<int,int> position);
	bool isQueen(std::pair<int,int> position);
	Slot getSlot(std::pair<int,int> position);
	
	Status getBoardStatus();
	char getWinner();

	bool isValidPosition(std::pair<int,int> position);
	bool isEmpty(std::pair<int,int> position);

	void updatePossibleMovesAt(Slot& piece);
	void updatePossibleMovesAt(std::pair<int,int> position);
	void updateAllPossibleMoves();

	std::vector<MoveEvent> getPossibleMovesAt(std::pair<int,int> position);

	int  movePiece(std::pair<int,int> positionFrom, std::pair<int,int> positionTo);
	void fireMoveEvent(MoveEvent event);
	int  undoMove(std::pair<int,int> moveFrom, std::pair<int,int> moveTo);
	void revertMoveEvent(MoveEvent event);

	void printAllPossibleMoves();
	void printBoard();
};

#endif