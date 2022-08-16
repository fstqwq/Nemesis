int n, m, S, K, ans , cnt , Best[N], fa[N], FE[N]; //对点S的度数限制为K
int f[N], p[M], t[M], c[M], o, Cost[N];
bool u[M], d[M];
pair<int, int> MinCost[N];
struct Edge {
	int a, b, c;
	bool operator < (const Edge & E) const { return c < E.c; }
}E[M];
vector<int> SE;
inline int F(int x) {
	return fa[x] == x ? x : fa[x] = F(fa[x]);
}
inline void AddEdge(int a, int b, int C) {
	p[++o] = b; c[o] = C;
	t[o] = f[a]; f[a] = o;
}
void dfs(int i, int father) {
	fa[i] = father;
	if (father == S) Best[i] = -1;
	else {
		Best[i] = i;
		if (~Best[father] && Cost[Best[father]] > Cost[i]) Best[i] = Best[father];
	}
	for (int j = f[i]; j; j = t[j])
	if (!d[j] && p[j] != father) {
		Cost[p[j]] = c[j];
		FE[p[j]] = j;
		dfs(p[j], i);
	}
}
inline bool Kruskal() {
	cnt = n - 1,ans = 0; o = 1;
	for (int i = 1; i <= n; i++) fa[i] = i, f[i] = 0;
	sort(E + 1, E + m + 1);
	for (int i = 1; i <= m; i++) {
		if (E[i].b == S) swap(E[i].a, E[i].b);
		if (E[i].a != S && F(E[i].a) != F(E[i].b)) {
			fa[F(E[i].a)] = F(E[i].b);
			ans += E[i].c;
			cnt --;
			u[i] = true;
			AddEdge(E[i].a, E[i].b, E[i].c);
			AddEdge(E[i].b, E[i].a, E[i].c);
		}
	}
	for (int i = 1; i <= n; i++) MinCost[i] = make_pair(INF, INF);
	for (int i = 1; i <= m; i++)
	if (E[i].a == S) {
		SE.push_back(i);
		MinCost[F(E[i].b)] = min(MinCost[F(E[i].b)], make_pair(E[i].c, i));
	}
	int dif = 0;
	for (int i = 1; i <= n; i++)
	if (i != S && fa[i] == i) {
		if (MinCost[i].second == INF) return false;
		if (++ dif > K) return false;
		dfs(E[MinCost[i].second].b, S);
		u[MinCost[i].second] = true;
		ans += MinCost[i].first;
	}
	return true;
}
bool Solve() {
	memset(d,false,sizeof d);
	memset(u,false,sizeof u);
	if (!Kruskal()) return false;
	for (int i = cnt + 1; i <= K && i <= n; i++) {
		int MinD = INF, MinID = -1;
		for (int j = (int) SE.size() - 1; j >= 0; j--)
		if (u[SE[j]])
			SE.erase(SE.begin() + j);
		for (int j = 0; j < (int) SE.size(); j++) {
			int tmp = E[SE[j]].c - Cost[Best[E[SE[j]].b]];
			if (tmp < MinD) {
				MinD = tmp;
				MinID= SE[j];
			}
		}
		if (MinID == -1) return true;
		if (MinD >= 0) break;
		ans += MinD;
		u[MinID] = true;
		d[FE[Best[E[MinID].b]]] = d[FE[Best[E[MinID].b]] ^ 1] = true;
		dfs(E[MinID].b, S);
	}
	return true;
}
int main(){
	Solve();
	return 0;
}
