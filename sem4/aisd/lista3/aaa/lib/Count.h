#ifndef COUNT_H
#define COUNT_H

class Count {
private:
	int comps;
	int swaps;

public:
	Count();

	template<typename T>
	void swapInArray(T* A, int i, int j);

	template<typename T>
	bool lt(T a, T b);

	template<typename T>
	bool le(T a, T b);
	
	template<typename T>
	bool eq(T a, T b);
	
	template<typename T>
	bool ge(T a, T b);
	
	template<typename T>
	bool gt(T a, T b);
	
	int getComps();
	int getSwaps();
};

#include "Count.cpp"

#endif