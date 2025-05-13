#include "puzzle.h"

bool Puzzle::isSolvable() {
	int inversions = 0;
	for (int i = 0; i < (this->size)-1; i++) {
		for (int j = i+1; j < (this->size); j++) {
			if ((this->board[i]) > (this->board[j])) inversions++;
		}
	}
	return inversions % 2 != (this->width) % 2;
}

uint64_t Puzzle::pack(array<uint8_t, 16> board) {
	uint64_t a = 0;
	for (int i = 0; i < (this->size); i++) a |= (uint64_t(board[i]) << i*4);
	return a;
}

array<uint8_t, 16> Puzzle::unpack(uint64_t a) {
	array<uint8_t, 16> board;
	for (int i = 0; i < (this->size); i++) board[i] = (a >> i*4) & 0xF;
	return board;
}

Puzzle::Puzzle(int width) {
	this->width = width;
	this->size = width*width;
}

void Puzzle::generateBoard() {
	for (int i = 0; i < (this->size)-1; i++) (this->board)[i] = i+1;
	(this->board)[(this->size) - 1] = 0;

	random_device rd;
	mt19937 gen(rd());

	do {
		shuffle((this->board).begin(), (this->board).end() - 1, gen);
	} while (!isSolvable());
	uint8_t emptyIndex = size-1;
}

void Puzzle::shuffleBoard(int moves) {
	for (int i = 0; i < (this->size)-1; i++) (this->board)[i] = i+1;
	(this->board)[(this->size) - 1] = 0;
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 4);
	
	int index = (this->size) - 1;
	for (int i = 0; i < moves; i++) {
		int column = index % (this->width);
		int row = index / (this->width);

		bool legal = false;
		while (!legal) {
			int direction = dis(gen);
			switch (direction) {
				case 1: if (column - 1 >= 0) {
					legal = true;
					column--;
				} break;
				case 2: if (column + 1 < (this->width)) {
					legal = true;
					column++;
				} break;
				case 3: if (row - 1 >= 0) {
					legal = true;
					row--;
				} break;
				case 4: if(row + 1 < (this->width)) {
					legal = true;
					row++;
				} break;
			}
		}
		int newIndex = row * width + column;
		swap((this->board)[index], (this->board)[newIndex]);
		index = newIndex;
	}
}

void Puzzle::setBoard(array<uint8_t, 16> board) {
	this->board = board;
}

void Puzzle::printBoard() {
	for (int i = 0; i < (this->width); i++) cout << "+----";
	cout << "+\n";

	for (int i = 0; i < (this->size); i++) {
		cout << "| " << ((int)(this->board)[i] < 10 ? "0" : "") << (int)(this->board)[i] << " ";

		if (i % (this->width) == (this->width) - 1) {
			cout << "|\n";
			for (int j = 0; j < (this->width); j++) cout << "+----";
			cout << "+\n";
		}
	}
}

int Puzzle::misplacedTiles(uint64_t a) {
	array<uint8_t, 16> board = unpack(a);
	int counter = 0;
	for (int i = 0; i < (this->size); i++) {
		if ((this->board)[i] != 0 && (this->board)[i] != i+1) counter++;
	}
	return counter;
}

int Puzzle::manhattan(uint64_t a) {
	array<uint8_t, 16> board = unpack(a);
	int distance = 0;
	for (int i = 0; i < (this->size); i++) {
		int value = (this->board)[i];
		if (value == 0) continue;
		int valRow = (value-1) / (this->width), valColumn = (value-1) % (this->width);
		int row = i/(this->width), column = i%(this->width);
		distance += abs(row-valRow) + abs(column-valColumn);
	}
	return distance;
}