int newnode() {
	++tot;
	memset(ch[tot], 0, sizeof(ch[tot]));
	fail[tot] = dep[tot] = par[tot] = 0;
	return tot;
}
void insert(char *s,int x) {
	if(*s == '\0') return;
	else {
		int &y = ch[x][*s - 'a'];
		if(y == 0) y = newnode(), par[y] = x, dep[y] = dep[x] + 1;
		insert(s + 1, y);
	}
}
void build() {
	int line[maxn];
	int f = 0, r = 0;
	fail[root] = root;
	for(int i = 0; i < alpha; i++) {
		if(ch[root][i]) fail[ch[root][i]] = root, line[r++] = ch[root][i];
		else ch[root][i] = root;
	}
	while(f != r) {
		int x = line[f++];
		for(int i = 0; i < alpha; i++) {
			if(ch[x][i]) fail[ch[x][i]] = ch[fail[x]][i], line[r++] = ch[x][i];
			else ch[x][i] = ch[fail[x]][i];
		}
	}
}
