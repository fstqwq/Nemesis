int ch[MAXN][26], fail[MAXN], q[MAXN], cnt = 0;
int insert(const char *c) { int x = 0; while (*c) {
	if (!ch[x][*c - 'a']) ch[x][*c - 'a'] = ++cnt;
	x = ch[x][*c++ - 'a']; } return x; }
void getfail() { int x, head = 0, tail = 0;
	for (int c = 0; c < 26; c++) if (ch[0][c])
			q[tail++] = ch[0][c];
	while (head != tail) { x = q[head++];
		for (int c = 0; c < 26; c++) { if (ch[x][c]) {
				fail[ch[x][c]] = ch[fail[x]][c];
				q[tail++] = ch[x][c];
			} else ch[x][c] = ch[fail[x]][c]; } } }
