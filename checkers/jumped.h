#ifndef __JUMPED_H__
#define __JUMPED_H__

#include "defines.h"
#include <utility>

class Jumped {
private:
	char sign;
	bool queenStatus;
	std::pair<int,int> position;

public:
	Jumped(char c, bool qs, std::pair<int,int> jumpedPosition);
	char getSign();
	bool isQueen();
	std::pair<int,int> getPosition();
};

#endif