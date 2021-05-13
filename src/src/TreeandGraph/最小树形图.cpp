struct UnionFind {
	int fa[N * 2];
	UnionFind() { memset(fa, 0, sizeof(fa)); }
	void clear(int n) { memset(fa + 1, 0, sizeof(int) * n); }
	int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
	int operator[](int x) { return find(x); } };
struct Edge { int u, v, w, w0; };
struct Heap {
	Edge *e;
	int rk, constant;
	Heap *lch, *rch;
	Heap(Edge *_e) : e(_e), rk(1), constant(0), lch(NULL), rch(NULL) {}
	void push() {
		if (lch) lch->constant += constant;
		if (rch) rch->constant += constant;
		e->w += constant;
		constant = 0; } };
Heap *merge(Heap *x, Heap *y) {
	if (!x) return y;
	if (!y) return x;
	if (x->e->w + x->constant > y->e->w + y->constant) swap(x, y);
	x->push();
	x->rch = merge(x->rch, y);
	if (!x->lch || x->lch->rk < x->rch->rk) swap(x->lch, x->rch);
	if (x->rch) x->rk = x->rch->rk + 1;
	else x->rk = 1;
	return x;
}
Edge *extract(Heap *&x) {
	Edge *r = x->e; x->push();
	x = merge(x->lch, x->rch);
	return r;
}
vector<Edge> in[N];
int n, m, fa[N * 2], nxt[N * 2];
Edge *ed[N * 2];
Heap *Q[N * 2];
UnionFind id;
void contract() {
	bool mark[N * 2];
	/* 将图上的每一个结点与其相连的那些结点进行记录 */
	for (int i = 1; i <= n; i++) {
		queue<Heap *> q;
		for (int j = 0; j < in[i].size(); j++) q.push(new Heap(&in[i][j]));
		while (q.size() > 1) {
		  auto u = q.front(); q.pop();
		  auto v = q.front(); q.pop();
		  q.push(merge(u, v)); }
		Q[i] = q.front(); }
	mark[1] = true;
	for (int a = 1, b = 1, p; Q[a]; b = a, mark[b] = true) {
		/* 找最小入边及其端点,保证无环 */
		do {
		  ed[a] = extract(Q[a]);
		  a = id[ed[a]->u];
		} while (a == b && Q[a]);
		if (a == b) break;
		if (!mark[a]) continue;
		/* 收缩环,环内的结点重编号,总权值更新 */
		for (a = b, n++; a != n; a = p) {
		  id.fa[a] = fa[a] = n;
		  if (Q[a]) Q[a]->constant -= ed[a]->w;
		  Q[n] = merge(Q[n], Q[a]);
		  p = id[ed[a]->u];
		  nxt[p == n ? b : p] = a;
		} } }

LL expand(int x, int r);
LL expand_iter(int x) {
	LL r = 0;
	for (int u = nxt[x]; u != x; u = nxt[u]) {
		if (ed[u]->w0 >= INF) return INF;
		else r += expand(ed[u]->v, u) + ed[u]->w0; }
	return r;
}
LL expand(int x, int t) {
	LL r = 0;
	for (; x != t; x = fa[x]) {
		r += expand_iter(x);
		if (r >= INF) return INF; }
	return r;
}
void adde(int u, int v, int w){
	in[v].push_back({u, v, w, w}); }

int main() {
	int rt;
	scanf("%d %d %d", &n, &m, &rt);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adde(u, v, w); }
	/* 保证强连通 */
	for (int i = 1; i <= n; i++)
		adde(i > 1 ? i - 1 : n, i, INF);
	contract();
	LL ans = expand(rt, n);
	if (ans >= INF) puts("-1");
	else printf("%lld\n", ans); }
