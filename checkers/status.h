#ifndef __STATUS_H__
#define __STATUS_H__

class Status {
private:
	int  xCount;
	int  xQueenCount;
	int  oCount;
	int  oQueenCount;
	int  totalXCount;
	int  totalOCount;

public:
	Status(int x, int xq, int o, int oq, int totalX, int totalO);

	void setXCount(int count);
	void setXQueenCount(int count);
	void setOCount(int count);
	void setOQueenCount(int count);
	void setTotalXCount(int count);
	void setTotalOCount(int count);

	void incrementXCount();
	void incrementXQueenCount();
	void incrementOCount();
	void incrementOQueenCount();
	void incrementTotalXCount();
	void incrementTotalOCount();

	void decrementXCount();
	void decrementXQueenCount();
	void decrementOCount();
	void decrementOQueenCount();
	void decrementTotalXCount();
	void decrementTotalOCount();

	void resetAllCounts();

	int getXCount();
	int getXQueenCount();
	int getOCount();
	int getOQueenCount();
	int getTotalXCount();
	int getTotalOCount();
};

#endif