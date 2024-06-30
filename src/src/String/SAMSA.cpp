bool vis[MAXN * 2]; char s[MAXN];
int id[MAXN * 2], ch[MAXN * 2][26], height[MAXN], stamp = 0;
void dfs(int x) {
	if (id[x]) { height[stamp++] = val[last];
		sa[stamp] = id[x]; last = x; }
    for (int c = 0; c < 26; c++)
		if (ch[x][c]) dfs(ch[x][c]);
	last = par[x]; }
int main() { last = ++cnt; scanf("%s", s + 1);
    int n = strlen(s + 1); for (int i = n; i; i--) {
		expand(s[i] - 'a'); id[last] = i; }
	vis[1] = true; for (int i = 1; i <= cnt; i++) if (id[i])
			for (int x = i,pos = n; x && !vis[x]; x = par[x]){
				vis[x] = true; pos -= val[x] - val[par[x]];
				ch[par[x]][s[pos + 1] - 'a'] = x; }
	dfs(1); for (int i = 1; i <= n; i++)
		printf("%d%c", sa[i], i < n ? ' ' : '\n');
	for (int i = 1; i < n; i++) printf("%d%c", height[i],
        i < n ? ' ' : '\n'); return 0; }
