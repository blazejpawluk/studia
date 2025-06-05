public class Library {
	public static int move() {
		int move = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] != 0) move++;
			}
		}
		return move+1;
	}

	public static final int giveMove() {
		System.out.println("Library move.");
		int move = move();

		if (move == 1) return 21;
		if (move == 2) {
			// change
			if (Board.board[1][0] == 0) return 21;
			return 41;
		}
		if (move == 3) {
			if (Board.board[4][3] == 0) return 54;
			return 24;
		}
		if (move == 4) {
			// change
			if (Board.board[1][0] == 2) {
				if (Board.board[4][3] == 0) return 54;
				if (Board.board[1][3] == 0) return 24;
				return 51;
			}
			if (Board.board[0][3] == 0) return 14;
			return 44;
		}
		if (move == 5) {
			if (Board.board[4][3] == 1) {
				if (Board.board[1][3] == 0) return 24;
				if (Board.board[4][0] == 0) return 51;
				return 42;
			}
			if (Board.board[4][0] == 0) return 51;
			return 22;
		}
		if (move == 6) {

		}
		if (move == 7) {

		}
		if (move == 8) {
			
		}
		if (move == 9) {

		}
		if (move == 10) {
			
		}

		return -1;
	}
}