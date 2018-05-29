#include "slot.h"
#include "defines.h"
#include <iostream>

Slot::Slot() : queenStatus(false) {}
Slot::Slot(char c) : sign(c), queenStatus(false) {}
Slot::Slot(char c, int x, int y) : sign(c), queenStatus(false), position(std::make_pair(x,y)) {}
Slot::Slot(char c, bool qs, int x, int y) : sign(c), queenStatus(qs), position(std::make_pair(x,y)) {}
Slot::Slot(char c, std::pair<int,int> slotPosition) : sign(c), queenStatus(false), position(slotPosition) {}

void Slot::setSign(char c)                             { sign = c;               }
void Slot::setQueenStatus(bool qs)                     { queenStatus = qs;       }
void Slot::setPosition(std::pair<int,int> newPosition) { position = newPosition; }

void Slot::setAttributes(char c, bool qs, int x, int y) {
	setSign(c);
	setQueenStatus(qs);
	setPosition(std::make_pair(x,y));
}

char Slot::getSign()                   { return sign;        }
bool Slot::isQueen()                   { return queenStatus; }
std::pair<int,int> Slot::getPosition() { return position;    }

void Slot::resetPossibleMoves() {
	if (!possibleMoves.empty()) {
		possibleMoves.clear();
	}
}

void Slot::clear() {
	sign = NO_SIGN;
	queenStatus = false;
	resetPossibleMoves();	
}

std::vector<MoveEvent> Slot::getMoveEventTo(std::pair<int,int> requestedMove) {
	std::vector<MoveEvent> paths;
	for (auto event : possibleMoves) {
		if (event.getTo() == requestedMove) {
			paths.push_back(event);
		}
	}
	return paths;
}


void Slot::addToPossibleMoves(std::pair<int,int> from, std::pair<int,int> to) {
	MoveEvent moveEvent(sign, queenStatus, from, to);
	possibleMoves.push_back(moveEvent);
}

void Slot::addToPossibleMoves(std::pair<int,int> from, std::pair<int,int> to, std::vector<Jumped> jumpedList) {
	MoveEvent moveEvent(sign, queenStatus, from, to, jumpedList);
	possibleMoves.push_back(moveEvent);
}


std::vector<MoveEvent> Slot::getPossibleMoves() {
	return possibleMoves;
}



// void Slot::addToHistory(std::pair<int,int> from, std::pair<int,int> to) {
// 	MoveEvent moveEvent(sign, from, to);
// 	history.push(moveEvent);
// }

void Slot::addToHistory(MoveEvent event) {
	history.push(event);
}

MoveEvent Slot::popHistory() {
	MoveEvent event = history.top();
	history.pop();
	return event;
}


void Slot::printPossibleMoves() {
	std::cout << "Slot (" << position.first << "," << position.second << "): ";
	for (auto event : possibleMoves) {
		std::cout << "(" << event.getTo().first << "," << event.getTo().second << ") ";
	}
	std::cout << std::endl;
}