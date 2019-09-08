// 左侧N个点, 右侧K个点 ,1-base, 初始化将matx[],maty[]都置为0
int N, K, que[N], dx[N], dy[N], matx[N], maty[N];
int BFS() { int flag = 0, qt = 0, qh = 0;
	for(int i = 1; i <= K; ++ i) dy[i] = 0;
	for(int i = 1; i <= N; ++ i) { dx[i] = 0;
		if (! matx[i]) que[qt ++] = i; }
	while (qh < qt) { int u = que[qh ++];
		for(Edge *e = E[u]; e; e = e->n) {
			if (! dy[e->t]) { dy[e->t] = dx[u] + 1;
				if (! maty[e->t]) flag = true; else {
					dx[maty[e->t]] = dx[u] + 2;
					que[qt ++] = maty[e->t]; } } } }
	return flag; }
int DFS(int u) {
	for(Edge *e = E[u]; e; e = e->n) {
		if (dy[e->t] == dx[u] + 1) { dy[e->t] = 0;
			if (! maty[e->t] || DFS(maty[e->t])) {
				matx[u] = e->t; maty[e->t] = u; return true; }}}
	return false; }
void Hopcroft() {
while (BFS()) for(int i=1; i<=N; ++i) if (!matx[i]) DFS(i);}