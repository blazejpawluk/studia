import java.util.Random;

class Move {
	int score;
	int depth;
	Move(int s, int d) {score = s; depth = d;}

	boolean isBetter(Move a, int previous) {
		if (this.score > a.score) return true;
		if (this.score < a.score) return false;
		if (this.depth > a.depth) return this.score > previous ? true : false;
		if (this.depth < a.depth) return this.score > previous ? false : true;
		return new Random().nextBoolean();
	}
}

public class NewBot {
	private static int previousScore;
	public static int move(int player, int depth) {
		previousScore = evaluate(player);
		Move bestScore = new Move(-1000000, depth+1);
		int bestMove = -1;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = player;

					if (Board.winCheck(player)) return (i+1)*10 + (j+1);
					if (Board.loseCheck(player)) {
						Board.board[i][j] = 0;
						continue;
					}

					Move score = minimax(player, depth-1, new Move(-1000000, depth+1), new Move(1000000, depth+1), false);

					Board.board[i][j] = 0;

					if (score.isBetter(bestScore, previousScore)) {
						bestScore = score;
						bestMove = (i+1)*10 + (j+1);
					}
				}
			}
		}

		System.out.println("Best move: " + bestScore.score + " on " + bestScore.depth);

		// wszystkie ruchy prowadza do porazki
		if (bestScore.score == -1000000) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) return (i+1)*10 + (j+1);
				}
			}
		}

		// -1 gdy nie ma wolnych pol
		return bestMove == -1 ? 0 : bestMove;
	}

	private static Move minimax(int player, int depth, Move best, Move worst, boolean maximizing) {
		if (Board.winCheck(player)) return new Move(2000, depth);
		if (Board.winCheck(3 - player)) return new Move(-2000, depth);
		if (Board.loseCheck(player)) return new Move(-1000, depth);
		if (Board.loseCheck(3 - player)) return new Move(1000, depth);

		if (depth == 0) return new Move(evaluate(player), 0);

		Move bestScore;
		if (maximizing) {
			bestScore = new Move(-1000000, depth+1);
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) {
						Board.board[i][j] = player;

						Move score = minimax(player, depth-1, best, worst, false);

						Board.board[i][j] = 0;

						if (score.isBetter(bestScore, previousScore)) bestScore = score;
						if (bestScore.isBetter(best, previousScore)) best = bestScore;
						if (best.isBetter(worst, previousScore)) return bestScore;
					}
				}
			}
		} else {
			bestScore = new Move(1000000, depth+1);
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) {
						Board.board[i][j] = 3-player;

						Move score = minimax(player, depth-1, best, worst, true);

						Board.board[i][j] = 0;

						if (!score.isBetter(bestScore, previousScore)) bestScore = score;
						if (!bestScore.isBetter(worst, previousScore)) worst = bestScore;
						if (best.isBetter(worst, previousScore)) return bestScore;
					}
				}
			}
		}
		return bestScore;
	}

	// heurystyka
	private static int evaluate(int player) {
		int opp = 3 - player;
		
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
		
		int score = 0;
		score += 20*winLineDiff;
		score += 10*loseLineDiff;
		score += 20*availableDiff;

		return score;
	}
}