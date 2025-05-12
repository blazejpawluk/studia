#include <bits/stdc++.h>
using namespace std;

bool isSolvable(array<uint8_t, 16> board) {
	int inversions = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = i+1; j < 16; j++) {
			if (board[i] > board[j]) inversions++;
		}
	}
	return inversions % 2 != 0;
}

void printBoard(array<uint8_t, 16> board) {
	cout << "+----+----+----+----+\n";
	for (int i = 0; i < 16; i++) {
		cout << "| " << ((int)board[i] < 10 ? "0" : "") << (int)board[i] << " ";
		if (i % 4 == 3) cout << "|\n+----+----+----+----+\n";
	}
}

uint64_t pack(array<uint8_t, 16> board) {
	uint64_t a = 0;
	for (int i = 0; i < 16; i++) a |= (uint64_t(board[i]) << i*4);
	return a;
}

array<uint8_t, 16> unpack(uint64_t a) {
	array<uint8_t, 16> board;
	for (int i = 0; i < 16; i++) board[i] = (a >> i*4) & 0xF;
	return board;
}

// heurystyka 1 - zliczanie zle ulozonych pol
int misplacedTiles(uint64_t a) {
	array<uint8_t, 16> board = unpack(a);
	int counter = 0;
	for (int i = 0; i < 16; i++) {
		if (board[i] != 0 && board[i] != i+1) counter++;
	}
	return counter;
}

// heurystyka 2 - Manhattan
int manhattan(uint64_t a) {
	array<uint8_t, 16> board = unpack(a);
    int distance = 0;
    for (int i = 0; i < 16; i++) {
        int value = board[i];
        if (value == 0) continue;
        int valRow = (value-1) / 4, valColumn = (value-1) % 4;
        int row = i/4, column = i%4;
        distance += abs(row-valRow) + abs(column-valColumn);
    }
    return distance;
}

struct Node {
	uint64_t state;
	uint8_t emptyIndex;
	vector<uint8_t> path;

	int g; // koszt dojścia do węzła od początku
	int f; // g + wynik heurystyki
	bool operator>(Node const& o) const {return f > o.f;}
};

vector<uint8_t> aStar(uint64_t startingState, uint8_t emptyIndex, int (*heur)(uint64_t), size_t& visited) {
	priority_queue<Node, vector<Node>, greater<Node>> pq;
	unordered_set<uint64_t> checked;

	Node root {startingState, emptyIndex, {emptyIndex}, 0, heur(startingState)};
	pq.push(root);

	visited = 0;

	// wspolczynniki ruchow (gora, dol, lewo, prawo)
	int dv[4] = {-1, 1, 0, 0};
	int dh[4] = {0, 0, -1, 1};

	while (!pq.empty()) {
		Node current = pq.top();
		pq.pop();

		if (checked.count(current.state)) continue;

		checked.insert(current.state);
		visited++;

		if (visited % 1000000 == 0) cout << "Odwiedzono juz " << visited << " stanow\n";

		if (current.f - current.g == 0) {
			return current.path;
		} 

		int row = current.emptyIndex / 4, column = current.emptyIndex % 4;
		array<uint8_t, 16> board = unpack(current.state);

		for (int i = 0; i < 4; i++) {
			int newRow = row + dv[i], newColumn = column + dh[i];

			if (newRow < 0 || newRow >= 4 || newColumn < 0 || newColumn >= 4) continue;

			int newEmptyIndex = newRow * 4 + newColumn;

			array<uint8_t, 16> newBoard = board;
			swap(newBoard[current.emptyIndex], newBoard[newEmptyIndex]);
			uint64_t newState = pack(newBoard);

			if (checked.count(newState)) continue;

			int newG = current.g + 1;
			int newH = heur(newState);

			Node nextNode {newState, (uint8_t)newEmptyIndex, current.path, newG, newG+newH};
			nextNode.path.push_back(nextNode.emptyIndex);
			pq.push(nextNode);
		}
	}

	return {};
}

int main() {
	array<uint8_t, 16> board;
	for (int i = 0; i < 15; i++) board[i] = i+1;
	board[15] = 0;

	random_device rd;
	mt19937 gen(rd());

	// losowa permutacja
	do {
		shuffle(board.begin(), board.end() - 1, gen);
	} while (!isSolvable(board));
	uint64_t startingState = pack(board);
	uint8_t emptyIndex = 15;

	// losowe przesunięcia
	// int index = 15;
	// uniform_int_distribution<> dis(1, 4);
	// for (int i = 0; i < 20; i++) {
	// 	int column = index % 4, row = index / 4;

	// 	bool legal = false;
	// 	while (!legal) {
	// 		int direction = dis(gen);
	// 		switch (direction) {
	// 			case 1: if (column - 1 >= 0) {
	// 				legal = true;
	// 				column--;
	// 			} break;
	// 			case 2: if (column + 1 < 4) {
	// 				legal = true;
	// 				column++;
	// 			} break;
	// 			case 3: if (row - 1 >= 0) {
	// 				legal = true;
	// 				row--;
	// 			} break;
	// 			case 4: if(row + 1 < 4) {
	// 				legal = true;
	// 				row++;
	// 			} break;
	// 		}
	// 	}
	// 	int newIndex = row * 4 + column;
	// 	swap(board[index], board[newIndex]);
	// 	index = newIndex;
	// }
	// uint64_t startingState = pack(board);
	// uint8_t emptyIndex = (int)index;

	cout << "Stan poczatkowy: \n";
	printBoard(board);

	// cout << "==================================================\n";
	
	// cout << "Heurystyka: zliczanie pol na zlych miejscach.\n";
	// size_t visitedMisplaced;
	// vector<uint8_t> misplacedPath = aStar(startingState, emptyIndex, misplacedTiles, visitedMisplaced);
	
	// array<uint8_t, 16> tempBoard = board;
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