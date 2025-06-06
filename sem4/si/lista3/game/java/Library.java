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

	public static int giveMove() {
		System.out.println("Library move.");
		int move = move();

		switch (move) {
			case 1:
				System.out.println(21); 
				return 21;
			case 2: 
				if (Board.board[0][1] == 0) {
					System.out.println(21);
					return 21;
				}
				System.out.println(24);
				return 24;
			case 3: 
				if (Board.board[4][3] == 0) {
					System.out.println(54);
					return 54;
				}
				System.out.println(24);
				return 24;
			case 4: 
				if (Board.board[1][0] == 1) {
					if (Board.board[4][3] == 0) {
						System.out.println(54);
						return 54;
					}
					if (Board.board[1][3] == 0) {
						System.out.println(24);
						return 24;
					}
					System.out.println(34);
					return 34;
				}
				if (Board.board[4][3] == 0) {
					System.out.println(54);
					return 54;
				}
				System.out.println(43);
				return 43;
			case 5: 
				if (Board.board[4][3] == 1) {
					if (Board.board[1][3] == 0) {
						System.out.println(24);
						return 24;
					}
					if (Board.board[4][0] == 0) {
						System.out.println(51);
						return 51;
					}
					System.out.println(42);
					return 42;
				}
				if (Board.board[4][0] == 0) {
					System.out.println(51);
					return 51;
				}
				System.out.println(22);
				return 22;
			case 6: break;
		}

		System.out.println("Case not in library.");
		return -1;
	}
}