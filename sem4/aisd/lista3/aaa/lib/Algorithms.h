#ifndef ALGORITHMS
#define ALGORITHMS

#include "Count.h"

class RandomSelect {
private:
	int n;

	template<typename T>
	int partition(T* A, int p, int q);

	template<typename T>
	T randomSelectRec(T* A, int p, int q, int i);
public:
	Count c;

	template<typename T>
	T randomSelect(T* A, int n, int i);
};

class Select {
private:
	int n = 30;
	int treshold = 5;

	template<typename T>
	int partition(T* A, int p, int q);

	template<typename T>
	void sortFragment(T* A, int l, int r);


public:
	Count c;

	template<typename T>
	T select(T* A, int n, int i);

	template<typename T>
	T selectRec(T* A, int p, int q, int i);
	
	void setTreshold(int newTreshold);
};

class BinSearch {
private:
	template<typename T>
	int binSearchRec(T* A, int p, int q, int v);
public:
	Count c;

	template<typename T>
	int binSearch(T* A, int n, int v);
};

class QuickSort {
private:
	int n = 30;

	template<typename T>
	int partition(T* A, int p, int q);

	template<typename T>
	std::pair<int, int> DPPartition(T* A, int p, int q);

	template<typename T>
	void quickSortRec(T* A, int p, int q);

	template<typename T>
	void quickSelectSortRec(T* A, int p, int q);

	template<typename T>
	void DPQuickSortRec(T* A, int p, int q);

	template<typename T>
	void DPQuickSelectSortRec(T* A, int p, int q);

public:
	Count c;

	template<typename T>
	void quickSort(T* A, int n);

	template<typename T>
	void quickSelectSort(T* A, int n);

	template<typename T>
	void DPQuickSort(T* A, int n);

	template<typename T>
	void DPQuickSelectSort(T* A, int n);
};

#include "randomSelect.cpp"
#include "select.cpp"
#include "binSearch.cpp"
#include "quickSort.cpp"

#endif