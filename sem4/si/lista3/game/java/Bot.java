import java.util.Random;

class Result {
	public int score, depth;
	Result(int s, int d) {
		score = s;
		depth = d;
	}
}

public class Bot {
	private static Random r = new Random();
	private static int goal;

	public static int move(int player, int depth, int prev) {
		goal = prev;
		int bestMove = -1;
		Result best = new Result(Integer.MIN_VALUE, depth+1);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = player;

					if (Board.winCheck(player)) return (i+1)*10 + (j+1);
					if (Board.loseCheck(player)) {
						Board.board[i][j] = 0;
						continue;
					}

					Result val = minimax(player, depth - 1, new Result(Integer.MIN_VALUE, depth+1), new Result(Integer.MAX_VALUE, depth+1), false);
					
					Board.board[i][j] = 0;

					if (val.score > best.score) {best = val; bestMove = (i+1)*10 + (j+1);}
					else if (val.score == best.score) {
						if (val.depth < best.depth && val.score > goal) {best = val; bestMove = (i+1)*10 + (j+1);}
						else if (val.depth > best.depth && val.score < goal) {best = val; bestMove = (i+1)*10 + (j+1);}
						else if (val.depth == best.depth && r.nextBoolean()) {best = val; bestMove = (i+1)*10 + (j+1);}
					}
				}
			}
		}

		System.out.println("Najlepszy ruch ma wartosc: " + best.score + " znaleziony na glebokosci: " + best.depth);

		if (best.score == Integer.MIN_VALUE) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) return (i+1)*10 + (j+1);
				}
			}
		}

		return bestMove == -1 ? 0 : bestMove;
	}

	private static Result minimax(int rootPlayer, int depth, Result alpha, Result beta, boolean maximizing) {
		if (Board.winCheck(rootPlayer)) return new Result(2000, depth);
		if (Board.winCheck(3 - rootPlayer)) return new Result(-2000, depth);
		if (Board.loseCheck(rootPlayer)) return new Result(-1000, depth);
		if (Board.loseCheck(3 - rootPlayer)) return new Result(1000, depth);

		if (depth == 0) return new Result(evaluate(rootPlayer), 0);

		Result best;
		if (maximizing) {
			best = new Result(Integer.MIN_VALUE, 0);
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) {
						Board.board[i][j] = rootPlayer;
						
						Result val = minimax(rootPlayer, depth - 1, alpha, beta, false);
						if (evaluate(rootPlayer) == val.score) val.depth = depth;

						Board.board[i][j] = 0;

						if (val.score > best.score) best = val;
						else if (val.score == best.score) {
							if (val.depth < best.depth && val.score > goal) best = val;
							else if (val.depth > best.depth && val.score < goal) best = val; 
						}

						if (best.score > alpha.score) alpha = best;
						else if (best.score == alpha.score) {
							if (best.depth < alpha.depth && best.score > goal) alpha = best;
							else if (best.depth > alpha.depth && best.score < goal) alpha = best; 
						}
						if (alpha.score >= beta.score) return alpha;
					}
				}
			}
		} else {
			best = new Result(Integer.MAX_VALUE, 0);
			int opp = 3 - rootPlayer;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (Board.board[i][j] == 0) {
						Board.board[i][j] = opp;

						Result val = minimax(rootPlayer, depth - 1, alpha, beta, true);
						if (evaluate(rootPlayer) == val.score) val.depth = depth;

						Board.board[i][j] = 0;

						if (val.score < best.score) best = val;
						else if (val.score == best.score) {
							if (val.depth < best.depth && val.score < goal) best = val;
							else if (val.depth > best.depth && val.score > goal) best = val; 
						}

						if (best.score < beta.score) beta = best;
						else if (best.score == beta.score) {
							if (best.depth < beta.depth && best.score < goal) beta = best;
							else if (best.depth > beta.depth && best.score > goal) beta = best; 
						}

						if (alpha.score >= beta.score) return beta;
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
