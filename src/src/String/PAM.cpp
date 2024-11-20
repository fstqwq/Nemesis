int len[N], fail[N], go[N][26], last, pam_cnt; char s[N];
int dif[N], slink[N], g[N]; // 最小回文划分相关的 dp
void clgo(int x){memset(go[x], 0, sizeof(go[x]));}
void init(){ fail[0] = pam_cnt = 1; len[1] = -1;
	last = 0; clgo(0); clgo(1);}
int getfail(int n, int p){
	while (s[n - len[p] - 1] != s[n]) p = fail[p];
	return p;}
void extend(int n) {// 1 - base
	int p = getfail(n, last), c = s[n] - 'a';
	if (!go[p][c]) { int q = ++pam_cnt, now = p;
		clgo(q);
		len[q] = len[p] + 2;
		p = getfail(n, fail[p]);
		fail[q] = go[p][c]; last = go[now][c] = q;
		dif[q] = len[q] - len[fail[q]];
		slink[q] = dif[q] == dif[fail[q]] ? 
		slink[fail[q]] : fail[q];} else last = go[p][c];}
void solve(){
	for(int x = last; x > 1; x = slink[x]){
		g[x] = dp[i - len[slink[x]] - dif[x]];
		if(dif[x] == dif[fail[x]]) g[x] <- g[fail[x]];
		dp[i] <- g[x]; } }
//双端插入:前缀后缀分别写一个last和getfail,回文所以只需要维护回文后缀,当last=串长的时候两个last要等于整个串
//去均摊:quick[x][c]表示x的最长真回文后缀能匹配上c,初始化quick[0]全为1