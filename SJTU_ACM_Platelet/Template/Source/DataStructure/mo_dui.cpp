int size;
struct Query {
	int l, r, id;
	inline bool operator < (const Queuy &that) const {return l / size != that.l / size ? l < that.l : ((l / size) & 1 ? r < that.r : r > that.r);}
} q[maxn];
int main()
{
	size = (int) sqrt(n * 1.0);
	std::sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i)
	{
		for (; r < q[i].r; ) add(++r);
		for (; r > q[i].r; ) del(r--);
		for (; l < q[i].l; ) del(l++);
		for (; l > q[i].l; ) add(--l);
		/*
			write your code here.
		*/
	}
	return 0;
}

