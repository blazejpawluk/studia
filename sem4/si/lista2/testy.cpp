#include "ukladanka.cpp"

random_device rd;
mt19937 gen(rd());

array<uint8_t, 16> generateBoard() {
	array<uint8_t, 16> board;
	for (int i = 0; i < SIZE-1; i++) board[i] = i+1;
	board[SIZE-1] = 0;
	do {
		shuffle(board.begin(), board.begin() + SIZE - 1, gen);
	} while (!isSolvable(board));
	return board;
}

array<uint8_t, 16> shuffle(int moves) {
	array<uint8_t, 16> board;
	for (int i = 0; i < SIZE-1; i++) board[i] = i+1;
	board[SIZE-1] = 0;
	int index = SIZE-1;
	uniform_int_distribution<> dis(1, 4);
	for (int i = 0; i < moves; i++) {
		int column = index % WIDTH, row = index / WIDTH;

		bool legal = false;
		while (!legal) {
			int direction = dis(gen);
			switch (direction) {
				case 1: if (column - 1 >= 0) {
					legal = true;
					column--;
				} break;
				case 2: if (column + 1 < WIDTH) {
					legal = true;
					column++;
				} break;
				case 3: if (row - 1 >= 0) {
					legal = true;
					row--;
				} break;
				case 4: if(row + 1 < WIDTH) {
					legal = true;
					row++;
				} break;
			}
		}
		int newIndex = row * WIDTH + column;
		swap(board[index], board[newIndex]);
		index = newIndex;
	}
	return board;
}

int findEmpty(array<uint8_t, 16> board) {
	for (int i = 0; i < 16; i++) {
		if (board[i] == 0) return i;
	}
	return -1;
}

int main() {
	cout << "Testy heurystyk w ukladance 3x3\n";

	ofstream file3x3Misplaced("results/3x3-misplaced-results.txt");
	ofstream file3x3Manhattan("results/3x3-manhattan-results.txt");

	WIDTH = 3;
	SIZE = WIDTH*WIDTH;

	for (int powtorzenie = 1; powtorzenie <= 500; powtorzenie++) {
		if (powtorzenie % 50 == 0) {
			cout << "Powtorzenie nr " << powtorzenie << endl;
		}

		array<uint8_t, 16> board = generateBoard();
		uint64_t startingState = pack(board);
		uint8_t emptyIndex = SIZE-1;

		size_t visited;
		vector<uint8_t> path = aStar(startingState, emptyIndex, misplacedTiles, visited);
		file3x3Misplaced << visited << " " << path.size() << endl;

		path = aStar(startingState, emptyIndex, manhattan, visited);
		file3x3Manhattan << visited << " " << path.size() << endl;
	}

	file3x3Misplaced.close();
	file3x3Manhattan.close();


	cout << "\nTesty ukladanki 4x4\n";

	ofstream file4x4("results/4x4-results.txt");

	WIDTH = 4;
	SIZE = WIDTH*WIDTH;

	for (int przestawienia = 10; przestawienia <= 100; przestawienia += 10) {
		cout << "Ukladanka cofnieta o " << przestawienia << " przestawien\n";

		for (int powtorzenia = 0; powtorzenia < 100; powtorzenia++) {
			array<uint8_t, 16> board = shuffle(przestawienia);
			uint64_t startingState = pack(board);
			uint8_t emptyIndex = findEmpty(board);

			size_t visited;
			vector<uint8_t> path = aStar(startingState, emptyIndex, manhattan, visited);
			file4x4 << przestawienia << " " << visited << " " << path.size() << endl;
		}
	}

	file4x4.close();
}