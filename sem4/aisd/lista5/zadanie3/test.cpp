#include "heap.cpp"

int main() {
	Node* H = MakeHeap();

	int A[8] = {5, 3, 7, 1, 4, 9, 2, 6};
	for (int i = 0; i < 8; i++) {
		cout << "\nInsert " << A[i] << endl;
		H = Insert(H, A[i]);
		printHeap(H);
	}

	cout << "\nMinimum=" << Minimum(H)->key << endl;

	int min;
	H = ExtractMin(H, min);
	cout << "\nExtractMin=" << min << endl;
	printHeap(H);

	H = ExtractMin(H, min);
	cout << "\nExtractMin=" << min << endl;
	printHeap(H);

	DecreaseKey(find(H, 9), 8);
	cout << "\nDecreaseKey(9->8)\n";
	printHeap(H);

	DecreaseKey(find(H, 8), 1);
	cout << "\nDecreaseKey(8->1)\n";
	printHeap(H);

	H = Delete(H, find(H, 4));
	cout << "\nDelete 4\n";
	printHeap(H);

	H = Delete(H, find(H, 1));
	cout << "\nDelete 1\n";
	printHeap(H);

	return 0;
}