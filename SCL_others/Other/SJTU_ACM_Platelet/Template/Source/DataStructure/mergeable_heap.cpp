struct Node {
	Node *ch[2];
	ll val; int size;
	inline void update()
	{
		size = ch[0] -> size + ch[1] -> size + 1;
	}
} mem[maxn], *rt[maxn];
Node *merge(Node *a, Node *b)
{
	if (a == mem) return b;
	if (b == mem) return a;
	if (a -> val < b -> val) std::swap(a, b);
	// a -> pushdown();
	std::swap(a -> ch[0], a -> ch[1]);
	a -> ch[1] = merge(a -> ch[1], b);
	a -> update();
	return a;
}
