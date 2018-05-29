#include "status.h"

Status::Status(int x, int xq, int o, int oq, int totalX, int totalO) 
			  : xCount(x), xQueenCount(xq), oCount(o), oQueenCount(oq), totalXCount(totalX), totalOCount(totalO) {}

void Status::setXCount     (int count) { xCount = count;      }
void Status::setXQueenCount(int count) { xQueenCount = count; }
void Status::setOCount     (int count) { oCount = count;      }
void Status::setOQueenCount(int count) { oQueenCount = count; }
void Status::setTotalXCount(int count) { totalXCount = count; }
void Status::setTotalOCount(int count) { totalOCount = count; }

void Status::incrementXCount     () { xCount++;      }
void Status::incrementXQueenCount() { xQueenCount++; }
void Status::incrementOCount     () { oCount++;      }
void Status::incrementOQueenCount() { oQueenCount++; }
void Status::incrementTotalXCount() { totalXCount++; }
void Status::incrementTotalOCount() { totalOCount++; }

void Status::decrementXCount     () { xCount--;      }
void Status::decrementXQueenCount() { xQueenCount--; }
void Status::decrementOCount     () { oCount--;      }
void Status::decrementOQueenCount() { oQueenCount--; }
void Status::decrementTotalXCount() { totalXCount--; }
void Status::decrementTotalOCount() { totalOCount--; }

int Status::getXCount     () { return xCount;      }
int Status::getXQueenCount() { return xQueenCount; }
int Status::getOCount     () { return oCount;      }
int Status::getOQueenCount() { return oQueenCount; }
int Status::getTotalXCount() { return totalXCount; }
int Status::getTotalOCount() { return totalOCount; }

void Status::resetAllCounts() {
	xCount       = 0;
	xQueenCount  = 0;
	oCount       = 0;
	oQueenCount  = 0;
	totalXCount  = 0;
	totalOCount  = 0;
}


