template <int MAXN = 500>
struct kuhn_munkres {
	int n, w[MAXN][MAXN], lx[MAXN], ly[MAXN], m[MAXN], way[MAXN], sl[MAXN];
	bool u[MAXN];
	void hungary(int x) {
		m[0] = x;  int j0 = 0;
		std::fill (sl, sl + n + 1, INF); std::fill (u, u + n + 1, false);
		do {
			u[j0] = true; int i0 = m[j0], d = INF, j1 = 0;
			for (int j = 1; j <= n; ++j) 
				if (u[j] == false) {
					int cur = -w[i0][j] - lx[i0] - ly[j];
					if (cur < sl[j]) { sl[j] = cur; way[j] = j0; }
					if (sl[j] < d) { d = sl[j]; j1 = j; } }
			for (int j = 0; j <= n; ++j) {
				if (u[j]) { lx[m[j]] += d; ly[j] -= d; }
				else sl[j] -= d; }
			j0 = j1; } while (m[j0] != 0);
		do {
			int j1 = way[j0]; m[j0] = m[j1]; j0 = j1;
		} while (j0); }
	int solve() {
		for (int i = 1; i <= n; ++i) m[i] = lx[i] = ly[i] = way[i] = 0;
		for (int i = 1; i <= n; ++i) hungary (i);
		int sum = 0; for (int i = 1; i <= n; ++i) sum += w[m[i]][i];
		return sum; } };
