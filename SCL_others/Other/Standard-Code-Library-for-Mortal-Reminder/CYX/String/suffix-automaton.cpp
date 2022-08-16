static const int MAXL = MAXN * 2;  // MAXN is original length
static const int alphabet = 26;  // sometimes need changing
int l, last, cnt, trans[MAXL][alphabet], par[MAXL], sum[MAXL], seq[MAXL], mxl[MAXL], size[MAXL];  // mxl is maxlength, size is the size of right
char str[MAXL];
inline void init() {
	l = strlen(str + 1); cnt = last = 1;
	for (int i = 0; i <= l * 2; ++i) memset(trans[i], 0, sizeof(trans[i]));
	memset(par, 0, sizeof(*par) * (l * 2 + 1));
	memset(mxl, 0, sizeof(*mxl) * (l * 2 + 1));
	memset(size, 0, sizeof(*size) * (l * 2 + 1));
}
inline void extend(int pos, int c) {
	int p = last, np = last = ++cnt;
	mxl[np] = mxl[p] + 1; size[np] = 1;
	for (; p && !trans[p][c]; p = par[p]) trans[p][c] = np;
	if (!p) par[np] = 1;
	else {
		int q = trans[p][c];
		if (mxl[p] + 1 == mxl[q]) par[np] = q;
		else {
			int nq = ++cnt;
			mxl[nq] = mxl[p] + 1;
			memcpy(trans[nq], trans[q], sizeof(trans[nq]));
			par[nq] = par[q];
			par[np] = par[q] = nq;
			for (; trans[p][c] == q; p = par[p]) trans[p][c] = nq;
		}
	}
}
inline void buildsam() {
	for (int i = 1; i <= l; ++i) extend(i, str[i] - 'a');
	memset(sum, 0, sizeof(*sum) * (l * 2 + 1));
	for (int i = 1; i <= cnt; ++i) sum[mxl[i]]++;
	for (int i = 1; i <= l; ++i) sum[i] += sum[i - 1];
	for (int i = cnt; i; --i) seq[sum[mxl[i]]--] = i;
	for (int i = cnt; i; --i) size[par[seq[i]]] += size[seq[i]];
}
