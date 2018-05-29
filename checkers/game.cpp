#include "game.h"
#include <iostream>

Game::Game() : gameBoard(new Board()), currentTurn(O_SIGN), human(new Human(O_SIGN)), ai(new AI(X_SIGN, O_SIGN)), winner(NO_SIGN) {}

Game::~Game() {
	delete human;
	delete ai;
	delete gameBoard;
}

void Game::toggleTurn() {
	currentTurn = (currentTurn == X_SIGN) ? O_SIGN : X_SIGN;

}

void Game::play() {
	gameBoard->printBoard();
	while (winner == NO_SIGN) {
		human->makeMove(gameBoard);
		MoveEvent aiMove = ai->makeMove(gameBoard);

		gameBoard->printBoard();
		std::cout << "\n\n" << PRINT_PROMPT_TEXT_BUFFER << "*** AI moved from (" << aiMove.getFrom().first << "," << aiMove.getFrom().second << ") to "
				                                        << "(" << aiMove.getTo().first << "," << aiMove.getTo().second << ") ***\n" << std::endl;
		
		//gameBoard->updateAllPossibleMoves();
		//gameBoard->printAllPossibleMoves();
		winner = gameBoard->getWinner();
	}

	gameBoard->printBoard();
	std::cout << PRINT_PROMPT_TEXT_BUFFER << "\nWinner: " << winner << std::endl;
	
	char c = getchar();
	std::cin.ignore();
}




// void Game::play() {
// 	gameBoard->printBoard();

// 	while (true) {
// 		int row;
// 		int col;
		
// 		std::cout << "Select Piece" << std::endl;
// 		std::cout << "Row: ";
// 		std::cin >> row;
// 		std::cout << "Column: ";
// 		std::cin >> col;
// 		std::pair<int,int> moveFrom = std::make_pair(row,col);

// 		std::cout << "Choose Move Location" << std::endl;
// 		std::cout << "Row: ";
// 		std::cin >> row;
// 		std::cout << "Column: ";
// 		std::cin >> col;
// 		std::pair<int,int> moveTo = std::make_pair(row,col);

// 		int status = gameBoard->movePiece(moveFrom, moveTo);
// 		gameBoard->printBoard();

// 		if (status == 0) {
// 			char undo;
// 			std::cout << "Undo move? (y/n): ";
// 			std::cin >> undo;
// 			std::cout << std::endl;
// 			if (undo == 'y') {
// 				gameBoard->undoMove(moveFrom, moveTo);
// 				gameBoard->printBoard();
// 			}	
// 		}
// 	}
// } 