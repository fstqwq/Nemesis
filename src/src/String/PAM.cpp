int val[maxn], par[maxn], go[maxn][26], last, cnt;
char s[maxn];
void extend(int n) { int p = last, c = s[n] - 'a';
	while (s[n - val[p] - 1] != s[n]) p = par[p];
	if (!go[p][c]) { int q = ++cnt, now = p;
		val[q] = val[p] + 2;
		do p = par[p];
		while (s[n - val[p] - 1] != s[n]);
		par[q] = go[p][c]; last = go[now][c] = q;
	} else last = go[p][c]; }
int main() { par[0] = cnt = 1; val[1] = -1; }