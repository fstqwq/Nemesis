struct edge { int u, v, w, id; } edges[maxm];
void undo(int x) { sz[ufs[x]] -= sz[x]; ufs[x] = x; }
int vis[maxm], now;
void reduction(int l, int r, vector<edge> &vec) {
	now++;
	for (int i = l; i <= r; i++) // a是操作，3是询问
		if (a[i].op != 3)vis[a[i].id] = now;
	vector<edge> ret; ret.reserve(vec.size());

	int tmp = top;

	for (auto &e : vec)
		if (vis[e.id] < now) {
			int u = findufs(e.u), v = findufs(e.v);
			if (u != v) { link(e.u, e.v, true);
				ret.push_back(e); } }
		else ret.push_back(e);
	for (int i = top; i > tmp; i--) undo(stk[i]);
	top = tmp; vec = move(ret); }

void contraction(int l, int r, vector<edge> &vec) {
	now++;

	int tmp = top;

	for (int i = l; i <= r; i++)
		if (a[i].op != 3 && vis[a[i].id] < now) {
			vis[a[i].id] = now;

			int u = findufs(a[i].u), v = findufs(a[i].v);
			if (u != v)
				link(u, v, true);
		}

	vector<edge> must, ret;
	must.reserve(vec.size());
	ret.reserve(vec.size());
	
	for (auto &e : vec)
		if (vis[e.id] < now) {
			int u = findufs(e.u), v = findufs(e.v);
			if (u != v) {
				link(u, v, true);
				must.push_back(e);
				// cerr << "must, u = " << e.u << ", v = " << e.v << endl;
			}
			else
				ret.push_back(e);
		}
		else
			ret.push_back(e);

	for (int i = top; i > tmp; i--)
		undo(stk[i]);
	top = tmp;
	
	vec = move(ret);

	for (auto &e : must) {
		int u = findufs(e.u), v = findufs(e.v);
		assert(u != v);
		link(u, v, true);
		join(null + e.u, null + e.v, e.w);
	}
}

int ans[maxm], global_m;

int fuck_cnt = 0;

void solve(int l, int r, vector<edge> vec) {
	assert(is_sorted(vec.begin(), vec.end(), [](auto &a, auto &b) {
		return a.w < b.w;
	}));

	assert(all_of(vec.begin(), vec.end(), [&r](auto &e) {
		return e.id <= global_m + r;
	}));

	if (none_of(a + l, a + r + 1, [](auto &o) {
		return o.op == 3;
	}))
		return;

	if (l == r) {
		int tmp = top;
		for (auto &e : vec) {
			int u = findufs(e.u), v = findufs(e.v);
			if (u != v) {
				link(u, v, true);
				join(null + e.u, null + e.v, e.w);
			}
		}

		int u = a[l].u, v = a[l].v;
		if (findufs(u) != findufs(v))
			ans[a[l].id] = -1;
		else
			ans[a[l].id] = query(null + a[l].u, null + a[l].v);
		for (int i = top; i > tmp; i--) {
			undo(stk[i]);
		}
		top = tmp;

		return;
	}

	int tmp = top;

	reduction(l, r, vec);

	contraction(l, r, vec);

	int mid = (l + r) / 2;

	vector<edge> ret;
	ret.reserve(vec.size());

	for (auto &e : vec)
		if (e.id <= global_m + mid)
			ret.push_back(e);

	solve(l, mid, move(ret));

	ret.clear();
	ret.reserve(vec.size());

	now++;
	for (int i = l; i <= mid; i++)
		if (a[i].op == 2)
			vis[a[i].id] = now;

	for (auto &e : vec)
		if (vis[e.id] < now)
			ret.push_back(e);
	
	vec.clear();
	vec.shrink_to_fit();
	solve(mid + 1, r, move(ret));

	for (int i = top; i > tmp; i--)
		undo(stk[i]);
	top = tmp;
}