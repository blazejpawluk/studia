#include <bits/stdc++.h>
using namespace std;

const int WIDTH = 4;
const int SIZE = WIDTH*WIDTH;

bool isSolvable(array<uint8_t, SIZE> board) {
	int inversions = 0;
	for (int i = 0; i < SIZE-1; i++) {
		for (int j = i+1; j < SIZE; j++) {
			if (board[i] > board[j]) inversions++;
		}
	}
	return inversions % 2 != WIDTH % 2;
}

void printBoard(array<uint8_t, SIZE> board) {
	for (int i = 0; i < WIDTH; i++) cout << "+----";
	cout << "+\n";

	for (int i = 0; i < SIZE; i++) {
		cout << "| " << ((int)board[i] < 10 ? "0" : "") << (int)board[i] << " ";

		if (i % WIDTH == WIDTH-1) {
			cout << "|\n";
			for (int j = 0; j < WIDTH; j++) cout << "+----";
			cout << "+\n";
		}
	}
}

uint64_t pack(array<uint8_t, SIZE> board) {
	uint64_t a = 0;
	for (int i = 0; i < SIZE; i++) a |= (uint64_t(board[i]) << i*4);
	return a;
}

array<uint8_t, SIZE> unpack(uint64_t a) {
	array<uint8_t, SIZE> board;
	for (int i = 0; i < SIZE; i++) board[i] = (a >> i*4) & 0xF;
	return board;
}

// heurystyka 1 - zliczanie zle ulozonych pol
int misplacedTiles(uint64_t a) {
	array<uint8_t, SIZE> board = unpack(a);
	int counter = 0;
	for (int i = 0; i < SIZE; i++) {
		if (board[i] != 0 && board[i] != i+1) counter++;
	}
	return counter;
}

// heurystyka 2 - Manhattan
int manhattan(uint64_t a) {
	array<uint8_t, SIZE> board = unpack(a);
	int distance = 0;
	for (int i = 0; i < SIZE; i++) {
		int value = board[i];
		if (value == 0) continue;
		int valRow = (value-1) / WIDTH, valColumn = (value-1) % WIDTH;
		int row = i/WIDTH, column = i%WIDTH;
		distance += abs(row-valRow) + abs(column-valColumn);
	}
	return distance;
}

struct Node {
	uint64_t state;
	uint8_t emptyIndex;
	shared_ptr<Node> parent;

	int g; // koszt dojścia do węzła od początku
	int f; // g + wynik heurystyki
};

struct NodeCompare {
	bool operator()(shared_ptr<Node> const& a, shared_ptr<Node> const& b) const {
		return a->f > b->f;
	}
};

vector<uint8_t> aStar(uint64_t startingState, uint8_t emptyIndex, int (*heur)(uint64_t), size_t& visited) {
	priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, NodeCompare> pq;
	unordered_set<uint64_t> checked;

	Node root {startingState, emptyIndex, nullptr, 0, heur(startingState)};
	shared_ptr<Node> rootPtr = make_shared<Node>(root);
	pq.push(rootPtr);

	visited = 0;

	// wspolczynniki ruchow (gora, dol, lewo, prawo)
	int dv[4] = {-1, 1, 0, 0};
	int dh[4] = {0, 0, -1, 1};

	while (!pq.empty()) {
		shared_ptr<Node> current = pq.top();
		pq.pop();

		if (checked.count(current->state)) continue;

		checked.insert(current->state);
		visited++;

		if (visited % 1000000 == 0) cout << "Odwiedzono juz " << visited << " stanow\n";

		if ((current->f) - (current->g) == 0) {
			vector<uint8_t> path;
			shared_ptr<Node> node = current;
			while (node) {
				path.push_back(node->emptyIndex);
				node = node->parent;
			}
			reverse(path.begin(), path.end());
			return path;
		}

		int row = (current->emptyIndex) / WIDTH;
		int column = (current->emptyIndex) % WIDTH;
		array<uint8_t, SIZE> board = unpack(current->state);

		for (int i = 0; i < 4; i++) {
			int newRow = row + dv[i], newColumn = column + dh[i];
			
			if (newRow < 0 || newRow >= WIDTH || newColumn < 0 || newColumn >= WIDTH) continue;

			int newEmptyIndex = newRow * WIDTH + newColumn;

			array<uint8_t, SIZE> newBoard = board;
			swap(newBoard[current->emptyIndex], newBoard[newEmptyIndex]);
			uint64_t newState = pack(newBoard);

			if (checked.count(newState)) continue;

			int newG = (current->g) + 1;
			int newH = heur(newState);

			Node nextNode {newState, (uint8_t)newEmptyIndex, current, newG, newG+newH};
			shared_ptr<Node> nextPtr = make_shared<Node>(nextNode);
			pq.push(nextPtr);
		}
	}

	return {};
}

int main() {
	array<uint8_t, SIZE> board;
	for (int i = 0; i < SIZE-1; i++) board[i] = i+1;
	board[SIZE-1] = 0;

	random_device rd;
	mt19937 gen(rd());

	// board = {12, 10, 14, 11, 9, 8, 6, 2, 0, 7, 15, 13, 4, 1, 5, 3}; uint8_t emptyIndex = 8;
	// board = {4, 12, 15, 5, 14, 10, 11, 13, 0, 7, 2, 8, 6, 9, 1, 3}; uint8_t emptyIndex = 8;
	// board = {7, 5, 8, 12, 1, 6, 9, 14, 10, 0, 2, 4, 3, 11, 13, 15}; uint8_t emptyIndex = 8;

	// losowa permutacja
	// do {
	// 	shuffle(board.begin(), board.end() - 1, gen);
	// } while (!isSolvable(board));
	// uint8_t emptyIndex = SIZE-1;

	// losowe przesunięcia
	int index = SIZE-1;
	uniform_int_distribution<> dis(1, 4);
	for (int i = 0; i < 20; i++) {
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
	uint8_t emptyIndex = (int)index;

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
	
	cout << "==================================================\n";
	
	cout << "Heurystyka: Manhattan.\n";
	size_t visitedManhattan;
	vector<uint8_t> manhattanPath = aStar(startingState, emptyIndex, manhattan, visitedManhattan);
	
	array<uint8_t, SIZE> tempBoard = board;
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