#define isroot(x) ((x) -> p == null || \
((x) -> p -> ch[0] != (x) && (x) -> p -> ch[1] != (x)))
#define dir(x) ((x) == (x) -> p -> ch[1])
struct node{ int key, mx, pos; bool rev; node *ch[2], *p;
	node(int key = 0): key(key), mx(key), pos(-1), rev(false) {}
	void pushdown() { if (!rev) return;
		ch[0] -> rev ^= true; ch[1] -> rev ^= true;
		swap(ch[0], ch[1]); if (pos != -1) pos ^= 1;
		rev = false; }
	void update() { mx = key; pos = -1;
		if (ch[0] -> mx > mx) { mx = ch[0] -> mx; pos = 0; }
		if (ch[1] -> mx > mx) { mx = ch[1] -> mx; pos = 1; } }
} null[maxn * 2];
void init(node *x, int k) {
	x -> ch[0] = x -> ch[1] = x -> p = null;
	x -> key = x -> mx = k; }
void rot(node *x, int d) { node *y = x -> ch[d ^ 1];
	if ((x -> ch[d ^ 1] = y -> ch[d]) != null)
		y -> ch[d] -> p = x;
	y -> p = x -> p;
	if (!isroot(x)) x -> p -> ch[dir(x)] = y;
	(y -> ch[d] = x) -> p = y;
	x -> update(); y -> update(); }
void splay(node *x) { x -> pushdown();
	while (!isroot(x)) {
		if (!isroot(x -> p)) x -> p -> p -> pushdown();
		x -> p -> pushdown(); x -> pushdown();
		if (isroot(x -> p)) {
			rot(x -> p, dir(x) ^ 1); break; }
		if (dir(x) == dir(x -> p))
			rot(x -> p -> p, dir(x -> p) ^ 1);
		else rot(x -> p, dir(x) ^ 1);
		rot(x -> p, dir(x) ^ 1); } }
node *access(node *x) { node *y = null;
	while (x != null) { splay(x); x -> ch[1] = y;
		(y = x) -> update(); x = x -> p; } return y; }
void makeroot(node *x) {
	access(x); splay(x); x -> rev ^= true; }
void link(node *x, node *y) { makeroot(x); x -> p = y; }
void cut(node *x, node *y) { makeroot(x); access(y); splay(y);
	y -> ch[0] -> p = null; y -> ch[0] = null;
	y -> update(); }
node *getroot(node *x) { x = access(x);
	while (x -> pushdown(), x -> ch[0] != null)
		x = x -> ch[0];
	splay(x); return x; }
node *getmax(node *x, node *y) { makeroot(x); x = access(y);
	while (x -> pushdown(), x -> pos != -1)
		x = x -> ch[x -> pos];
	splay(x); return x; }
int main() { for (int i = 1; i <= m; i++) {
	init(null + n + i, w[i]);
	if (getroot(null + u[i]) != getroot(null + v[i])) {
		ans[q + 1] -= k; ans[q + 1] += w[i];
		link(null + u[i], null + n + i);
		link(null + v[i], null + n + i);
		vis[i] = true; } else {
		int ii = getmax(null + u[i], null + v[i]) - null - n;
		if (w[i] >= w[ii]) continue;
		cut(null + u[ii], null + n + ii);
		cut(null + v[ii], null + n + ii);
		link(null + u[i], null + n + i);
		link(null + v[i], null + n + i);
		ans[q + 1] -= w[ii]; ans[q + 1] += w[i]; } } }