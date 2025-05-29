#include "rbbst.cpp"
#include <algorithm>
#include <random>

int main() {
	int size = 30;

	for (int i = 0; i < size; i++) {
		left_trace[i] = ' ';
		right_trace[i] = ' ';
	}
	initNIL();

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> ArrayDis(0, 2 * size - 1);

	int ascArr[size], ranArr[size], del[size];
	for (int i = 0; i < size; i++) {
		ranArr[i] = ArrayDis(gen);
		ascArr[i] = ranArr[i];
		del[i] = i;
	}
	sort(ascArr, ascArr + size);
	random_shuffle(del, del + size);

	cout << "==================================================\n";
	cout << "1. Ascending array\n";

	root = NIL;
	for (int i = 0; i < size; i++) {
		Insert(root, ascArr[i]);
		cout << "\ninsert " << ascArr[i] << endl;
		Print(root, 0, '-');
	}

	for (int i = 0; i < size; i++) {
		Delete(root, ascArr[del[i]]);
		cout << "\ndelete " << ascArr[del[i]] << endl;
		Print(root, 0, '-');
	}

	cout << "==================================================\n";
	cout << "2. Random array\n";

	root = NIL;
	for (int i = 0; i < size; i++) {
		Insert(root, ranArr[i]);
		cout << "\ninsert " << ranArr[i] << endl;
		Print(root, 0, '-');
	}

	for (int i = 0; i < size; i++) {
		Delete(root, ranArr[del[i]]);
		cout << "\ndelete " << ranArr[del[i]] << endl;
		Print(root, 0, '-');
	}

	return 0;
}