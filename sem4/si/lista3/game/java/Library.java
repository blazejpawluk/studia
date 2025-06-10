import java.util.Random;

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

	private static int prev;

	public static int giveMove() {
		System.out.println("Library move.");
		int move = move();

		switch (move) {
			case 1: return 21;
			case 2: 
				int pos = -1;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						if (Board.board[i][j] == 1) pos = (i+1)*10 + j+1;
					}
				}
				prev = pos;

				switch (pos) {
					case 21, 41: return pos+3;
					case 12, 14: return pos+30;
					case 25, 45: return pos-3;
					case 52, 54: return pos-30;
					case 22: return 14;
					case 24: return 12;
					case 42: return 21;
					case 44: return 52;
				}
				return -1;
			case 3: 
				if (Board.board[4][3] == 0) return 54;
				return 24;
			case 4: 
				pos = -1;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						if (Board.board[i][j] == 2 && (i+1)*10 + j+1 != prev) pos = (i+1)*10 + j+1;
					}
				}

				for (int[][] line : Board.win) {
					int count = 0;
					for (int i = 0; i < 4; i++) 
						if (Board.board[line[i][0]][line[i][1]] == 1) count++;

					if (count == 2) {
						for (int i = 0; i < 4; i++) {
							if (Board.board[line[i][0]][line[i][1]] == 0) {
								Board.board[line[i][0]][line[i][1]] = 2;

								for (int[][] l : Board.win) {
									int c = 0;
									for (int j = 0; j < 4; j++) 
										if (Board.board[l[j][0]][l[j][1]] == 2 && (line[i][0] != l[j][0] || line[i][1] != l[j][1])) count++;
									
									if (c == 1) {
										Board.board[line[i][0]][line[i][1]] = 0;
										return (line[i][0]+1)*10 + line[i][1]+1;
									}
								}

								Board.board[line[i][0]][line[i][1]] = 0;
							}
						}

						int a = -1, b = -1;
						for (int i = 0; i < 4; i++) {
							if (Board.board[line[i][0]][line[i][1]] == 0) {
								if (a == -1) a = (line[i][0]+1)*10 + line[i][1]+1;
								else b = (line[i][0]+1)*10 + line[i][1]+1;
							}
						}
						return new Random().nextBoolean() ? a : b;
					}
				}

				return -1;
			case 5: 
				if (Board.board[4][3] == 1) {
					if (Board.board[1][3] == 0) return 24;
					if (Board.board[4][0] == 0) return 51;
					return 32;
				}
				if (Board.board[4][0] == 0) return 51;
				return 22;
		}

		System.out.println("Case not in library.");
		return -1;
	}
}