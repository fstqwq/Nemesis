import java.util.*;
import java.math.*;
import java.text.*;
import java.io.*;

// Byte Camp 2021 Final : F
// Calulate a, b ~ Polygon, E[|a.x - b.x| + |a.y - b.y|]
public class Main {
	static class point {
		BigDecimal x, y;
		point () {}
		point (int xx, int yy) {x = new BigDecimal(xx); y = new BigDecimal(yy);}
		point (BigDecimal xx, BigDecimal yy) {x = xx; y = yy;}

		point add(point a) {
			return new point(x.add(a.x), y.add(a.y));
		}
		point sub(point a) {
			return new point(x.subtract(a.x), y.subtract(a.y));
		}
	}

	static BigDecimal det(point a, point b) {return a.x.multiply(b.y).subtract(b.x.multiply(a.y));}

	static BigDecimal ans, S, C;
	static MathContext fuckJava = new MathContext(100, RoundingMode.HALF_EVEN); 

	static BigDecimal getlen(point a1, point a2, point b1, point b2, BigDecimal x) {
		BigDecimal k1 = a2.y.subtract(a1.y).divide(a2.x.subtract(a1.x), fuckJava);
		BigDecimal k2 = b2.y.subtract(b1.y).divide(b2.x.subtract(b1.x), fuckJava);
		BigDecimal p1 = x.subtract(a1.x).multiply(k1).add(a1.y), p2 = x.subtract(b1.x).multiply(k2).add(b1.y);
		return p2.subtract(p1).abs();
	}
	/* ... */
	
	static int n;
	static point[] a = new point[31111];
	static List<point> p = new ArrayList<>();

	static void work() {
		BigDecimal minx = BigDecimal.TEN.pow(18);
		int id = 0;
		for (int i = 0; i < n; i++) {
			if (a[i].x.compareTo(minx) < 0) {
				minx = a[i].x;
				id = i;
			}
		}
		p.clear();
		for (int i = id; i < n; i++) p.add(a[i]);
		for (int i = 0; i < id; i++) p.add(a[i]);
		p.add(p.get(0));

		C = BigDecimal.ZERO;
		int l = 1, r = n - 1;
		for ( ; ; ) {
			solve(p.get(l - 1), p.get(l), p.get(r + 1), p.get(r));
			if (l == r) break;
			if (p.get(l).x.compareTo(p.get(r).x) < 0) {
				l++;
			} else {
				r--;
			} } } 
	static Scanner scanner;
	public static void main(String[] args) {
		scanner = new Scanner(new BufferedInputStream(System.in));
		n = scanner.nextInt();
		ans = BigDecimal.ZERO;
		for (int i = 0; i < n; i++) {
			int x = scanner.nextInt();
			a[i] = new point();
			a[i].x = new BigDecimal(x);
		}
		for (int i = 0; i < n; i++) {
			int x = scanner.nextInt();
			a[i].y = new BigDecimal(x);
		}
		S = BigDecimal.ZERO;
		for (int i = 1; i < n - 1; i++) {
			S = S.add(det(a[i].sub(a[0]), a[i + 1].sub(a[0])));
		}
		S = S.divide(BigDecimal.valueOf(2), fuckJava);
		work();
		for (int i = 0; i < n; i++) {
			BigDecimal t = a[i].x;
			a[i].x = a[i].y;
			a[i].y = t;
		}
		work();
		ans = ans.divide(S.multiply(S), fuckJava).multiply(new BigDecimal(2));

		System.out.println(new DecimalFormat("0.0000000000000").format(ans))

//		ans = ans.setScale(20, RoundingMode.HALF_EVEN);
//		System.out.println( ans.stripTrailingZeros().toPlainString());

//		System.out.printf("%.9f\n", ans.doubleValue());
	}
}


// Closest Pair of Points

public class Main {

	public static final int N = 111111;
	public static final long INF = (1l << 63) - 1; 

	static class point implements Comparable<point> {
		long x, y;
		public point () {}
		public point (long xx, long yy) {x = xx; y = yy;}
		public int compareTo(point b) {
			return y > b.y ? 1 : (y < b.y ? -1 : 0);
		}
	}
	static point[] p;

	static long sqr(long x) {
		return x * x;
	}
	static long solve(int l, int r) {
		if (l + 1 >= r) return INF;
		int m = (l + r) / 2;
		long mx = p[m].x;
		List <point> v = new ArrayList<>();
		long ret = Long.min(solve(l, m), solve(m, r));
		for (int i = l; i < r; i++) {
			if (sqr(p[i].x - mx) < ret) v.add(p[i]);
		}
		Collections.sort(v);
		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {
				if (sqr(v.get(i).y - v.get(j).y) > ret) break;
				ret = Long.min(ret, sqr(v.get(i).y - v.get(j).y) + sqr(v.get(i).x - v.get(j).x));
			}
		}
		v.clear();
		return ret;
	}

	static class InputReader { // Fast Reader
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null; }
		public String next() {
			while (tokenizer==null||!tokenizer.hasMoreTokens()) {
				try { String line = reader.readLine();
					tokenizer = new StringTokenizer(line);
				} catch (IOException e) {
					throw new RuntimeException(e); }
			} return tokenizer.nextToken(); }
		public int nextInt() {
			return Integer.valueOf(next());
		}
	 }

	public static void main(String[] args) {
		InputReader in = new InputReader(System.in);
		int n = in.nextInt();
		p = new point[n];
		for (int i = 0; i < n; i++) {
			int x = in.nextInt();
			int y = in.nextInt();
			p[i] = new point(x, y);	
		}
		Arrays.sort(p, new Comparator <point>() {
			public int compare(point a, point b) { return a.x > b.x ? 1 : (a.x < b.x ? -1 : 0); }
		});
		System.out.printf("%.4f\n", Math.sqrt(solve(0, n)));
	}
}
// Yinchuan 2019, I. Base62
public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(new BufferedInputStream(System.in));
		int x = in.nextInt();
		int y = in.nextInt();
		String z = in.next();
		int n = z.length();
		BigInteger val = BigInteger.ZERO;
		for (int i = 0; i < n; i++) {
			char ch = z.charAt(i);
			int v;
			if (ch >= '0' && ch <= '9') v = ch - '0';
			else if (ch >= 'A' && ch <= 'Z') v = ch - 'A' + 10;
			else v = ch - 'a' + 36;
			val = val.multiply(BigInteger.valueOf(x)) .add(BigInteger.valueOf(v));
		}
		StringBuilder ans = new StringBuilder();
		while (val.compareTo(BigInteger.ZERO) > 0) {
			int last = val.mod(BigInteger.valueOf(y)).intValue();
			if (last < 10) ans.append((char)('0' + last));
			else if (last < 36) ans.append((char)('A' + last - 10));
			else ans.append((char)('a' + last - 36));
			val = val.divide(BigInteger.valueOf(y));
		}
		String s = ans.reverse().toString();
		System.out.println(s.length() == 0 ? "0" : s);
	} 
}

