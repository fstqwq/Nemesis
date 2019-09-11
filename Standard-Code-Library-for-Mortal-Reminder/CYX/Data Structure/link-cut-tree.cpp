inline void reverse(int x) {
	tr[x].rev ^= 1; swap(tr[x].c[0], tr[x].c[1]);
}
inline void rotate(int x, int k) {
	int y = tr[x].fa, z = tr[y].fa;
    tr[x].fa = z; tr[z].c[tr[z].c[1] == y] = x;
    tr[tr[x].c[k ^ 1]].fa = y; tr[y].c[k] = tr[x].c[k ^ 1];
    tr[x].c[k ^ 1] = y; tr[y].fa = x;
}
inline void splay(int x, int w) {
	int z = x; pushdown(x);
	while (tr[x].fa != w) {
		int y = tr[x].fa; z = tr[y].fa;
		if (z == w) {
			pushdown(z = y); pushdown(x);
			rotate(x, tr[y].c[1] == x);
			update(y); update(x);
		} else {
			pushdown(z); pushdown(y); pushdown(x);
			int t1 = tr[y].c[1] == x, t2 = tr[z].c[1] == y;
			if (t1 == t2) rotate(y, t2), rotate(x, t1);
			else rotate(x, t1), rotate(x, t2);
			update(z); update(y); update(x);
		}
	}
	update(x);
	if (x != z) par[x] = par[z], par[z] = 0;
}
inline void access(int x) {
	for (int y = 0; x; y = x, x = par[x]) {
		splay(x, 0);
		if (tr[x].c[1]) par[tr[x].c[1]] = x, tr[tr[x].c[1]].fa = 0;
		tr[x].c[1] = y; par[y] = 0; tr[y].fa = x; update(x);
	}
}
inline void makeroot(int x) {
	access(x); splay(x, 0); reverse(x);
}
inline void link(int x, int y) {
	makeroot(x); par[x] = y;
}
inline void cut(int x, int y) {
	access(x); splay(y, 0);
	if (par[y] != x) swap(x, y), access(x), splay(y, 0);
	par[y] = 0;
}
inline void split(int x, int y) {  // x will be the root of the tree
	makeroot(y); access(x); splay(x, 0);
}
