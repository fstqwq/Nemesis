// NOI 2014 购票
int dep[maxn], fa[maxn], son[maxn], dfn[maxn], timer, pos[maxn], size[maxn], n, top[maxn];
ll d[maxn], p[maxn], q[maxn], l[maxn], f[maxn];
int stcnt;
void dfs1(int x);
void dfs2(int x);
#define P pair<ll, ll>
#define mkp make_pair
#define x first
#define y second
#define inf ~0ULL >> 2
inline double slope(const P &a, const P &b)
{
	return (b.y - a.y) / (double) (b.x - a.x);
}
struct Seg
{
	vector<P> v;
	inline void add(const P &that) 
	{
		int top = v.size();
		P *v = this -> v.data() - 1;
		while (top > 1 && slope(v[top - 1], v[top]) > slope(v[top], that)) --top;
		this -> v.erase(this -> v.begin() + top, this -> v.end());
		this -> v.push_back(that);
	}
	inline ll query(ll k)
	{
		if (v.empty()) return inf;
		int l = 0, r = v.size() - 1;
		while (l < r)
		{
			int mid = l + r >> 1;
			if (slope(v[mid], v[mid + 1]) > k) r = mid;
			else l = mid + 1;
		}
		cmin(l, v.size() - 1);
		return v[l].y - v[l].x * k;
	}
} tr[1 << 19];
void Change(int o, int l, int r, int x, P val)
{
	tr[o].add(val);
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) Change(o << 1, l, mid, x, val);
	else Change(o << 1 | 1, mid + 1, r, x, val);
}
int ql, qr, now, tmp;
ll len;
inline ll Query(int o, int l, int r)
{
	if (ql <= l && r <= qr && d[tmp] - d[pos[r]] > len) return inf;
	if (ql <= l && r <= qr && d[tmp] - d[pos[l]] <= len)
		return tr[o].query(p[now]);
	ll ret = inf, temp;
	int mid = l + r >> 1;
	if (ql <= mid) temp = Query(o << 1, l, mid), cmin(ret, temp);
	if (mid < qr) temp = Query(o << 1 | 1, mid + 1, r), cmin(ret, temp);
	return ret;
}
inline ll calc()
{
	ll ret = inf;
	ll lx = l[now];
	tmp = now;
	while (lx >= 0 && tmp)
	{
		len = lx;
		ql = dfn[top[tmp]];
		qr = dfn[tmp];
		ll g = Query(1, 1, n);
		cmin(ret, g);
		lx -= d[tmp] - d[fa[top[tmp]]];
		tmp = fa[top[tmp]];
	}
	return ret;
}
int main()
{
	n = F(); int t = F();
	for (int i = 2; i <= n; ++i)
	{
		fa[i] = F(); ll dis = F(); p[i] = F(), q[i] = F(), l[i] = F();
		link(fa[i], i); d[i] = d[fa[i]] + dis;
	}
	dfs1(1);
	dfs2(1);
	Change(1, 1, n, 1, mkp(0, 0));
	for (now = 2; now <= n; ++now)
	{
		f[now] = calc() + q[now] + d[now] * p[now];
		Change(1, 1, n, dfn[now], mkp(d[now], f[now]));
		printf("%lld\n", f[now] );
	}
	return 0;
}
