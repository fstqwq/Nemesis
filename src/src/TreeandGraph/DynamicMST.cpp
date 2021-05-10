int n, m, q; // $ O((m+q) \log q) $
struct EdgeInfo {
int u, v, w, l, r; EdgeInfo(int u,int v,int w,int l,int r) : 
	u(u),v(v),w(w),l(l),r(r){} EdgeInfo() {} };
long long ans[N]; int find(int f[], int u) {
	return f[u] == u ? u : f[u] = find(f, f[u]); }
bool join(int f[], int u, int v){ u=find(f,u), v=find(f, v);
	if (u == v) return false; return f[u] = v, true; }
void dfs(int l, int r, int n, const vector<EdgeInfo> &list, long long base) {
	if (list.empty())
		{ for (int i=l; i<=r; i++) ans[l]=base; return ; }
	static vector<EdgeInfo> all,part;all.clear();part.clear();
	for (auto &e : list) if (e.l <= l && r <= e.r) {
			all.push_back(e);
		} else if (l <= e.r && e.l <= r) {part.push_back(e);}
	static int f[N], color[N], id[N]; // Contraction
	for (int i = 0; i < n; i++) f[i] = color[i] = i;
	for (auto &e : part) join(f, e.u, e.v);
	for (auto &e : all) if (join(f, e.u, e.v)) {
		join(color, e.u, e.v); base += e.w; }
	if (l == r) { ans[l] = base; return ; }
	for (int i = 0; i < n; i++) id[i] = -1;
	int tot = 0; for (int u = 0; u < n; u++) {
		int v = find(color, u); if (id[v] == -1) id[v] = tot++;
		id[u] = id[v]; } int m = 0; // Reduction
	for (int i = 0; i < tot; i++) f[i] = i;
	for (auto &e : part) { e.u = id[find(color, e.u)];
		e.v = id[find(color, e.v)]; }
	for (auto &e : all) {
		e.u = id[find(color, e.u)], e.v = id[find(color, e.v)];
		if (e.u == e.v) continue; assert(e.u<tot && e.v<tot);
		if (join(f, e.u, e.v)) all[m++] = e; }
	all.resize(m); vector<EdgeInfo> new_list;
	for (int i=0, j=0; i < part.size() || j < all.size(); ) {
		if(i<part.size()&&(j==all.size()||all[j].w>part[i].w)){
			new_list.push_back(part[i++]);
		} else { new_list.push_back(all[j++]); } }
	int mid = (l + r) / 2; dfs(l, mid, tot, new_list, base);
	dfs(mid + 1, r, tot, new_list, base); }
int main() { scanf("%d %d %d", &n, &m, &q);
	vector<pair<int, int> > memo; static int u[N], v[N], w[N];
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u[i], &v[i], &w[i]);
		--u[i], --v[i]; memo.push_back({0, w[i]}); }
	vector<EdgeInfo> info; // 把第 k 条边权值改为 d
	for (int i = 0; i < q; i++) {
		int k, d; scanf("%d %d", &k, &d); --k;
		if (memo[k].first < i) {
			info.push_back({u[k], v[k], memo[k].second, memo[k].first, i - 1});
		} memo[k] = {i, d}; }
	for (int i = 0; i < m; i++) {
		info.push_back({u[i], v[i], memo[i].second, memo[i].first, q - 1}); }
	sort(info.begin(), info.end(), [&](const EdgeInfo &a, const EdgeInfo &b) { return a.w < b.w; });
	dfs(0, q - 1, n, info, 0);
	for (int i = 0; i < q; i++) printf("%lld\n", ans[i]); }