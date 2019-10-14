int fa[maxn], ch[maxn][2], a[maxn], size[maxn], cnt;
int sum[maxn], lmx[maxn], rmx[maxn], mx[maxn], v[maxn], id[maxn], root;
bool rev[maxn], tag[maxn];
inline void update(int x)
{
	int ls = ch[x][0], rs = ch[x][1];
	size[x] = size[ls] + size[rs] + 1;
	sum[x] = sum[ls] + sum[rs] + v[x];
	mx[x] = gmax(mx[ls], mx[rs]);
	cmax(mx[x], lmx[rs] + rmx[ls] + v[x]);
	lmx[x] = gmax(lmx[ls], sum[ls] + v[x] + lmx[rs]);
	rmx[x] = gmax(rmx[rs], sum[rs] + v[x] + rmx[ls]);
}
inline void pushdown(int x)
{
	int ls = ch[x][0], rs = ch[x][1];
	if (tag[x])
	{
		rev[x] = tag[x] = 0;
		if (ls) tag[ls] = 1, v[ls] = v[x], sum[ls] = size[ls] * v[x];
		if (rs) tag[rs] = 1, v[rs] = v[x], sum[rs] = size[rs] * v[x];
		if (v[x]>= 0)
		{
			if (ls) lmx[ls] = rmx[ls] = mx[ls] = sum[ls];
			if (rs) lmx[rs] = rmx[rs] = mx[rs] = sum[rs];
		}
		else
		{
			if (ls) lmx[ls] = rmx[ls] = 0, mx[ls] = v[x];
			if (rs) lmx[rs] = rmx[rs] = 0, mx[rs] = v[x];
		}	
	}
	if (rev[x])
	{
		rev[x] ^= 1; rev[ls] ^= 1; rev[rs] ^= 1;
		swap(lmx[ls], rmx[ls]);swap(lmx[rs], rmx[rs]);
		swap(ch[ls][0], ch[ls][1]); swap(ch[rs][0], ch[rs][1]);
	}
}
inline void rotate(int x)
{
	int f = fa[x], gf = fa[f], d = ch[f][1] == x;
	if (f == root) root = x;
	(ch[f][d] = ch[x][d ^ 1]) > 0 ? fa[ch[f][d]] = f : 0;
	(fa[x] = gf) > 0 ? ch[gf][ch[gf][1] == f] = x : 0;
	fa[ch[x][d ^ 1] = f] = x;
	update(f);
}
inline void splay(int x, int rt)
{
	while (fa[x] != rt)
	{
		int f = fa[x], gf = fa[f];
		if (gf != rt) rotate((ch[gf][1] == f) ^ (ch[f][1] == x) ? x : f);
		rotate(x);
	}
	update(x);
}
void build(int l, int r, int rt)
{
	if (l > r) return ;
	int mid = l + r >> 1, now = id[mid], last = id[rt];
	if (l == r)
	{
		sum[now] = a[l];
		size[now] = 1;
		tag[now] = rev[now] = 0;
		if (a[l] >= 0) lmx[now] = rmx[now] = mx[now] = a[l];
		else lmx[now] = rmx[now] = 0, mx[now] = a[l];
	}
	else
	{
		build(l, mid - 1, mid);
		build(mid + 1, r, mid);
	}
	v[now] = a[mid];
	fa[now] = last;
	update(now);
	ch[last][mid >= rt] = now;
}
int find(int x, int rank)
{
	if (tag[x] || rev[x]) pushdown(x);
	int ls = ch[x][0], rs = ch[x][1], lsize = size[ls];
	if (lsize + 1 == rank) return x;
	if (lsize >= rank)
		return find(ls, rank);
	else
		return find(rs, rank - lsize - 1);
}
inline int prepare(int l, int tot)
{
	int x = find(root, l - 1), y = find(root, l + tot);
	splay(x, 0);
	splay(y, x);
	return ch[y][0];
}
std::queue <int> q;
inline void Insert(int left, int tot)
{
	for (int i = 1; i <= tot; ++i ) a[i] = FastIn();
	for (int i = 1; i <= tot; ++i )
		if (!q.empty()) id[i] = q.front(), q.pop();
		else id[i] = ++cnt;
	build(1, tot, 0);
	int z = id[(1 + tot) >> 1];
	int x = find(root, left), y = find(root, left + 1);
	splay(x, 0);
	splay(y, x);
	fa[z] = y;
	ch[y][0] = z;
	update(y);
	update(x);
}
void rec(int x)
{
	if (!x) return ;
	int ls = ch[x][0], rs = ch[x][1];
	rec(ls); rec(rs); q.push(x);
	fa[x] = ch[x][0] = ch[x][1] = 0;
	tag[x] = rev[x] = 0;
}
inline void Delete(int l, int tot)
{
	int x = prepare(l, tot), f = fa[x];
	rec(x); ch[f][0] = 0;
	update(f); update(fa[f]);
}
inline void Makesame(int l, int tot, int val)
{
	int x = prepare(l, tot), y = fa[x];
	v[x] = val; tag[x] = 1; sum[x] = size[x] * val;
	if (val >= 0) lmx[x] = rmx[x] = mx[x] = sum[x];
	else lmx[x] = rmx[x] = 0, mx[x] = val;
	update(y); update(fa[y]);
}
inline void Reverse(int l, int tot)
{
	int x = prepare(l, tot), y = fa[x];
	if (!tag[x])
	{
		rev[x] ^= 1;
		swap(ch[x][0], ch[x][1]);
		swap(lmx[x], rmx[x]);
		update(y); update(fa[y]);
	}
}
inline void Query(int l, int tot)
{
	int x = prepare(l, tot);
	printf("%d\n",sum[x] );
}
#define inf ((1 << 30))
int main()
{
	int n = FastIn(),  m = FastIn(), l, tot, val;
	char op, op2;
	mx[0] = a[1] = a[n + 2] = -inf;
	for (int i = 2; i <= n + 1; i++ )
	{
		a[i] = FastIn();
	}
	for (int i = 1; i <= n + 2; ++i) id[i] = i;
	n += 2; cnt = n; root = (n + 1) >> 1;
	build(1, n, 0);
	for (int i = 1; i <= m; i++ )
	{
		op = getc();
		while (op < 'A' || op > 'Z') op = getc();
		getc(); op2 = getc();getc();getc();getc();getc();
		if (op == 'M' && op2 == 'X')
		{
			printf("%d\n",mx[root] );
		}
		else
		{
			l = FastIn() + 1; tot = FastIn();
			if (op == 'I') Insert(l, tot);
			if (op == 'D') Delete(l, tot);
			if (op == 'M') val = FastIn(), Makesame(l, tot, val);
			if (op == 'R')
				Reverse(l, tot);
			if (op == 'G')
				Query(l, tot);
		}
	}
	return 0;
}
