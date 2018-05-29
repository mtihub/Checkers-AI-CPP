#include "board.h"
#include <iostream>

//----------------------------------------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------------------------------------
Board::Board() : boardStatus(INIT_X_COUNT, 0, INIT_O_COUNT, 0, INIT_X_COUNT, INIT_O_COUNT) {
	//boardStatus = Status(8, 0, 8, 0, 8, 8);

	placePieces();

	// for (int i = 0; i < BOARD_HEIGHT; i++) {
	// 	for (int j = 0; j < BOARD_WIDTH; j++) {
	// 		board[i][j] = Slot(NO_SIGN, i, j);
	// 	}
	// }
	// board[6][1].setSign(O_SIGN);
	// board[4][3].setSign(O_SIGN);
	// board[2][5].setSign(O_SIGN);
	// board[4][5].setSign(O_QUEEN_SIGN);
	// board[1][6].setSign(X_SIGN);
	// board[1][2].setSign(X_SIGN);

	// board[4][3].setSign(X_SIGN);
	// board[2][5].setSign(X_SIGN);
	// board[2][7].setSign(X_SIGN);
	// board[5][2].setSign(O_SIGN);
	// board[5][4].setSign(O_SIGN);
	// board[6][1].setSign(O_SIGN);
	// board[6][3].setSign(O_SIGN);	
	// board[6][5].setSign(O_SIGN);	
	// board[4][7].setSign(O_SIGN);	
	// board[7][0].setSign(O_SIGN);
	// board[7][4].setSign(O_SIGN);
	// board[7][2].setSign(O_SIGN);
	// board[7][6].setSign(O_SIGN);	

}

void Board::placePieces() {
	// TOP: X
	for (int i = 0; i < OCCUPIED_ROWS; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i%2 == 0) {
				if (j%2 == 0) {
					board[i][j].setAttributes(NO_SIGN, false, i, j);
				}
				else {
					board[i][j].setAttributes(X_SIGN, false, i, j);
				}
			}
			else {
				if (j%2 == 0) {
					board[i][j].setAttributes(X_SIGN, false, i, j);
				}
				else {
					board[i][j].setAttributes(NO_SIGN, false, i, j);
				}
			}
		}
	}

	// MIDDLE: EMPTY
	for (int i = OCCUPIED_ROWS; i < BOARD_HEIGHT-OCCUPIED_ROWS; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			board[i][j].setAttributes(NO_SIGN, false, i, j);
		}
	}

	// BOTTOM: O
	for (int i = BOARD_HEIGHT-OCCUPIED_ROWS; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i%2 == 0) {
				if (j%2 == 0) {
					board[i][j].setAttributes(NO_SIGN, false, i, j);
				}
				else {
					board[i][j].setAttributes(O_SIGN, false, i, j);
				}
			}
			else {
				if (j%2 == 0) {
					board[i][j].setAttributes(O_SIGN, false, i, j);
				}
				else {
					board[i][j].setAttributes(NO_SIGN, false, i, j);
				}
			}
		}
	}
}


//----------------------------------------------------------------------------------------------------------
// Getters
//----------------------------------------------------------------------------------------------------------
char Board::getSign(std::pair<int,int> position) {
	if (isValidPosition(position)) {
		return (board[position.first][position.second]).getSign();
	}
	else {
		return NO_SIGN;
	}
}

bool Board::isQueen(std::pair<int,int> position) {
	if (isValidPosition(position)) {
		return (board[position.first][position.second]).isQueen();
	}
	else {
		return false;
	}
}

Slot Board::getSlot(std::pair<int,int> position) {
	return board[position.first][position.second];
}

Status Board::getBoardStatus() {
	return boardStatus;
}


//----------------------------------------------------------------------------------------------------------
// Position Validity Check
//----------------------------------------------------------------------------------------------------------
bool Board::isValidPosition(std::pair<int,int> position) {
	if (position.first < 0 || position.first > (BOARD_HEIGHT-1)) {
		return false;
	}
	if (position.second < 0 || position.second > (BOARD_HEIGHT-1)) {
		return false;
	}
	return true;
}

bool Board::isEmpty(std::pair<int,int> position) {
	if (!isValidPosition(position)) {
		return false;
	}

	if ((board[position.first][position.second]).getSign() == NO_SIGN) {
		return true;
	}
	else {
		return false;
	}
}


//----------------------------------------------------------------------------------------------------------
// Check Game Completion
//----------------------------------------------------------------------------------------------------------
char Board::getWinner() {
	if (boardStatus.getTotalXCount() == 0) {
		return O_SIGN;
	}
	else if (boardStatus.getTotalOCount() == 0) {
		return X_SIGN;
	}
	else {
		return NO_SIGN;
	}
}



//----------------------------------------------------------------------------------------------------------
// Update Piece Counters
//----------------------------------------------------------------------------------------------------------
void Board::updateCount() {
	boardStatus.resetAllCounts();

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			switch ((board[i][j]).getSign()) {
				case X_SIGN:
					if(!(board[i][j]).isQueen()) {
						boardStatus.incrementXCount();
					}
					else {
						boardStatus.incrementXQueenCount();
					}
					boardStatus.incrementTotalXCount();
					break;
				
				case O_SIGN:
					if(!(board[i][j]).isQueen()) {
						boardStatus.incrementOCount();
					}
					else {
						boardStatus.incrementOQueenCount();
					}
					boardStatus.incrementTotalOCount();
					break;
			}
		}
	}
}


//----------------------------------------------------------------------------------------------------------
// Update Potential Move(s) for a Slot
//----------------------------------------------------------------------------------------------------------
void Board::updateAllPossibleMoves() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			updatePossibleMovesAt(board[i][j]);
		}
	}
}


void Board::updatePossibleMovesAt(std::pair<int,int> position) {
	updatePossibleMovesAt(board[position.first][position.second]);
}

void Board::updatePossibleMovesAt(Slot& piece) {
	piece.resetPossibleMoves();
	
	if ((piece.getSign() == X_SIGN) && !(piece.isQueen())) {
		updatePossibleMovesDownwards(piece);
	}
	else if ((piece.getSign() == O_SIGN)  && !(piece.isQueen())) {
		updatePossibleMovesUpwards(piece);
	}
	else if ((piece.getSign() == X_SIGN || piece.getSign() == O_SIGN) && (piece.isQueen())) {
		updatePossibleMovesQueen(piece);
	}
}

// **** Moves are saves as MoveEvent that holds sign, queenStatus, position, and jumped pieces information ****
// **** Jumped pieces object holds the sign, queenStatus, and the position of the piece that was jumped ****

void Board::updatePossibleMovesDownwards(Slot& piece) {	
	std::vector<Jumped> jumpedPieces;
	recurseDownwards(piece, piece.getPosition(), jumpedPieces, false);
}

void Board::updatePossibleMovesUpwards(Slot& piece) {
	std::vector<Jumped> jumpedPieces;
	recurseUpwards(piece, piece.getPosition(), jumpedPieces, false);
}

void Board::updatePossibleMovesQueen(Slot& piece) {
	std::vector<Jumped> jumpedPieces;
	recurseDownwards(piece, piece.getPosition(), jumpedPieces, false);
	recurseUpwards(piece, piece.getPosition(), jumpedPieces, false);
}

// Recursive check downwards and update the potential moves
void Board::recurseDownwards(Slot& piece, std::pair<int,int> currentPosition, std::vector<Jumped> jumpedPieces, bool hasJumped) {
	std::pair<int,int> bottomLeft     = std::make_pair(currentPosition.first+1, currentPosition.second-1);
	std::pair<int,int> bottomRight    = std::make_pair(currentPosition.first+1, currentPosition.second+1);
	std::pair<int,int> bottomFarLeft  = std::make_pair(currentPosition.first+2, currentPosition.second-2);
	std::pair<int,int> bottomFarRight = std::make_pair(currentPosition.first+2, currentPosition.second+2);

	if (isValidPosition(bottomLeft)) {
		if (!hasJumped) {
			if (isEmpty(bottomLeft)) {
				piece.addToPossibleMoves(piece.getPosition(), bottomLeft);
			}
		}
		
		// if ( (((piece.getSign() == X_SIGN || piece.getSign() == X_QUEEN_SIGN) && (getSign(bottomLeft) == O_SIGN || getSign(bottomLeft) == O_QUEEN_SIGN)) ||
		// 	 ((piece.getSign() == O_QUEEN_SIGN) && (getSign(bottomLeft) == X_SIGN || getSign(bottomLeft) == X_QUEEN_SIGN))) && 
		// 	 (isEmpty(bottomFarLeft)) ) {
		if ( (((piece.getSign() == X_SIGN) && (getSign(bottomLeft) == O_SIGN)) ||
		      ((piece.getSign() == O_SIGN && piece.isQueen()) && (getSign(bottomLeft) == X_SIGN))) &&
		     (isEmpty(bottomFarLeft)) ) {
			jumpedPieces.push_back(Jumped(getSign(bottomLeft), isQueen(bottomLeft), bottomLeft));
			piece.addToPossibleMoves(piece.getPosition(), bottomFarLeft, jumpedPieces);
			recurseDownwards(piece, bottomFarLeft, jumpedPieces, true);
		}
	}

	if (isValidPosition(bottomRight)) {
		if (!hasJumped) {
			if (isEmpty(bottomRight)) {
				piece.addToPossibleMoves(piece.getPosition(), bottomRight);
			}
		}

		if (jumpedPieces.size() > 1) {
			jumpedPieces.pop_back();
		}
		// if ( (((piece.getSign() == X_SIGN || piece.getSign() == X_QUEEN_SIGN) && (getSign(bottomRight) == O_SIGN || getSign(bottomRight) == O_QUEEN_SIGN)) ||
		// 	 ((piece.getSign() == O_QUEEN_SIGN) && (getSign(bottomRight) == X_SIGN || getSign(bottomRight) == X_QUEEN_SIGN))) && 
		// 	 (isEmpty(bottomFarRight)) ) {
		if ( (((piece.getSign() == X_SIGN) && (getSign(bottomRight) == O_SIGN)) ||
		      ((piece.getSign() == O_SIGN && piece.isQueen()) && (getSign(bottomRight) == X_SIGN))) &&
		     (isEmpty(bottomFarRight)) ) {
			jumpedPieces.push_back(Jumped(getSign(bottomRight), isQueen(bottomRight), bottomRight));
			piece.addToPossibleMoves(piece.getPosition(), bottomFarRight, jumpedPieces);
			recurseDownwards(piece, bottomFarRight, jumpedPieces, true);
		}
	}
}

// Recursive check upwards and update the potential moves
void Board::recurseUpwards(Slot& piece, std::pair<int,int> currentPosition, std::vector<Jumped> jumpedPieces, bool hasJumped) {
	std::pair<int,int> topLeft     = std::make_pair(currentPosition.first-1, currentPosition.second-1);
	std::pair<int,int> topRight    = std::make_pair(currentPosition.first-1, currentPosition.second+1);
	std::pair<int,int> topFarLeft  = std::make_pair(currentPosition.first-2, currentPosition.second-2);
	std::pair<int,int> topFarRight = std::make_pair(currentPosition.first-2, currentPosition.second+2);

	if (isValidPosition(topLeft)) {
		if (!hasJumped) {
			if (isEmpty(topLeft)) {
				piece.addToPossibleMoves(piece.getPosition(), topLeft);
			}
		}
		
		// if ( (((piece.getSign() == O_SIGN || piece.getSign() == O_QUEEN_SIGN) && (getSign(topLeft) == X_SIGN || getSign(topLeft) == X_QUEEN_SIGN)) ||
		// 	 ((piece.getSign() == X_QUEEN_SIGN) && (getSign(topLeft) == O_SIGN || getSign(topLeft) == O_QUEEN_SIGN))) && 
		// 	 (isEmpty(topFarLeft)) ) {
		if ( (((piece.getSign() == O_SIGN) && (getSign(topLeft) == X_SIGN)) ||
		      ((piece.getSign() == X_SIGN && piece.isQueen()) && (getSign(topLeft) == O_SIGN))) &&
		     (isEmpty(topFarLeft)) ) {
			jumpedPieces.push_back(Jumped(getSign(topLeft), isQueen(topLeft), topLeft));
			piece.addToPossibleMoves(piece.getPosition(), topFarLeft, jumpedPieces);
			recurseUpwards(piece, topFarLeft, jumpedPieces, true);
		}
	}

	if (isValidPosition(topRight)) {
		if (!hasJumped) {
			if (isEmpty(topRight)) {
				piece.addToPossibleMoves(piece.getPosition(), topRight);
			}
		}
		
		if (jumpedPieces.size() > 1) {
			jumpedPieces.pop_back();
		}
		// if ( (((piece.getSign() == O_SIGN || piece.getSign() == O_QUEEN_SIGN) && (getSign(topRight) == X_SIGN || getSign(topRight) == X_QUEEN_SIGN)) ||
		// 	 ((piece.getSign() == X_QUEEN_SIGN) && (getSign(topRight) == O_SIGN || getSign(topRight) == O_QUEEN_SIGN))) && 
		// 	 (isEmpty(topFarRight)) ) {
		if ( (((piece.getSign() == O_SIGN) && (getSign(topRight) == X_SIGN)) ||
		      ((piece.getSign() == X_SIGN && piece.isQueen()) && (getSign(topRight) == O_SIGN))) &&
		     (isEmpty(topFarRight)) ) {
			jumpedPieces.push_back(Jumped(getSign(topRight), isQueen(topRight), topRight));
			piece.addToPossibleMoves(piece.getPosition(), topFarRight, jumpedPieces);
			recurseUpwards(piece, topFarRight, jumpedPieces, true);
		}
	}
}

// Print the possible moves
void Board::printAllPossibleMoves() {
	std::cout << "Possible moves for the slots:" << std::endl;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			(board[i][j]).printPossibleMoves();
		}
	}
	std::cout << "\n" << std::endl;
}


std::vector<MoveEvent> Board::getPossibleMovesAt(std::pair<int,int> position) {
	return (board[position.first][position.second]).getPossibleMoves();
}

//----------------------------------------------------------------------------------------------------------
// Handle and Perform the Move
//----------------------------------------------------------------------------------------------------------
int Board::movePiece(std::pair<int,int> moveFrom, std::pair<int,int> moveTo) {
	if (!isValidPosition(moveFrom) || isEmpty(moveFrom)) {
		return 1;
	}
	if (!isEmpty(moveTo)) {
		return 1;
	}

	// Update and salve all the possible moves at this position
	updatePossibleMovesAt(board[moveFrom.first][moveFrom.second]);
	//(board[moveFrom.first][moveFrom.second]).printPossibleMoves();

	// Get the path(s) that lead to the target position
	std::vector<MoveEvent> paths = (board[moveFrom.first][moveFrom.second]).getMoveEventTo(moveTo);
	
	if (paths.size() == 0) {	// No path that leads to the target position
		return 1;
	}
	else if (paths.size() > 1) {	// Multiple paths are leading to the target position
		std::cout << PRINT_PROMPT_TEXT_BUFFER << "There are multiple paths to get to the target position." << std::endl;
		std::cout << PRINT_PROMPT_TEXT_BUFFER << "Choose the piece(s) that you want to jump to move to the target position." << std::endl;
		for (int i = 0; i < paths.size(); i++) {
			std::cout << PRINT_PROMPT_TEXT_BUFFER << i+1 << ": ";
			//std::cout << "(" << paths.at(i).getFrom().first << "," << paths.at(i).getFrom().second << ") -> ";
			for (auto jumped : paths.at(i).getJumpedList()) {
				std::cout << "(" << jumped.getPosition().first << "," << jumped.getPosition().second << ") ";
			}
			std::cout << std::endl;
		}

		int pathIndex;
		bool isValid = false;
		while (!isValid) {
			std::cout << PRINT_PROMPT_TEXT_BUFFER << "Choose: ";
			std::cin >> pathIndex;
			if (pathIndex >= 0 && pathIndex < paths.size()-1) {
				isValid = true;
			}
			else {
				std::cout << PRINT_PROMPT_TEXT_BUFFER << "Invalid choise. Try again." << std::endl;
			}
		}

		// Fire the move
		fireMoveEvent(paths.at(pathIndex-1));
		(board[moveFrom.first][moveFrom.second]).addToHistory(paths.at(pathIndex-1));
	}
	else {
		// Fire the move
		fireMoveEvent(paths.at(0));
		(board[moveFrom.first][moveFrom.second]).addToHistory(paths.at(0));	
	}
	
	return 0;
}

// Takes a move event and performs the move
void Board::fireMoveEvent(MoveEvent event) {
	//(board[event.getTo().first][event.getTo().second]).setSign(event.getFinalSign());
	
	(board[event.getTo().first][event.getTo().second]).setSign(event.getSign());
	
	if (event.hasBecomeQueen()) {
		(board[event.getTo().first][event.getTo().second]).setQueenStatus(true);
	}
	else {
		(board[event.getTo().first][event.getTo().second]).setQueenStatus((board[event.getFrom().first][event.getFrom().second]).isQueen());
	}
	
	(board[event.getTo().first][event.getTo().second]).resetPossibleMoves();
	//(board[event.getTo().first][event.getTo().second]).updateAfterMove(event);

	(board[event.getFrom().first][event.getFrom().second]).clear();

	for (auto jumped : event.getJumpedList()) {
		switch (jumped.getSign()) {
			case X_SIGN:
				if (!jumped.isQueen()) {
					boardStatus.decrementXCount();
				}
				else {
					boardStatus.decrementXQueenCount();	
				}
				boardStatus.decrementTotalXCount();
				break;
			
			case O_SIGN:
				if (!jumped.isQueen()) {
					boardStatus.decrementOCount();
				}
				else {
					boardStatus.decrementOQueenCount();	
				}
				boardStatus.decrementTotalOCount();
				break;
		}

		board[jumped.getPosition().first][jumped.getPosition().second].clear();
	}

	//updateAllPossibleMoves();
}


int Board::undoMove(std::pair<int,int> moveFrom, std::pair<int,int> moveTo) {
	if (!isValidPosition(moveFrom) || !isValidPosition(moveTo)) {
		return 1;
	}

	revertMoveEvent((board[moveFrom.first][moveFrom.second]).popHistory());
	return 0;
}

// Takes a move event and reverts that move
void Board::revertMoveEvent(MoveEvent event) {
	// std::cout << "Undo-ing move (" 
	// 		  << event.getFrom().first << "," << event.getFrom().second << ") -> (" 
	// 		  << event.getTo().first << "," << event.getTo().second << ")" << std::endl;

	(board[event.getFrom().first][event.getFrom().second]).setSign(event.getSign());
	
	if (event.hasBecomeQueen()) {
		(board[event.getFrom().first][event.getFrom().second]).setQueenStatus(false);
	}
	else {
		(board[event.getFrom().first][event.getFrom().second]).setQueenStatus((board[event.getTo().first][event.getTo().second]).isQueen());
	}

	(board[event.getTo().first][event.getTo().second]).clear();

	for (auto jumped : event.getJumpedList()) {
		switch (jumped.getSign()) {
			case X_SIGN:
				if (!jumped.isQueen()) {
					boardStatus.incrementXCount();
				}
				else {
					boardStatus.incrementXQueenCount();	
				}
				boardStatus.incrementTotalXCount();
				break;
			
			case O_SIGN:
				if (!jumped.isQueen()) {
					boardStatus.incrementOCount();
				}
				else {
					boardStatus.incrementOQueenCount();	
				}
				boardStatus.incrementTotalOCount();
				break;
		}

		(board[jumped.getPosition().first][jumped.getPosition().second]).setSign(jumped.getSign());
		(board[jumped.getPosition().first][jumped.getPosition().second]).setQueenStatus(jumped.isQueen());
	}
}



//----------------------------------------------------------------------------------------------------------
// Board Printer
//----------------------------------------------------------------------------------------------------------
void Board::printBoard() {
	printer.printBoard(board);
}

