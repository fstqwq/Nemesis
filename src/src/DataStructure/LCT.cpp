// 记得初始化 mn; 维护虚子树：access link cut pushup
int fa[MX], ch[MX][2], w[MX], mn[MX], mark[MX];
int get(int x) {return x == ch[fa[x]][1];}
int nrt(int x) {return get(x) || x == ch[fa[x]][0];}
void pushup(int x) {
	mn[x] = w[x];
	if (lch(x)) mn[x] = min(mn[x], mn[lch(x)]);
	if (rch(x)) mn[x] = min(mn[x], mn[rch(x)]); }
void rev(int x) {mark[x] ^= 1, swap(lch(x), rch(x));}
void pushdown(int x) {
	if (mark[x]) {
		if (lch(x)) rev(lch(x));
		if (rch(x)) rev(rch(x));
		mark[x] = false; } }
void rot(int x) {
	int f = fa[x], gf = fa[f];
	int which = get(x), W = ch[x][!which];
	if (nrt(f)) ch[gf][ch[gf][1] == f] = x;
	ch[x][!which] = f, ch[f][which] = W;
	if (W) fa[W] = f;
	fa[f] = x, fa[x] = gf;
	pushup(f); }
void splay(int x) {
	static int stk[MX];
	int f = x, dep = 0; stk[++dep] = f;
	while (nrt(f)) stk[++dep] = f = fa[f];
	while (dep) pushdown(stk[dep--]);
	while (nrt(x)) {
		if (nrt(f = fa[x])) rot(get(x) == get(f) ? f : x);
		rot(x);
	} pushup(x); }
void access(int x) {
	for(int y = 0 ; x ; x = fa[y = x])
		splay(x), rch(x) = y, pushup(x); }
void makeroot(int x) {access(x), splay(x), rev(x);}
void split(int x, int y) {makeroot(x), access(y), splay(y);}
int findroot(int x) {
	access(x), splay(x);
	while (lch(x)) pushdown(x), x = lch(x);
	return splay(x), x;	}
void link(int x, int y) {
	makeroot(x);
	if (findroot(y) != x) fa[x] = y; }
void cut(int x, int y) {
	makeroot(x);
	if (findroot(y) != x || fa[y] != x || lch(y)) return;
	rch(x) = fa[y] = 0, pushup(x); }