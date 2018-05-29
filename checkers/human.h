#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "defines.h"
#include "board.h"
#include <utility>

class Human {
private:
	char humanSign;

public:
	Human();
	Human(char c);
	void setSign(char c);
	char getSign();
	void makeMove(Board *gameBoard);
};

#endif