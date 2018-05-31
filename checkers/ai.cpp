#include "ai.h"
#include <iostream>
#include <cstdlib>

AI::AI(char ai, char human) : aiSign(ai), humanSign(human), treeDepth(AI_TREE_DEPTH) {}

MoveEvent AI::makeMove(Board *gameBoard) {
	MinimaxMove bestMove = minimax(gameBoard, gameBoard->getBoardStatus(), aiSign, 1, 5);
	gameBoard->fireMoveEvent(bestMove.getMoveEvent());
	return bestMove.getMoveEvent();
}

MinimaxMove AI::minimax(Board *gameBoard, Status initialStatus, char player, int currentDepth, int maxDepth) {
	char winner = gameBoard->getWinner();
	
	if (winner != NO_SIGN) {
		return getEndGameMove(winner);
	}
	if (currentDepth == maxDepth) {
		return getRecursionCutoffMove(gameBoard, initialStatus);
	}

	std::vector<MinimaxMove> potentialMoves;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {

			std::pair<int,int> position = std::make_pair(i,j);

			if ( ((player == aiSign)    && (gameBoard->getSign(position) == aiSign)) ||
				 ((player == humanSign) && (gameBoard->getSign(position) == humanSign)) ) {
				
				gameBoard->updatePossibleMovesAt(position);
				std::vector<MoveEvent> currentPossibleMoves = gameBoard->getPossibleMovesAt(position);

				for (auto moveEvent : currentPossibleMoves) {
					// std::cout << "firing: (" << moveEvent.getFrom().first << "," << moveEvent.getFrom().second << ") -> ("
					// 		  << moveEvent.getTo().first << "," << moveEvent.getTo().second << ")" << std::endl;

					gameBoard->fireMoveEvent(moveEvent);
					
					MinimaxMove currentMove(moveEvent, 0);
					if (player == aiSign) {
						int minimaxScore = (minimax(gameBoard, initialStatus, humanSign, currentDepth+1, maxDepth)).getScore();
						currentMove.setScore(minimaxScore);
					}
					else {
						int minimaxScore = (minimax(gameBoard, initialStatus, aiSign, currentDepth+1, maxDepth)).getScore();
						currentMove.setScore(minimaxScore);	
					}
					potentialMoves.push_back(currentMove);

					gameBoard->revertMoveEvent(moveEvent);
				}
			}
		}
	}

	//std::cout << "\nPotential Moves Size: " << potentialMoves.size() << "\n" << std::endl;

	if (potentialMoves.empty()) {
		return getRecursionCutoffMove(gameBoard, initialStatus);
	}

	std::vector<int> bestMovesVec;
	int bestMoveAt = 0;
	int bestScore = 0;

	if (player == aiSign) {
		bestScore = -100000;
		for (int i = 0; i < potentialMoves.size(); i++) {
			if (potentialMoves.at(i).getScore() > bestScore) {
				bestMoveAt = i;
				bestScore = potentialMoves.at(i).getScore();
			}
		}
	}
	else {
		bestScore = 100000;
		for (int i = 0; i < potentialMoves.size(); i++) {
			if (potentialMoves.at(i).getScore() < bestScore) {
				bestMoveAt = i;
				bestScore = potentialMoves.at(i).getScore();
			}
		}
	}

	for (int i = 0; i < potentialMoves.size(); i++) {
		if (potentialMoves.at(i).getScore() == bestScore) {
			bestMovesVec.push_back(i);
		}
	}

	int chooseBestMove = rand() % bestMovesVec.size();

	//return potentialMoves.at(bestMoveAt);
	return potentialMoves.at(bestMovesVec.at(chooseBestMove));
}


MinimaxMove AI::getRecursionCutoffMove(Board *currentGameBoard, Status initialStatus) {
	Status currentStatus = currentGameBoard->getBoardStatus();
	MinimaxMove minimaxMove(0);
	int score = 0;
	
	score += (((initialStatus.getTotalOCount()) - (currentStatus.getTotalOCount())) * 10);
	score -= (((initialStatus.getTotalXCount()) - (currentStatus.getTotalXCount())) * 10);
	score += (((currentStatus.getXQueenCount()) - (initialStatus.getXQueenCount())) * 5);
	score -= (((currentStatus.getOQueenCount()) - (initialStatus.getOQueenCount())) * 5);
	
	minimaxMove.setScore(score);
	return minimaxMove;
}

MinimaxMove AI::getEndGameMove(char winner) {
	MinimaxMove minimaxMove(0);
	int score = (winner == aiSign) ? 1000 : -1000;
	minimaxMove.setScore(score);
	return minimaxMove;
}