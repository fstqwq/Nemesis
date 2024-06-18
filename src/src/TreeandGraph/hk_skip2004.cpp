vector <int> E[N];
vector <int> ml, mr, a, p;
void match (int nl, int nr) { // 1-based
	ml.assign(nl + 1, 0);
	mr.assign(nr + 1, 0); // nr
	while (true) {
		bool ok = 0;
		a.assign(nl + 1, 0);
		p.assign(nl + 1, 0); // nl
		static queue <int> q;
		for (int i = 1; i <= nl; i++)
			if (!ml[i]) a[i] = p[i] = i, q.push(i);
		while (!q.empty()) {
			int x = q.front(); q.pop();
			if (ml[a[x]]) continue;
			for (auto y : E[x]) {
				if (!mr[y]) {
					for (ok = 1; y; x = p[x])
						mr[y] = x, swap(ml[x], y);
					break;
				} else if (!p[mr[y]])
					q.push(y = mr[y]), p[y] = x, a[y] = a[x];
			} } // while (!q.empty())
		if (!ok) break; } }
array<vector<int>, 2> min_edge_cover(int nl, int nr) {
 match(nl, nr); vector <int> l, r;
 for (int i = 1; i <= nl; i++) if (!a[i]) l.push_back(i);
 for (int i = 1; i <= nr; i++) if (a[mr[i]]) r.push_back(i);
 return {l, r}; }