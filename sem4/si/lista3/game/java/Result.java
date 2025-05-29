import java.util.Random;

public class Result {
		public int eval;
		public int moves;

		public Result(int eval, int moves) {
			this.eval = eval;
			this.moves = moves;
		}

		public static Result returnBetter(Result a, Result b, Random r) {
			if (a.eval > b.eval) return a;
			if (b.eval > a.eval) return b;

			if (a.eval >= 0) {
				if (a.moves < b.moves) return a;
				if (b.moves > a.moves) return b;
				return (r.nextBoolean() ? a : b);
			} else {
				if (a.moves > b.moves) return a;
				if (b.moves < a.moves) return b;
				return (r.nextBoolean() ? a : b);
			}
		}

		public static Result returnWorse(Result a, Result b, Random r) {
			return (returnBetter(a, b, r).equals(a) ? b : a);
		}

		public boolean isBetter(Result a, Random r) {
			return (returnBetter(this, a, r).equals(this) ? true : false);
		}
	}