import java.util.Random;

public class Bot {
	private static Random r = new Random();

	public static int move(int player, int depth) {
		int bestMove = -1;
		int bestScore = Integer.MIN_VALUE;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = player;
					int score = minimax(player, depth - 1, Integer.MIN_VALUE, Integer.MAX_VALUE, false);
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

	private static int minimax(int rootPlayer, int depth, int alpha, int beta, boolean maximizing) {
		if (Board.winCheck(rootPlayer)) return 2000;
		if (Board.winCheck(3 - rootPlayer)) return -2000;
		if (Board.loseCheck(rootPlayer)) return -1000;
		if (Board.loseCheck(3 - rootPlayer)) return 1000;

		if (depth == 0) return evaluate(rootPlayer);

		int best;
		if (maximizing) {
			best = Integer.MIN_VALUE;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) {
						Board.board[i][j] = rootPlayer;
						int val = minimax(rootPlayer, depth - 1, alpha, beta, false);
						Board.board[i][j] = 0;

						best = Math.max(best, val); 
						alpha = Math.max(alpha, best);
						if (alpha >= beta) return alpha;
					}
				}
			}
		} else {
			best = Integer.MAX_VALUE;
			int opp = 3 - rootPlayer;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) {
						Board.board[i][j] = opp;
						int val = minimax(rootPlayer, depth - 1, alpha, beta, true);
						Board.board[i][j] = 0;

						best = Math.min(best, val); 
						beta = Math.min(beta, best);
						if (alpha >= beta) return beta;
					}
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
		score += 2*winLineDiff;

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
		score += 2*availableDiff;

		return score;
	}
}
