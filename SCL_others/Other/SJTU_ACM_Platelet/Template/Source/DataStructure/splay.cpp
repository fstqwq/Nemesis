struct Node *null;
struct Node {
	Node *ch[2], *fa;
	int val; bool rev;
	inline bool type()
	{
		return fa -> ch[1] == this;
	}
	inline void pushup()
	{
	}
	inline void pushdown()
	{
		if (rev)
		{
			ch[0] -> rev ^= 1;
			ch[1] -> rev ^= 1;
			std::swap(ch[0], ch[1]);
			rev ^= 1;
		}
	}
	inline void rotate()
	{
		bool d = type(); Node *f = fa, *gf = f -> fa;
		(fa = gf, f -> fa != null) ? fa -> ch[f -> type()] = this : 0;
		(f -> ch[d] = ch[!d]) != null ? ch[!d] -> fa = f : 0;
		(ch[!d] = f) -> fa = this;
		f -> pushup();
	}
	inline void splay()
	{
		for (; fa != null; rotate())
			if (fa -> fa != null)
				(type() == fa -> type() ? fa : this) -> rotate();
		pushup();
	}
} mem[maxn];
