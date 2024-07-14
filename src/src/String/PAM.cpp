int len[N], par[N], go[N][26], last, pam_cnt; char s[N];
void init(){ par[0] = pam_cnt = 1; len[1] = -1; }
int getfail(int n, int p){
	while (s[n - len[p] - 1] != s[n]) p = par[p];
	return p;}
void extend(int n) {
	int p = getfail(n, last), c = s[n] - 'a';
	if (!go[p][c]) { int q = ++pam_cnt, now = p;
		len[q] = len[p] + 2;
		p = getfail(n, par[p]);
		par[q] = go[p][c]; last = go[now][c] = q;
	} else last = go[p][c]; }