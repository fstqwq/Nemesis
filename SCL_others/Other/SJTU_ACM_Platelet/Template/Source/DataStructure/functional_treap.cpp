char str[maxn];
struct Treap
{
	Treap *ls, *rs;
	char data; int size;
	inline void update()
	{
		size = ls -> size + rs -> size + 1;
	}
} *root[maxn], mem[maxcnt], *tot = mem, *last = mem, *null = mem;
inline Treap* new_node(char ch)
{
	*++tot = (Treap) {null, null, ch, 1};
	return tot;
}
struct Pair
{
	Treap *fir, *sec;
};
inline Treap *copy(Treap *x)
{
	if (x == null) return null;
	if(x > last) return x;
	*++tot = *x;
	return tot;
}
Pair Split(Treap *x, int k)
{
	if (x == null) return (Pair) {null, null};
	Pair y;
	Treap *nw = copy(x);
	if (nw -> ls -> size >= k)
	{
		y = Split(nw -> ls, k);
		nw -> ls = y.sec;
		nw -> update();
		y.sec = nw;
	}
	else
	{
		y = Split(nw -> rs, k - nw -> ls -> size - 1);
		nw -> rs = y.fir;
		nw -> update();
		y.fir = nw;
	}
	return y;
}
Treap *Merge(Treap *a, Treap *b)
{
	if (a == null) return b;
	if (b == null) return a;
	Treap *nw;
	if (rand() % (a -> size + b -> size) < a -> size)
	{
		nw = copy(a);
		nw -> rs = Merge(nw -> rs, b);
	}
	else
	{
		nw = copy(b);
		nw -> ls = Merge(a, nw -> ls);
	}
	nw -> update();
	return nw;
}
Treap *Build(int l, int r)
{
	if (l > r) return null;
	int mid = l + r >> 1;
	Treap *nw = new_node(str[mid]);
	nw -> ls = Build(l, mid - 1);
	nw -> rs = Build(mid + 1, r);
	nw -> update();
	return nw;
}
int now;
inline void Insert(int k, char ch)
{
	Pair x = Split(root[now], k);
	Treap *nw = new_node(ch);
	root[++now] = Merge(Merge(x.fir, nw), x.sec);
}
inline void Del(int l, int r)
{
	Pair x = Split(root[now], l - 1);
	Pair y = Split(x.sec, r - l + 1);
	root[++now] = Merge(x.fir, y.sec);
}
inline void Copy(int l, int r, int ll)
{
	Pair x = Split(root[now], l - 1);
	Pair y = Split(x.sec, r - l + 1);
	Pair z = Split(root[now], ll);
	Treap *ans = y.fir;
	root[++now] = Merge(Merge(z.fir, ans), z.sec);
}
void Print(Treap *x, int l, int r)
{
	if (!x) return ;
	if (l > r) return;
	int mid = x -> ls -> size + 1;
	if (r < mid)
	{
		Print(x -> ls, l, r);
		return ;
	}
	if (l > mid)
	{
		Print(x -> rs, l - mid, r - mid);
		return ;
	}
	Print(x -> ls, l, mid - 1);
	printf("%c", x -> data );
	Print(x -> rs, 1, r - mid);
}
void Printtree(Treap *x)
{
	if (!x) return;
	Printtree(x -> ls);
	printf("%c", x -> data );
	Printtree(x -> rs);
}
int main()
{
	srand(time(0) + clock());
	null -> ls = null -> rs = null; null -> size = 0; null -> data = 0;
	int n = F();
	gets(str + 1);
	int len = strlen(str + 1);
	root[0] = Build(1, len);
	while (1)
	{
		last = tot;
		char opt = getc();
		while (opt < 'A' || opt > 'Z')
		{
			if (opt == EOF) return 0;
			opt = getc();
		}
		if (opt == 'I')
		{
			int x = F();
			char ch = getc();
			Insert(x, ch);
		}
		else if (opt == 'D')
		{
			int l = F(), r = F();
			Del(l, r);
		}
		else if (opt == 'C')
		{
			int x = F(), y = F(), z = F();
			Copy(x, y, z);
		}
		else if (opt == 'P')
		{
			int x = F(), y = F(), z = F();
			Print(root[now - x], y, z);
			puts("");
		}
	}
	return 0;
}
