import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

class Result {
	int score;
	int depth;
	private final static Random RAND = new Random();
	public Result(int s, int d) {score = s; depth = d;}

	boolean isBetter(Result a, int previous) {
		if (this.score > a.score) return true;
		if (this.score < a.score) return false;
		if (this.depth > a.depth) return this.score >= previous ? true : false;
		if (this.depth < a.depth) return this.score >= previous ? false : true;
		return RAND.nextBoolean();
	}
}

class Move {
	int score;
	int col, row;
	public Move(int s, int c, int r) {score = s; col = c; row = r;}
}

public class NewBot {
	private static int previousScore;

	public static int move(int player, int depth) {
		previousScore = evaluate(player);
		Result bestScore = new Result(-1000000, depth+1);
		int bestMove = -1;

		System.out.println("Eval: " + previousScore);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = player;

					if (Board.winCheck(player)) return (i+1)*10 + (j+1);
					if (Board.loseCheck(player)) {
						Board.board[i][j] = 0;
						continue;
					}

					Result score = minimax(player, depth-1, new Result(-1000000, depth+1), new Result(1000000, depth+1), false);

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

	private static Result minimax(int player, int depth, Result best, Result worst, boolean maximizing) {
		if (Board.winCheck(player)) return new Result(2000, depth);
		if (Board.winCheck(3 - player)) return new Result(-2000, depth);
		if (Board.loseCheck(player)) return new Result(-1000, depth);
		if (Board.loseCheck(3 - player)) return new Result(1000, depth);

		if (depth == 0) return new Result(evaluate(player), 0);

		int opp = 3 - player;
		List<Move> moves = new ArrayList<>();
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = maximizing ? player : opp;
					moves.add(new Move(evaluate(player), i, j));
					Board.board[i][j] = 0;
				}
			}
		}
		
		Result bestScore;
		if (maximizing) {
			bestScore = new Result(-1000000, depth+1);
			moves.sort(Comparator.comparingInt(m -> -m.score));

			int n = moves.size();
			for (int i = 0; i < n; i++) {
				int c = moves.get(i).col, r = moves.get(i).row;
				if (Board.board[c][r] == 0) {
					Board.board[c][r] = player;
					Result score = minimax(player, depth-1, best, worst, false);
					Board.board[c][r] = 0;

					if (score.score == moves.get(i).score) score.depth = depth;
					if (score.isBetter(bestScore, previousScore)) bestScore = score;
					if (bestScore.isBetter(best, previousScore)) best = bestScore;
					if (best.isBetter(worst, previousScore)) return bestScore;
				}
			}
		} else {
			bestScore = new Result(1000000, depth+1);
			moves.sort(Comparator.comparingInt(m -> m.score));
			
			int n = moves.size();
			for (int i = 0; i < n; i++) {
				int c = moves.get(i).col, r = moves.get(i).row;
				if (Board.board[c][r] == 0) {
					Board.board[c][r] = opp;
					Result score = minimax(player, depth-1, best, worst, true);
					Board.board[c][r] = 0;

					if (score.score == moves.get(i).score) score.depth = depth;
					if (bestScore.isBetter(score, previousScore)) bestScore = score;
					if (worst.isBetter(bestScore, previousScore)) worst = bestScore;
					if (best.isBetter(worst, previousScore)) return bestScore;
				}
			}
		}

		return bestScore;
	}

	private static boolean equal(int[] a, int[] b) {
		for (int i = 0; i < 4; i++) 
			if (a[i] != b[i]) return false;
		return true;
	}

	// heurystyka
	private static int evaluate(int player) {
		int opp = 3 - player;
		int bonus = 0;

		int xoox = 0, oxxo = 0, three = 0, oxox = 0, xxoo = 0;

		int n = Board.win.length;
		for (int i = 0; i < n; i++) {
			int[] line = new int[4];
			int[] counter = new int[3];
			for (int j = 0; j < 4; j++) {
				line[j] = Board.board[Board.win[i][j][0]][Board.win[i][j][1]] == 0 ? 0 : 1;
				counter[Board.board[Board.win[i][j][0]][Board.win[i][j][1]]]++;
			}

			if (equal(line, new int[]{1,0,0,1})) {
				if (counter[player] > 0 && counter[opp] == 0) xoox++;
				// else if (counter[opp] > 0 && counter[player] == 0) xoox--;
				else if (counter[opp] > 0 && counter[player] == 0) {xoox--; bonus -= 200;}
			} else if (equal(line, new int[]{0,1,1,0})) {
				// if (counter[player] > 0 && counter[opp] == 0) oxxo--;
				if (counter[player] > 0 && counter[opp] == 0) {oxxo--; bonus -= 100;}
				else if (counter[opp] > 0 && counter[player] == 0) oxxo++;
			} else if (counter[player] == 3 && counter[opp] == 0) three++;
			// else if (counter[opp] == 3 && counter[player] == 0) three--;
			else if (counter[opp] == 3 && counter[player] == 0) {three--; bonus -= 300;}
			else if (equal(line, new int[]{1,0,1,0}) || equal(line, new int[]{1,0,1,0})) {
				if (counter[player] > 0 && counter[opp] == 0) oxox++;
				else if (counter[opp] > 0 && counter[player] == 0) oxox--;
			} else if (equal(line, new int[]{1,1,0,0}) || equal(line, new int[]{0,0,1,1})) {
				if (counter[player] > 0 && counter[opp] == 0) xxoo++;
				else if (counter[opp] > 0 && counter[player] == 0) xxoo--;
			}
		}

		int aval = 0;
		n = Board.lose.length;
		for (int i = 0; i < n; i++) {
			int[] counter = new int[3];
			for (int j = 0; j < 3; j++) counter[Board.board[Board.lose[i][j][0]][Board.lose[i][j][1]]]++;
			
			if (counter[opp] == 2 && counter[player] == 0) aval++; 
			if (counter[player] == 2 && counter[opp] == 0) aval--;
		}

		int score = 0;
		
		score += 5*three;
		score += 3*xoox;
		score += 3*oxxo;
		score += oxox;
		score += xxoo;
		score += 10*aval;

		return score + bonus;
	}
}