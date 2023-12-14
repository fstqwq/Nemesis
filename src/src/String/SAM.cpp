int last, val[MAXN], par[MAXN], go[MAXN][26], sam_cnt;
void extend(int c) { // 结点数要开成串长的两倍
	int p = last, np = ++sam_cnt; val[np] = val[p] + 1;
	while (p && !go[p][c]) { go[p][c] = np; p = par[p]; }
	if (!p) par[np] = 1; else { int q = go[p][c];
		if (val[q] == val[p] + 1) par[np] = q;
		else { int nq = ++sam_cnt; val[nq] = val[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));
			par[nq] = par[q]; par[np] = par[q] = nq;
			while (p && go[p][c] == q) { go[p][c] = nq;
				p = par[p]; } } } last = np; }
void init() { last = sam_cnt = 1; }
int c[MAXN], q[MAXN]; 
void solve() { // 跑完得到的q是一个合法的拓扑序
	for (int i = 1; i <= sam_cnt; i++) c[val[i] + 1]++;
	for (int i = 1; i <= n; i++) c[i] += c[i - 1];
	for (int i = 1; i <= sam_cnt; i++) q[++c[val[i]]] = i;}
