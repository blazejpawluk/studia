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

public class Bot {
	private static int previousScore;

	public static int move(int player, int depth) {
		int move = Library.move();
		int lib = -1;
		if (move <= depth) lib = Library.giveMove();
		if (lib != -1) {
			System.out.println(lib);
			return lib;
		}
		previousScore = evaluate(player, true);
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

	private static Result minimax(int player, int depth, Result alpha, Result beta, boolean maximizing) {
		if (Board.winCheck(player)) return new Result(20000, depth); // pewna wygrana
		if (Board.winCheck(3 - player)) return new Result(-20000, depth); // pewna porazka
		if (Board.loseCheck(player)) return new Result(-10000, depth); // pewny brak wygranej
		if (Board.loseCheck(3 - player)) return new Result(10000, depth); // pewny brak porazki

		if (depth == 0) return new Result(evaluate(player, maximizing), 0);

		int opp = 3 - player;

		// lista dostepnych ruchow, w pozniejszej fazie sortowana, aby alfa-beta ciecia byly bardziej efektywne
		List<Move> moves = new ArrayList<>();
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Board.board[i][j] == 0) {
					Board.board[i][j] = maximizing ? player : opp;
					moves.add(new Move(evaluate(player, maximizing), i, j));
					Board.board[i][j] = 0;
				}
			}
		}
		
		if (maximizing) {
			moves.sort(Comparator.comparingInt(m -> -m.score));

			int n = moves.size();
			for (int i = 0; i < n; i++) {
				int c = moves.get(i).col, r = moves.get(i).row;
				if (Board.board[c][r] == 0) {
					Board.board[c][r] = player;
					Result score = minimax(player, depth-1, alpha, beta, false);
					Board.board[c][r] = 0;

					if (score.score == moves.get(i).score) score.depth = depth;
					if (score.isBetter(alpha, previousScore)) alpha = score;
					if (alpha.isBetter(beta, previousScore)) return alpha;

				}
			}

			return alpha;
		} else {
			moves.sort(Comparator.comparingInt(m -> m.score));
			
			int n = moves.size();
			for (int i = 0; i < n; i++) {
				int c = moves.get(i).col, r = moves.get(i).row;
				if (Board.board[c][r] == 0) {
					Board.board[c][r] = opp;
					Result score = minimax(player, depth-1, alpha, beta, true);
					Board.board[c][r] = 0;

					if (score.score == moves.get(i).score) score.depth = depth;
					if (beta.isBetter(score, previousScore)) beta = score;
					if (alpha.isBetter(beta, previousScore)) return beta;
				}
			}

			return beta;
		}
	}

	private static final int[][] T1 = {
		{1,1,0,1},{1,1,3,1},{1,1,4,1},{1,1,5,1},
		{1,0,1,1},{1,3,1,1},{1,4,1,1},{1,5,1,1},
		{1,3,0,1},{1,3,3,1},{1,4,0,1},{1,4,3,1},{1,5,0,1},{1,5,3,1},
		{1,0,3,1},{1,0,4,1},{1,3,4,1},{1,0,5,1},{1,3,5,1},
		{1,3,1,0},{1,3,1,3},{1,4,1,0},{1,4,1,3},{1,5,1,0},{1,5,1,3},
		{0,1,3,1},{3,1,3,1},{0,1,4,1},{3,1,4,1},{0,1,5,1},{3,1,5,1},
		{1,1,3,0},{1,1,3,3},{1,1,4,0},{1,1,4,3},{1,1,5,0},{1,1,5,3},
		{0,3,1,1},{0,4,1,1},{0,5,1,1},{3,3,1,1},{3,4,1,1},{3,5,1,1}
	};

	private static boolean checkT1(int[] line) {
		for (int[] t : T1) {
			boolean ok = true;
			for (int i = 0; i < 4; i++) {
				if (t[i] != line[i]) {
					ok = false; 
					break;
				}
			}
			if (ok) return true;
		}
		return false;
	}

	private static final int[][] T2 = {
		{2,2,0,2},{2,2,3,2},{2,2,4,2},{2,2,5,2},
		{2,0,2,2},{2,3,2,2},{2,4,2,2},{2,5,2,2},
		{2,3,0,2},{2,3,4,2},{2,4,0,2},{2,4,4,2},{2,5,0,2},{2,5,4,2},
		{2,0,3,2},{2,4,3,2},{2,0,4,2},{2,0,5,2},{2,4,5,2},
		{2,3,2,0},{2,3,2,4},{2,4,2,0},{2,4,2,4},{2,5,2,0},{2,5,2,4},
		{0,2,3,2},{4,2,3,2},{0,2,4,2},{4,2,4,2},{0,2,5,2},{4,2,5,2},
		{2,2,3,0},{2,2,3,4},{2,2,4,0},{2,2,4,4},{2,2,5,0},{2,2,5,4},
		{0,3,2,2},{0,4,2,2},{0,5,2,2},{4,3,2,2},{4,4,2,2},{4,5,2,2}
	};

	private static boolean checkT2(int[] line) {
		for (int[] t : T2) {
			boolean ok = true;
			for (int i = 0; i < 4; i++) {
				if (t[i] != line[i]) {
					ok = false; 
					break;
				}
			}
			if (ok) return true;
		}
		return false;
	}

	// heurystyka
	private static int evaluate(int player, boolean playing) {
		int opp = 3 - player;

		int win = 0, lose = 0, unavailable = 0, free = 0, block = 0;
		for (int[][] line : Board.win) {
			int[] t = new int[4];
			int countP = 0, countO = 0;
			for (int i = 0; i < 4; i++) {
				if (Board.board[line[i][0]][line[i][1]] == player) {
					countP++;
					t[i] = player;
				}
				else if (Board.board[line[i][0]][line[i][1]] == opp) {
					countO++;
					t[i] = opp;
				}
				else {
					boolean loseP = Board.loses(player, line[i][0], line[i][1]);
					boolean loseO = Board.loses(opp, line[i][0], line[i][1]);
					if (loseP && loseO) t[i] = 5;
					else if (loseP) {
						t[i] = opp+2;
						unavailable--;
					}
					else if (loseO) {
						t[i] = player+2;
						unavailable++;
					}
					else t[i] = 0;
				}
			}

			boolean t1 = checkT1(t), t2 = checkT2(t);
			if (player == 1) {
				if (playing) {
					if (t1) return 2000;
					if (t2) lose++;
				} else {
					if (t2) return -2000;
					if (t1) win++;
				}
			} else {
				if (playing) {
					if (t2) return 2000;
					if (t1) lose++;
				} else {
					if (t1) return -2000;
					if (t2) win++;
				}
			}

			if (countP == 0) free--;
			if (countO == 0) free++;
			if (countP > 0 && countO > 1) block++;
			else if (countO > 0 && countP > 1) block--;
		}

		if (playing && lose > 1) return -1000;
		if (!playing && win > 1) return 1000;

		return (win-lose)*1 + unavailable*7 + free*3 + block*1;
	}
}