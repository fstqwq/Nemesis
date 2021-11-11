// 点标号为$1, 2, \cdots, n$, 0为虚拟源点向其他点连权值为0的单向边.
// f[i][v] : 从 0 到 v 恰好经过 i 条路的最短路
ll f[N][N] = {Inf}; int u[M], v[M], w[M]; f[0][0] = 0;
for(int i = 1; i <= n + 1; i ++)
	for(int j = 0; j < m; j ++)
		f[i][v[j]] = min(f[i][v[j]], f[i - 1][u[j]] + w[j]);
double ans = Inf;
for(int i = 1; i <= n; i ++) {
	double t = -Inf;
	for(int j = 1; j <= n; j ++)
		t = max(t, (f[n][i] - f[j][i]) / (double)(n - j));
	ans = min(t, ans); }