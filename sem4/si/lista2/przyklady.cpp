#include "ukladanka.cpp"

int main() {
	WIDTH = 4;
	SIZE = WIDTH*WIDTH;

	array<uint8_t, 16> board;
	for (int i = 0; i < SIZE-1; i++) board[i] = i+1;
	board[SIZE-1] = 0;

	random_device rd;
	mt19937 gen(rd());

	// przykładowe układanki
	board = {7, 5, 8, 12, 1, 6, 9, 14, 10, 0, 2, 4, 3, 11, 13, 15}; uint8_t emptyIndex = 8;
	// board = {12, 10, 14, 11, 9, 8, 6, 2, 0, 7, 15, 13, 4, 1, 5, 3}; uint8_t emptyIndex = 8;
	// board = {4, 12, 15, 5, 14, 10, 11, 13, 0, 7, 2, 8, 6, 9, 1, 3}; uint8_t emptyIndex = 8;

	// losowa permutacja
	// do {
	// 	shuffle(board.begin(), board.begin() + SIZE - 1, gen);
	// } while (!isSolvable(board));
	// uint8_t emptyIndex = SIZE-1;

	// losowe przesunięcia
	// int index = SIZE-1;
	// uniform_int_distribution<> dis(1, 4);
	// for (int i = 0; i < 20; i++) {
	// 	int column = index % WIDTH, row = index / WIDTH;

	// 	bool legal = false;
	// 	while (!legal) {
	// 		int direction = dis(gen);
	// 		switch (direction) {
	// 			case 1: if (column - 1 >= 0) {
	// 				legal = true;
	// 				column--;
	// 			} break;
	// 			case 2: if (column + 1 < WIDTH) {
	// 				legal = true;
	// 				column++;
	// 			} break;
	// 			case 3: if (row - 1 >= 0) {
	// 				legal = true;
	// 				row--;
	// 			} break;
	// 			case 4: if(row + 1 < WIDTH) {
	// 				legal = true;
	// 				row++;
	// 			} break;
	// 		}
	// 	}
	// 	int newIndex = row * WIDTH + column;
	// 	swap(board[index], board[newIndex]);
	// 	index = newIndex;
	// }
	// uint8_t emptyIndex = (int)index;

	uint64_t startingState = pack(board);

	cout << "Stan poczatkowy: \n";
	printBoard(board);

	// cout << "==================================================\n";
	
	// cout << "Heurystyka: zliczanie pol na zlych miejscach.\n";
	// size_t visitedMisplaced;
	// vector<uint8_t> misplacedPath = aStar(startingState, emptyIndex, misplacedTiles, visitedMisplaced);
	
	// array<uint8_t, SIZE> tempBoard = board;
	// printBoard(tempBoard);
	// for (int i = 1; i < misplacedPath.size(); i++) {
	// 	cout << i << ":\n";
	// 	swap(tempBoard[misplacedPath[i-1]], tempBoard[misplacedPath[i]]);
	// 	printBoard(tempBoard);
	// }
	// cout << "Podsumowanie: odwiedzono " << visitedMisplaced << " stanow, rozwiazano w " << misplacedPath.size()-1 << " ruchach.\n";
	
	// cout << "==================================================\n";
	
	// cout << "Heurystyka: Manhattan.\n";
	// size_t visitedManhattan;
	// vector<uint8_t> manhattanPath = aStar(startingState, emptyIndex, manhattan, visitedManhattan);
	
	// array<uint8_t, 16> tempBoard = board;
	// printBoard(tempBoard);
	// for (int i = 1; i < manhattanPath.size(); i++) {
	// 	cout << i << ":\n";
	// 	swap(tempBoard[manhattanPath[i-1]], tempBoard[manhattanPath[i]]);
	// 	printBoard(tempBoard);
	// }
	// cout << "Podsumowanie: odwiedzono " << visitedManhattan << " stanow, rozwiazano w " << manhattanPath.size()-1 << " ruchach.\n";
	
	cout << "==================================================\n";
	
	cout << "Heurystyka: Manhattan z ulepszeniami.\n";
	size_t visitedManhattan;
	vector<uint8_t> manhattanPath = aStar(startingState, emptyIndex, heuristic, visitedManhattan);
	
	array<uint8_t, 16> tempBoard = board;
	printBoard(tempBoard);
	for (int i = 1; i < manhattanPath.size(); i++) {
		cout << i << ":\n";
		swap(tempBoard[manhattanPath[i-1]], tempBoard[manhattanPath[i]]);
		printBoard(tempBoard);
	}
	cout << "Podsumowanie: odwiedzono " << visitedManhattan << " stanow, rozwiazano w " << manhattanPath.size()-1 << " ruchach.\n";
	
	// cout << "==================================================\n";
	// cout << "Porownanie:\n";
	// cout << "Misplaced: " << visitedMisplaced << ", " << misplacedPath.size()-1 << ", (";
	// for (int i = 0; i < misplacedPath.size() - 1; i++) cout << (int)misplacedPath[i] << ", ";
	// cout << (int)misplacedPath[misplacedPath.size() - 1] << ")\nManhattan: " << visitedManhattan << ", " << manhattanPath.size()-1 << ", (";
	// for (int i = 0; i < manhattanPath.size() - 1; i++) cout << (int)manhattanPath[i] << ", ";
	// cout << (int)misplacedPath[misplacedPath.size() - 1] << ")\n";

	return 0;
}