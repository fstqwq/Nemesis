template <int MAXN = 100000, int MAXM = 100000>
struct flow_edge_list { int size;
int begin[MAXN], dest[MAXM], next[MAXM],flow[MAXM],inv[MAXM];
void clear(int n) { size=0; std::fill(begin, begin+n, -1); }
flow_edge_list (int n = MAXN) { clear (n); }
void add_edge (int u, int v, int f) {
	dest[size] = v; next[size] = begin[u]; flow[size] = f;
	inv[size] = size + 1; begin[u] = size++;
	dest[size] = u; next[size] = begin[v]; flow[size] = 0;
	inv[size] = size - 1; begin[v] = size++; } };
template <int MAXN = 1000, int MAXM = 100000>
struct dinic { int n, s, t; int d[MAXN], w[MAXN], q[MAXN];
int bfs (flow_edge_list <MAXN, MAXM> &e) {
	for (int i = 0; i < n; ++i) d[i] = -1; int l, r;
	q[l = r = 0] = s, d[s] = 0;
	for (; l <= r; l ++)
		for (int k = e.begin[q[l]]; k > -1; k = e.next[k])
			if (d[e.dest[k]] == -1 && e.flow[k] > 0)
				d[e.dest[k]] = d[q[l]]+1, q[++r] = e.dest[k];
	return d[t] > -1 ? 1 : 0; }
int dfs (flow_edge_list <MAXN, MAXM> &e, int u, int ext) {
	if (u == t) return ext; int k = w[u], ret = 0;
	for (; k>-1; k=e.next[k], w[u] = k) { if (ext==0) break;
		if (d[e.dest[k]] == d[u] + 1 && e.flow[k] > 0) {
			int flow=dfs(e, e.dest[k], std::min(e.flow[k],ext));
			if (flow > 0) {
				e.flow[k] -= flow, e.flow[e.inv[k]] += flow;
				ret += flow, ext -= flow; } } }
	if (k == -1) d[u] = -1; return ret; }
int solve(flow_edge_list<MAXN, MAXM> &e,int n,int s,int t) {
	int ans = 0; dinic::n = n; dinic::s = s; dinic::t = t;
	while (bfs (e)) {
		for (int i = 0; i < n; ++i) w[i] = e.begin[i];
		ans += dfs (e, s, INF); } return ans; } };