import java.util.Random;

public class Bot {
	private static Random r = new Random();

	public static int move(int player, int depth) {
		int bestMove = -1, bestScore = Integer.MIN_VALUE;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = player;
					int score = minimax(player, depth - 1, false, player);
					Board.board[i][j] = 0;

					if (score > bestScore || (score == bestScore && r.nextBoolean())) {
						bestScore = score;
						bestMove = (i+1)*10 + (j+1);
					}
				}
			}
		}
		System.out.println("Najlepszy ruch ma wartosc: " + bestScore);
		return bestMove == -1 ? 0 : bestMove;
	}

	private static int minimax(int player, int depth, boolean maximizing, int rootPlayer) {
		if (Board.winCheck(rootPlayer)) return 987654321;
		if (Board.winCheck(3 - rootPlayer)) return -987654321;
		if (Board.loseCheck(rootPlayer)) return -123456789;
		if (Board.loseCheck(3 - rootPlayer)) return 123456789;

		if (depth == 0) return evaluate(rootPlayer);

		int best = (maximizing ? Integer.MIN_VALUE : Integer.MAX_VALUE);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = (maximizing ? rootPlayer : 3 - rootPlayer);
					int val = minimax(player, depth - 1, !maximizing, rootPlayer);
					Board.board[i][j] = 0;
					best = (maximizing ? Math.max(best, val) : Math.min(best, val)); 
				}
			}
		}

		return best;
	}

	private static int evaluate(int player) {
		int opp = 3 - player;
		int score = 0;
		
		// różnica liczby wygrywających linii
		int winLineDiff = 0;
		for (int[][] line : Board.win) {
			boolean canWinPlayer = true;
			boolean canWinOpp = true;
			for (int[] p : line) {
				int r = p[0], c = p[1];
				if (Board.board[r][c] == opp) canWinPlayer = false;
				if (Board.board[r][c] == player) canWinOpp = false;
			}
			if (canWinPlayer) winLineDiff++;
			if (canWinOpp) winLineDiff--;
		}
		score += winLineDiff;

		// różnica przegrywających linii
		int loseLineDiff = 0;
		for (int[][] line : Board.lose) {
			boolean canWinPlayer = true;
			boolean canWinOpp = true;
			for (int[] p : line) {
				int r = p[0], c = p[1];
				if (Board.board[r][c] == opp) canWinPlayer = false;
				if (Board.board[r][c] == player) canWinOpp = false;
			}
			if (canWinPlayer) loseLineDiff--;
			if (canWinOpp) loseLineDiff++;
		}
		score += loseLineDiff;

		// różnica dostępnych (nie powodujących natychmiastowej przegranej) ruchów
		int availableDiff = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = player;
					if (!Board.loseCheck(player)) availableDiff++;
					Board.board[i][j] = 0;
					
					Board.board[i][j] = opp;
					if (!Board.loseCheck(opp)) availableDiff--;
					Board.board[i][j] = 0;
				}
			}
		}
		score += availableDiff;

		return score;
	}
}
