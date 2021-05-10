struct KM {
int n, nl, nr;
LL a[N][N];
LL hl[N], hr[N], slk[N];
int fl[N], fr[N], vl[N], vr[N], pre[N], q[N], ql, qr;
int check(int i) {
	if (vl[i] = 1, fl[i] != -1)
		return vr[q[qr++] = fl[i]] = 1;
	while (i != -1) swap(i, fr[fl[i] = pre[i]]);
	return 0; }
void bfs(int s) {
	fill(slk, slk + n, INF);
	fill(vl, vl + n, 0); fill(vr, vr + n, 0);
	q[ql = 0] = s; vr[s] = qr = 1;
	for (LL d;;) {
		for (; ql < qr; ++ql)
		for (int i = 0, j = q[ql]; i < n; ++i)
		if (d=hl[i]+hr[j]-a[i][j], !vl[i] && slk[i] >= d) {
			if (pre[i] = j, d) slk[i] = d;
			else if (!check(i)) return; }
		d = INF;
		for (int i = 0; i < n; ++i)
		if (!vl[i] && d > slk[i]) d = slk[i];
		for (int i = 0; i < n; ++i) {
			if (vl[i]) hl[i] += d; else slk[i] -= d;
			if (vr[i]) hr[i] -= d; }
		for (int i = 0; i < n; ++i)
			if (!vl[i] && !slk[i] && !check(i)) return; } }
void solve() {
	n = max(nl, nr);
	fill(pre, pre + n, -1); fill(hr, hr + n, 0);
	fill(fl, fl + n, -1); fill(fr, fr + n, -1);
	for (int i = 0; i < n; ++i)
		hl[i] = *max_element(a[i], a[i] + n);
	for (int i = 0; i < n; ++i)
		bfs(i); }
LL calc() {
	LL ans = 0;
	for (int i = 0; i < nl; ++i)
		if (~fl[i]) ans += a[i][fl[i]];
	return ans; }
void output() {
	for (int i = 0; i < nl; ++i)
	printf("%d ", (~fl[i] && a[i][fl[i]] ? fl[i] + 1 : 0));
} } km;
