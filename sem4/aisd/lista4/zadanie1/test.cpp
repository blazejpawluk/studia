#include "bst.cpp"
#include <algorithm>
#include <random>

int main() {
	int size = 30;

	for (int i = 0; i < size; i++) {
		left_trace[i] = ' ';
		right_trace[i] = ' ';
	}

	int ascArr[size], ranArr[size], del[size];
	for (int i = 0; i < size; i++) {
		ascArr[i] = i+1;
		ranArr[i] = i+1;
		del[i] = i+1;
	}
	random_shuffle(ranArr, ranArr + size);
	random_shuffle(del, del + size);

	cout << "==================================================\n";
	cout << "1. Ascending array\n";

	root = nullptr;
	for (int i = 0; i < size; i++) {
		root = Insert(root, ascArr[i]);
		cout << "\ninsert " << ascArr[i] << endl;
		Print(root, 0, '-');
	}

	for (int i = 0; i < size; i++) {
		root = Delete(root, del[i]);
		cout << "\ndelete " << del[i] << endl;
		Print(root, 0, '-');
	}

	cout << "==================================================\n";
	cout << "2. Random array\n";

	root = nullptr;
	for (int i = 0; i < size; i++) {
		root = Insert(root, ranArr[i]);
		cout << "\ninsert " << ranArr[i] << endl;
		Print(root, 0, '-');
	}

	for (int i = 0; i < size; i++) {
		root = Delete(root, del[i]);
		cout << "\ndelete " << del[i] << endl;
		Print(root, 0, '-');
	}

	return 0;
}