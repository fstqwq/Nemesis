struct Node *null;
struct Node {
	Node *ch[2], *fa, *pos;
	int val, mn, l, len; bool rev;
	// min_val in chain
	inline bool type()
	{
		return fa -> ch[1] == this;
	}
	inline bool check()
	{
		return fa -> ch[type()] == this;
	}
	inline void pushup()
	{
		pos = this; mn = val;
		ch[0] -> mn < mn ? mn = ch[0] -> mn, pos = ch[0] -> pos : 0;
		ch[1] -> mn < mn ? mn = ch[1] -> mn, pos = ch[1] -> pos : 0;
		len = ch[0] -> len + ch[1] -> len + l;
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
	inline void pushdownall()
	{
		if (check()) fa -> pushdownall();
		pushdown();
	}
	inline void rotate()
	{
		bool d = type(); Node *f = fa, *gf = f -> fa;
		(fa = gf, f -> check()) ? fa -> ch[f -> type()] = this : 0;
		(f -> ch[d] = ch[!d]) != null ? ch[!d] -> fa = f : 0;
		(ch[!d] = f) -> fa = this;
		f -> pushup();
	}
	inline void splay(bool need = 1)
	{
		if (need) pushdownall();
		for (; check(); rotate())
			if (fa -> check())
				(type() == fa -> type() ? fa : this) -> rotate();
		pushup();
	}
	inline Node *access()
	{
		Node *i = this, *j = null;
		for (; i != null; i = (j = i) -> fa)
		{
			i -> splay();
			i -> ch[1] = j;
			i -> pushup();
		}
		return j;
	}
	inline void make_root()
	{
		access();
		splay();
		rev ^= 1;
	}
	inline void link(Node *that)
	{
		make_root();
		fa = that;
		splay(0);
	}
	inline void cut(Node *that)
	{
		make_root();
		that -> access();
		that -> splay(0);
		that -> ch[0] = fa = null;
		that -> pushup();
	}
} mem[maxn];
inline Node *query(Node *a, Node *b)
{
	a -> make_root(); b -> access(); b -> splay(0);
	return b -> pos;
}
inline int dist(Node *a, Node *b)
{
	a -> make_root(); b -> access(); b -> splay(0);
	return b -> len;
}
