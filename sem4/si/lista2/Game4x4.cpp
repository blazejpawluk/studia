#ifndef GAME4x4
#define GAME4x4

#include <iostream>
#include <random>
#include <cmath>
#include <cstdint>
#include <ctime>

class Game4x4 {
private:
	std::uint64_t board;

	bool areNeighbour(int i, int j) {
		if (std::abs(i - j) == 4) {
			return true;
		}
		if (std::abs(i - j) == 1 && i/4 == j/4) {
			return true;
		}
		return false;
	}

	bool isSolvable() {
		int parity = 0;
		int row = 0;
		int blankRow = 0;

		for (int i = 0; i < 16; i++) {
			if (i % 4 == 0) row++;

			if (get(i) == 0) {
				blankRow = row;
				continue;
			}
			for (int j = i + 1; j < 16; j++) {
				if (get(i) > get(j) && get(j) != 0) {
					parity++;
				}
			}
		}

		if (blankRow % 2 == 0) {
			return parity % 2 == 0;
		}
		return parity % 2 == 1;
	}

public:
	Game4x4() {
		board = 0;
		std::srand(static_cast<unsigned>(std::time(nullptr)));
	}

	void set(int value, int pos) {
		if (value < 0 || value > 15) {
			throw std::out_of_range("value out of range");
		}
		if (pos < 0 || pos > 15) {
			throw std::out_of_range("pos out of range");
		}

		board &= ~(uint64_t(0xF) << (pos * 4));
		board |= (uint64_t(value & 0xF) << (pos * 4));
	}

	void setBoard(std::uint64_t board) {
		this->board = board;
	}

	int get(int pos) {
		if (pos < 0 || pos > 15) {
			throw std::out_of_range("pos out of range");
		}

		return int((board >> (pos * 4)) & 0xF);
	}

	std::uint64_t getBoard() {
		return board;
	}

	void shuffle() {
		for (int i = 0; i < 16; i++) {
			set(i, i);
		}

		for (int i = 15; i >= 1; i--) {
			int j = std::rand() % (i + 1);

			int iValue = get(i);
			int jValue = get(j);

			set(iValue, j);
			set(jValue, i);
		}

		if (!isSolvable()) {
			shuffle();
		}
	}

	void shuffle(int moves) {
		for (int i = 0; i < 15; i++) {
			set(i + 1, i);
		}
		set(0, 15);

		std::srand(static_cast<unsigned>(std::time(nullptr)));

		int emptyIndex = 15;
		for (int i = 0; i < moves; i++) {
			bool ready = false;
			while (!ready) {
				int randomIndex = std::rand() % 16;
				try {
					move(emptyIndex, randomIndex);
					emptyIndex = randomIndex;
					ready = true;
				} catch (std::exception &e) {}
			}
		}
	}

	void move(int i, int j) {
		int iValue = get(i);
		int jValue = get(j);

		if (iValue != 0 && jValue != 0) {
			throw std::out_of_range("not able to swap: trying to swap fields, when none of them is empty");
		}
		if (!areNeighbour(i, j)) {
			throw std::out_of_range("not able to swap: trying to swap fields that are not neighbors");
		}

		set(jValue, i);
		set(iValue, j);
	}

	void print() {
		for (int i = 0; i < 4; i++) {
			std::cout << "+--+--+--+--+\n|";
			for (int j = 0; j < 4; j++) {
				int value = get(i * 4 + j);
				std::cout << (value < 10 ? "0" : "") << value << "|" << (j == 3 ? "\n" : "");
			}
		}
		std::cout << "+--+--+--+--+\n";
	}
};

#endif

int main() {
	Game4x4 g;
	g.shuffle();
	g.print();
}