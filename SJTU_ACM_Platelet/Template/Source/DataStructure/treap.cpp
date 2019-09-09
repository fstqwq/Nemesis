struct Treap {
	Treap *ls, *rs;
	int size;
	bool rev;
	inline void update()
	{
		size = ls -> size + rs -> size + 1;
	}
	inline void set_rev()
	{
		rev ^= 1;
		std::swap(ls, rs);
	}
	inline void pushdown()
	{
		if (rev)
		{
			ls -> set_rev();
			rs -> set_rev();
			rev = 0;
		}
	}
} mem[maxn], *root, *null = mem;
struct Pair {
	Treap *fir, *sec;
};
Treap *build(R int l, R int r)
{
	if (l > r) return null;
	R int mid = l + r >> 1;
	R Treap *now = mem + mid;
	now -> rev = 0; 
	now -> ls = build(l, mid - 1);
	now -> rs = build(mid + 1, r);
	now -> update();
 
	return now;
}
inline Treap *Find_kth(R Treap *now, R int k)
{
	if (!k) return mem;
	if (now -> ls -> size >= k) return Find_kth(now -> ls, k);
	else if (now -> ls -> size + 1 == k) return now;
	else return Find_kth(now -> rs, k - now -> ls -> size - 1);
}
Treap *merge(R Treap *a, R Treap *b)
{
	if (a == null) return b;
	if (b == null) return a;
	if (rand() % (a -> size + b -> size) < a -> size)
	{
		a -> pushdown();
		a -> rs = merge(a -> rs, b);
		a -> update();
		return a;
	}
	else
	{
		b -> pushdown();
		b -> ls = merge(a, b -> ls);
		b -> update();
		return b;
	}
}
Pair split(R Treap *now, R int k)
{
	if (now == null) return (Pair) {null, null};
	R Pair t = (Pair) {null, null};
	now -> pushdown();
	if (k <= now -> ls -> size)
	{
		t = split(now -> ls, k);
		now -> ls = t.sec;
		now -> update();
		t.sec = now;
	}
	else
	{
		t = split(now -> rs, k - now -> ls -> size - 1);
		now -> rs = t.fir;
		now -> update();
		t.fir = now;
	}
	return t;
}
inline void set_rev(int l, int r)
{
	R Pair x = split(root, l - 1);
	R Pair y = split(x.sec, r - l + 1);
	y.fir -> set_rev();
	root = merge(x.fir, merge(y.fir, y.sec));
}
