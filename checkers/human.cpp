#include "human.h"
#include <iostream>

Human::Human() {}
Human::Human(char c) : humanSign(c) {}

void Human::setSign(char c) {
	humanSign = c;
}

char Human::getSign() {
	return humanSign;
}

void Human::makeMove(Board *gameBoard) {
	bool isValid = false;

	while (!isValid) {
		int row;
		int col;
		std::pair<int,int> moveFrom;
		std::pair<int,int> moveTo;
		
		bool isCorrectPieceChosen = false;
		while (!isCorrectPieceChosen) {
			std::cout << PRINT_PROMPT_TEXT_BUFFER << "--- Select Piece ---" << std::endl;
			std::cout << PRINT_PROMPT_TEXT_BUFFER << "Row   : ";
			std::cin  >> row;
			std::cout << PRINT_PROMPT_TEXT_BUFFER << "Column: ";
			std::cin  >> col;

			moveFrom = std::make_pair(row,col);

			if (gameBoard->getSign(moveFrom) == humanSign) {
				isCorrectPieceChosen = true;
			}
			else {
				std::cout << PRINT_PROMPT_TEXT_BUFFER << "Please select a correct piece.\n" << std::endl;
			}
		}
		
		std::cout << PRINT_PROMPT_TEXT_BUFFER << "--- Select Target Position ---" << std::endl;
		std::cout << PRINT_PROMPT_TEXT_BUFFER << "Row   : ";
		std::cin  >> row;
		std::cout << PRINT_PROMPT_TEXT_BUFFER << "Column: ";
		std::cin  >> col;
		
		moveTo = std::make_pair(row,col);

		int status = gameBoard->movePiece(moveFrom, moveTo);
		gameBoard->printBoard();

		if (status == 0) {
			int undo;
			bool isUndoInputCorrent = false;
			while (!isUndoInputCorrent) {
				std::cout << "\n" << PRINT_PROMPT_TEXT_BUFFER << "'0' to undo the move, '1' to proceed: ";
				std::cin  >> undo;
				if (undo == 0 || undo == 1) {
					if (undo == 0) {
						gameBoard->undoMove(moveFrom, moveTo);
						gameBoard->printBoard();
					}
					else {
						isValid = true;
					}

					isUndoInputCorrent = true;
				}
				else {
					std::cout << PRINT_PROMPT_TEXT_BUFFER << "Invalid input. Try again." << std::endl;
				}
			}
		}
	}
}

