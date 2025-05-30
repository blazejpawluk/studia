import java.util.Random;

class Move {
	int score;
	int depth;
	private final static Random RAND = new Random();
	public Move(int s, int d) {score = s; depth = d;}

	boolean isBetter(Move a, int previous) {
		if (this.score > a.score) return true;
		if (this.score < a.score) return false;
		if (this.depth > a.depth) return this.score >= previous ? true : false;
		if (this.depth < a.depth) return this.score >= previous ? false : true;
		return RAND.nextBoolean();
	}
}

public class Bot {
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

		Move bestScore = maximizing
				? new Move(-1000000, depth + 1)
				: new Move(1000000, depth + 1);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					int current = maximizing ? player : 3 - player;
					Board.board[i][j] = current;

					Move score = minimax(player, depth - 1, best, worst, !maximizing);

					Board.board[i][j] = 0;

					if (maximizing) {
						if (score.isBetter(bestScore, previousScore)) bestScore = score;
						if (bestScore.isBetter(best, previousScore)) best = bestScore;
						// if (best.isBetter(worst, previousScore)) break;
						if (best.isBetter(worst, previousScore)) return bestScore;
					} else {
						if (bestScore.isBetter(score, previousScore)) bestScore = score;
						if (worst.isBetter(bestScore, previousScore)) worst = bestScore;
						// if (best.isBetter(worst, previousScore)) break;
						if (best.isBetter(worst, previousScore)) return bestScore;
					}
				}
			}
			// if (best.isBetter(worst, previousScore)) break;
		}
		return bestScore;
	}

	// heurystyka
	private static int evaluate(int player) {
		int opp = 3 - player;

		int move = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] != 0) move++;
			}
		}

		int m3 = 0, m2 = 0, availableWinLines = 0;
		for (int[][] line : Board.win) {
			int[] count = new int[3];
			for (int i = 0; i < 4; i++) count[Board.board[line[i][0]][line[i][1]]]++;

			// 3 zajęte i 1 puste w linii: max = 28
			if (count[player] == 3 && count[0] == 1) m3++;
			if (count[opp] == 3 && count[0] == 1) m3--;

			// 2 zajęte i 2 puste w linii: max = 28
			if (count[player] == 2 && count[0] == 2) m2++;
			if (count[opp] == 2 && count[0] == 2) m2--;

			// wolne linie wygrywające: max = 28
			if (count[opp] == 0) availableWinLines++;
			if (count[player] == 0) availableWinLines--;
		}
		
		// różnica dostępnych przegrywających linii: max = 48
		int loseLineDiff = 0;
		for (int[][] line : Board.lose) {
			boolean canWinPlayer = true;
			boolean canWinOpp = true;
			for (int[] p : line) {
				int val = Board.board[p[0]][p[1]];
				if (val == opp) canWinPlayer = false;
				if (val == player) canWinOpp = false;
			}
			if (canWinPlayer) loseLineDiff--;
			if (canWinOpp) loseLineDiff++;
		}
		
		// różnica dostępnych (nie powodujących natychmiastowej przegranej) ruchów: max = 25
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

		// score += move > 6 ? 4*m3 : 0;
		score += 4*m3;
		// score += move > 6 ? 2*m2 : 0;
		score += 2*m2;
		score += 4*availableWinLines;
		// score += (move > 6 ? 1 : 2) * loseLineDiff;
		// score += 2*loseLineDiff;
		score += 2*loseLineDiff;
		score += 4*availableDiff;
		// max = 4*28 + 2*28 + 4*28 + 48 + 4*25 = 428

		return score;
	}
}