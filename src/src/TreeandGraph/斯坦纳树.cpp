LL d[1 << 10][N]; int c[15];
priority_queue < pair <LL, int> > q;
void dij(int S) {
	for (int i = 1; i <= n; i++) q.push(mp(-d[S][i], i));
	while (!q.empty()) {
		pair <LL, int> o = q.top(); q.pop();
		if (-o.x != d[S][o.y]) continue;
		int x = o.y;
		for (auto v : E[x]) if (d[S][v.v] > d[S][x] + v.w) {
			d[S][v.v] = d[S][x] + v.w;
			q.push(mp(-d[S][v.v], v.v));}}}
void solve() {
	for (int i = 1; i < (1 << K); i++)
		for (int j = 1; j <= n; j++) d[i][j] = INF;
	for (int i = 0; i < K; i++) d[1 << i][c[i]] = 0; 
	for (int S = 1; S < (1 << K); S++) {
		for (int k = S; k > (S >> 1); k = (k - 1) & S) {
			for (int i = 1; i <= n; i++) {
				d[S][i] = min(d[S][i], d[k][i] + d[S ^ k][i]);
		} }	dij(S);}}
