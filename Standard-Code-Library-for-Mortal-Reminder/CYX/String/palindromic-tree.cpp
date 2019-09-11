int nT, nStr, last, c[MAXT][26], fail[MAXT], r[MAXN], l[MAXN], s[MAXN];
int allocate(int len) {
	l[nT] = len;
	r[nT] = 0;
	fail[nT] = 0;
	memset(c[nT], 0, sizeof(c[nT]));
	return nT++;
}
void init() {
	nT = nStr = 0;
	int newE = allocate(0);
	int newO = allocate(-1);
	last = newE;
	fail[newE] = newO;
	fail[newO] = newE;
	s[0] = -1;
}
void add(int x) {
	s[++nStr] = x;
	int now = last;
	while (s[nStr - l[now] - 1] != s[nStr]) now = fail[now];
	if (!c[now][x]) {
		int newnode = allocate(l[now] + 2), &newfail = fail[newnode];
		newfail = fail[now];
		while (s[nStr - l[newfail] - 1] != s[nStr]) newfail = fail[newfail];
		newfail = c[newfail][x];
		c[now][x] = newnode;
	}
	last = c[now][x];
	r[last]++;
}
void count() {
	for (int i = nT - 1; i >= 0; i--) {
		r[fail[i]] += r[i];
	}
}
