struct Node {
	int d[2], ma[2], mi[2], siz;
	Node *l, *r;
	void upd() {
		ma[0] = mi[0] = d[0]; ma[1] = mi[1] = d[1]; siz = 1;
		if (l) {
			Max(ma[0], l->ma[0]); Max(ma[1], l->ma[1]);
			Min(mi[0], l->mi[0]); Min(mi[1], l->mi[1]);
			siz += l->siz; }
		if (r) {
			Max(ma[0], r->ma[0]); Max(ma[1], r->ma[1]);
			Min(mi[0], r->mi[0]); Min(mi[1], r->mi[1]);
			siz += r->siz; } }
} mem[N], *ptr = mem, *rt;
int n, m, ans;
Node *tmp[N]; int top, D, Q[2];
Node *newNode(int x = Q[0], int y = Q[1]) {
	ptr->d[0] = ptr->ma[0] = ptr->mi[0] = x;
	ptr->d[1] = ptr->ma[1] = ptr->mi[1] = y;
	ptr->l = ptr->r = NULL; ptr->siz = 1;
	return ptr++; }
bool cmp(const Node* a, const Node* b) {
	return a->d[D] < b->d[D] || (a->d[D] == b->d[D] && a->d[!D] < b->d[!D]);}
Node *build(int l, int r, int d = 0) {
	int mid = (l + r) / 2; // chk if negative
	D = d; nth_element(tmp + l, tmp + mid, tmp + r + 1, cmp);
	Node *x = tmp[mid];
	if (l < mid) x->l = build(l, mid - 1, !d); else x->l = NULL;
	if (r > mid) x->r = build(mid + 1, r, !d); else x->r = NULL;
	x->upd(); return x; }
int dis(const Node *x) {
	return (abs(x->d[0] - Q[0]) + abs(x->d[1] - Q[1]));}
int g(Node *x) {
	return x ? (max(max(Q[0] - x->ma[0], x->mi[0] - Q[0]), 0) + max(max(Q[1] - x->ma[1], x->mi[1] - Q[1]), 0)) : INF;}
void dfs(Node *x) {
	if (x->l) dfs(x->l);
	tmp[++top] = x;
	if (x->r) dfs(x->r); }
Node *insert(Node *x, int d = 0) {
	if (!x) return newNode();
	if (x->d[d] > Q[d]) x->l = insert(x->l, !d);
	else x->r = insert(x->r, !d);
	x->upd();
	return x; }
Node *chk(Node *x, int d = 0) {
	if (!x) return 0;
	if (max(x->l ? x->l->siz : 0, x->r ? x->r->siz : 0) * 5 > x->siz * 4) {
		return top = 0, dfs(x), build(1, top, d); }
	if (x->d[d] > Q[d]) x->l = chk(x->l, !d);
	else if (x->d[0] == Q[0] && x->d[1] == Q[1]) return x;
	else x->r = chk(x->r, !d);
	return x; } 
void query(Node *x) {
	if (!x) return;
	ans = min(ans, dis(x));
	int dl = g(x->l), dr = g(x->r);
	if (dl < dr) {
		if (dl < ans) query(x->l);
		if (dr < ans) query(x->r); }
	else {
		if (dr < ans) query(x->r);
		if (dl < ans) query(x->l); } }
int main() {
	read(n); read(m);
	for (int i = 1, x, y; i <= n; i++) read(x), read(y), tmp[i] = newNode(x, y);
	rt = build(1, n);
	for (int i = 1, op; i <= m; i++) {
		read(op); read(Q[0]); read(Q[1]);
		if (op == 1) rt = insert(rt), rt = chk(rt);
		else ans = INF, query(rt), printf("%d\n", ans); } } 
