struct Node {
	Node *fa, *top, *c[2], *mi;
	int val; bool rev, isrt;
	Node () : mi(this), val(INF) {}
	void setc(Node *ch, int p) {c[p] = ch; ch->fa = this;}
	bool d() {return fa->c[1] == this;}
	void upd() {
		mi = this;
		if (c[0]->mi->val < mi->val) mi = c[0]->mi;
		if (c[1]->mi->val < mi->val) mi = c[1]->mi;
	}
	void revIt() {
		rev ^= 1; swap(c[0], c[1]);
	}
	void relax() {
		if (rev) {
			c[0]->revIt(); c[1]->revIt(); rev = 0;
		}
	}
	void setrt(Node *f);
} Tnull, *null = &Tnull, mem[MAXN + MAXM], *ptr = mem;

void Node::setrt(Node *f) {top = f; fa = null; isrt = 1;}

Node *newNode(int v = INF) {
	ptr->fa = ptr->top = ptr->c[0] = ptr->c[1] = null;
	ptr->mi = ptr; ptr->rev = 0; ptr->isrt = 1; ptr->val = v;
	return ptr++;
}

void rot(Node *x) {
	Node *fa = x->fa; bool d = x->d();
	fa->fa->setc(x, fa->d());
	fa->setc(x->c[!d], d);
	x->setc(fa, !d);
	fa->upd();
	if (fa->isrt) {
		fa->isrt = 0; x->isrt = 1; x->top = fa->top;
	}
}

void pushto(Node *x) {
	static Node *st[MAXN]; int top = 0;
	while (x != null) st[top++] = x, x = x->fa;
	while (top--) st[top]->relax();
}


void splay(Node *x) {
	pushto(x);
	while (x->fa != null) {
		if (x->fa->fa == null) rot(x);
		else x->d() == x->fa->d() ? (rot(x->fa), rot(x)) : (rot(x), rot(x));
	}
	x->upd();
}

void expose(Node *x) {
	static Node *y;
	for (y = null; x != null; y = x, x = x->top) {
		splay(x);
		x->c[1]->setrt(x); x->setc(y, 1);
	}
	//return y;
}

void mkrt(Node *x) {
	expose(x); splay(x); x->revIt();
}

void Link(Node *u, Node *v) {
	mkrt(u); u->top = v;
}

void Cut(Node *u, Node *v) {
	mkrt(u); expose(v); splay(u);
	u->setc(null, 1); u->upd();
	v->setrt(null);
}

Node *query(Node *u, Node *v) {
	mkrt(u); expose(v); splay(v);
	return v->mi;
}

Node *getrt(Node *x) {
	expose(x); splay(x);
	while (x->c[0] != null) x = x->c[0];
	splay(x);
	return x;
}

struct Edge {
	int u, v, w;
	bool operator < (const Edge &a) const {
		return w < a.w;
	}
} e[MAXM];

int n, m, ans = INF;

Node *a[MAXN];
bool vis[MAXM];
int E[MAXN + MAXM];

void newE(int i) {
	Node *mid = newNode(e[i].w);
	Link(mid, a[e[i].u]); Link(mid, a[e[i].v]);
	E[mid - mem] = i;
	vis[i] = 1;
}

void delE(Node *mid) {
	int i = E[mid - mem];
	vis[i] = 0;
	int u = e[i].u, v = e[i].v;
	Cut(mid, a[u]); Cut(mid, a[v]);
}

int main() {
	read(n); read(m);
	for (int i = 1; i <= n; i++) a[i] = newNode();
	for (int i = 1; i <= m; i++) read(e[i].u), read(e[i].v), read(e[i].w);
	sort(e + 1, e + m + 1);
	for (int i = 1, cnt = 0, j = 1; i <= m; i++) {
		if (getrt(a[e[i].u]) != getrt(a[e[i].v])) {
			cnt++;
			newE(i);
		}
		else if (e[i].u != e[i].v){
			Node *mi = query(a[e[i].u], a[e[i].v]);
			delE(mi);
			newE(i);
		}
		while (!vis[j]) j++;
		if (cnt == n - 1) ans = min(ans, e[i].w - e[j].w);
	}
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}

