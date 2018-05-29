#ifndef __BOARD_PRINTER_H__
#define __BOARD_PRINTER_H__

#include "defines.h"
#include "slot.h"

class BoardPrinter {
private:
	void printLine(Slot& slot, int lineNum, int row, int col);

public:
	BoardPrinter();
	void printBoard(Slot board[BOARD_HEIGHT][BOARD_WIDTH]);
};

#endif