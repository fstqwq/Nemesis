int last, mxl[N * 2], par[N * 2], sam_cnt;
array <int, 26> go[N * 2];
void extend(int c) {
	int p = last, np = ++sam_cnt; mxl[np] = mxl[p] + 1;
	while (p && !go[p][c]) { go[p][c] = np; p = par[p]; }
	if (!p) par[np] = 1; else { int q = go[p][c];
		if (mxl[q] == mxl[p] + 1) par[np] = q;
		else { int nq = ++sam_cnt; mxl[nq] = mxl[p] + 1;
			go[nq] = go[q];
			par[nq] = par[q]; par[np] = par[q] = nq;
			while (p && go[p][c] == q) { go[p][c] = nq;
				p = par[p]; } } } last = np; }
void init() { last = sam_cnt = 1; }
int c[N], q[N * 2]; 
void solve() { // 跑完得到的q是一个合法的拓扑序, c 记得清空
	for (int i = 1; i <= sam_cnt; i++) c[mxl[i] + 1]++;
	for (int i = 1; i <= n; i++) c[i] += c[i - 1]; // n: 串长
	for (int i = 1; i <= sam_cnt; i++) q[++c[mxl[i]]] = i;}
