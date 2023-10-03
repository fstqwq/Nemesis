int len[N], par[N], go[N][26], last, cnt;
char s[N];
void extend(int n) { int p = last, c = s[n] - 'a';
	while (s[n - len[p] - 1] != s[n]) p = par[p];
	if (!go[p][c]) { int q = ++cnt, now = p;
		len[q] = len[p] + 2;
		do p = par[p];
		while (s[n - len[p] - 1] != s[n]);
		par[q] = go[p][c]; last = go[now][c] = q;
	} else last = go[p][c]; }
int main() { par[0] = cnt = 1; len[1] = -1; }