#include "heap.cpp"

int main() {
	vector<int> H = makeHeap();

	Insert(H, 5);
	Insert(H, 8);
	Insert(H, 4);
	Insert(H, 2);
	Insert(H, 6);
	Insert(H, 3);
	Insert(H, 1);
	Insert(H, 9);

	cout << "After inserts\n";
	print(H);

	cout << "Minimum " <<  Minimum(H) << endl;

	cout  << "Extracted " << ExtractMin(H) << endl;
	print(H);

	vector<int> H2 = makeHeap();
	Insert(H2, 1);
	Insert(H2, 10);
	Insert(H2, 7);

	H = Union(H, H2);

	cout << "After union\n";
	print(H);

	DecreaseKey(H, 10, 5);
	cout << "Decrease 10->5\n";
	print(H);
	
	DecreaseKey(H, 5, 2);
	cout << "Decrease 5->2\n";
	print(H);

	Delete(H, 8);
	cout << "Delete 8\n";
	print(H);

	Delete(H, 4);
	cout << "Delete 4\n";
	print(H);

	Delete(H, 1);
	cout << "Delete 1\n";
	print(H);

	return 0;
}