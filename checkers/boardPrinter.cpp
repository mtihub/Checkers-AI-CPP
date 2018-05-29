#include "boardPrinter.h"
#include <iostream>
#include <math.h>

using namespace std;

BoardPrinter::BoardPrinter() {}

void BoardPrinter::printBoard(Slot board[BOARD_HEIGHT][BOARD_WIDTH]) {
	//std::cout.flush();
	//system("clear");

	std::cout << "\n\n";

	std::cout << PRINT_BOARD_BUFFER << PRINT_HORIZONTAL_MARKINGS << std::endl;
	std::cout << PRINT_BOARD_BUFFER << PRINT_HORIZONTAL_BOUNDARY << std::endl;
	
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int k = 0; k < SQUARE_LINE_HEIGHT; k++) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				printLine(board[i][j], k+1, i, j);
			}
			std::cout << std::endl;
		}

		if (i != BOARD_HEIGHT-1) {
			std::cout << PRINT_BOARD_BUFFER << PRINT_ROW_DIVIDER << std::endl;
		}
	}

	std::cout << PRINT_BOARD_BUFFER << PRINT_HORIZONTAL_BOUNDARY << std::endl;
	std::cout << PRINT_BOARD_BUFFER << PRINT_HORIZONTAL_MARKINGS << "\n" << std::endl;
}

void BoardPrinter::printLine(Slot& slot, int lineNum, int row, int col) {
	if (col == 0) {
		std::cout << PRINT_BOARD_BUFFER;
		if (lineNum == ceil(SQUARE_LINE_HEIGHT / 2.0)) {
			std::cout << (row) << " |";
		}
		else {
			std::cout << "  |";
		}
	}

	switch(lineNum) {
		case 1:
			if (slot.getSign() == X_SIGN) {
				if (!slot.isQueen()) {
					std::cout << PRINT_X_LINE_1;
				}
				else {
					std::cout << PRINT_X_QUEEN_LINE_1;
				}
			}
			else if (slot.getSign() == O_SIGN) {
				if (!slot.isQueen()) {
					std::cout << PRINT_O_LINE_1;
				}
				else {
					std::cout << PRINT_O_QUEEN_LINE_1;	
				}
			}
			else {
				std::cout << PRINT_EMPTY_LINE;
			}
			break;

		case 2:
			if (slot.getSign() == X_SIGN) {
				if (!slot.isQueen()) {
					std::cout << PRINT_X_LINE_2;
				}
				else {
					std::cout << PRINT_X_QUEEN_LINE_2;
				}
			}
			else if (slot.getSign() == O_SIGN) {
				if (!slot.isQueen()) {
					std::cout << PRINT_O_LINE_2;
				}
				else {
					std::cout << PRINT_O_QUEEN_LINE_2;
				}
			}
			else {
				std::cout << PRINT_EMPTY_LINE;
			}
			break;

		case 3:
			if (slot.getSign() == X_SIGN) {
				if (!slot.isQueen()) {
					std::cout << PRINT_X_LINE_3;
				}
				else {
					std::cout << PRINT_X_QUEEN_LINE_3;
				}
			}
			else if (slot.getSign() == O_SIGN) {
				if (!slot.isQueen()) {
					std::cout << PRINT_O_LINE_3;
				}
				else {
					std::cout << PRINT_O_QUEEN_LINE_3;
				}
			}
			else {
				std::cout << PRINT_EMPTY_LINE;
			}
			break;
	}

	std::cout << "|";

	if (col == BOARD_WIDTH-1 && lineNum == ceil(SQUARE_LINE_HEIGHT / 2.0)) {
		std::cout << " " << (row);
	}
}