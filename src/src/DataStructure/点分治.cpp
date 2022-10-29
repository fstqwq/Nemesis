vector<pair<int, int> > G[maxn];
int sz[maxn], son[maxn], q[maxn];
int pr[maxn], depth[maxn], rt[maxn][19], d[maxn][19];
int cnt_all[maxn],sum_all[maxn],cnt[maxn][],sum[maxn][];
bool vis[maxn], col[maxn];
int getcenter(int o, int s) {
	int head = 0, tail = 0; q[tail++] = o;
	while (head != tail) {
		int x = q[head++]; sz[x] = 1; son[x] = 0;
		for (auto [y, _] : G[x]) if (!vis[y] && y != pr[x]) {
			pr[y] = x; q[tail++] = y; } }
	for (int i = tail - 1; i; i--) {
		int x = q[i]; sz[pr[x]] += sz[x];
		if (sz[x] > sz[son[pr[x]]]) son[pr[x]] = x; }
	int x = q[0];
	while (son[x] && sz[son[x]] * 2 >= s) x = son[x];
	return x; }
void getdis(int o, int k) {
	int head = 0, tail = 0; q[tail++] = o;
	while (head != tail) {
		int x = q[head++]; sz[x] = 1; rt[x][k] = o;
		for (auto [y, w] : G[x]) if (!vis[y] && y != pr[x]) {
			pr[y]=x; d[y][k] = d[x][k] + w; q[tail++]=y; } }
	for (int i = tail - 1; i; i--)sz[pr[q[i]]] += sz[q[i]];}
void build(int o, int k, int s, int fa) {
	int x = getcenter(o, s);
	vis[x] = true; depth[x] = k; pr[x] = fa;
	for (auto [y, w] : G[x]) if (!vis[y]) {
		d[y][k] = w; pr[y] = x; getdis(y, k); }
	for (auto [y, w] : G[x]) if (!vis[y])
		build(y, k + 1, sz[y], x); }
void modify(int x) {
	int t = col[x] ? -1 : 1; cnt_all[x] += t;
	for (int u = pr[x], k = depth[x] - 1; u; u = pr[u],k--){
		sum_all[u] += t * d[x][k]; cnt_all[u] += t;
		sum[rt[x][k]][k] += t*d[x][k]; cnt[rt[x][k]][k] += t;
	} col[x] ^= true; }
int query(int x) { int ans = sum_all[x];
	for (int u = pr[x], k = depth[x] - 1; u; u = pr[u], k--)
		ans += sum_all[u] - sum[rt[x][k]][k]
			+ d[x][k] * (cnt_all[u] - cnt[rt[x][k]][k]);
	return ans; }