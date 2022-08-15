//
//  Title : LCT(change root)
//  Date : 03.05.2016
//  Test : BZOJ-2049
//  Complexity : O(mlogn)
//  
/*
	对于有link和cut操作维护树上的信息等问题——
	解决办法：link-cut tree
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

#ifdef CT
	#define debug(...) printf(__VA_ARGS__)
	#define setfile() 
#else
	#define debug(...)
	#define filename ""
	#define setfile() freopen(filename".in", "r", stdin); freopen(filename".out", "w", stdout);
#endif

#define R register
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? EOF : *S++)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
char B[1 << 15], *S = B, *T = B;
inline int FastIn()
{
	R char ch; R int cnt = 0; R bool minus = 0;
	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-') ;
	ch == '-' ? minus = 1 : cnt = ch - '0';
	while (ch = getc(), ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return minus ? -cnt : cnt;
}
#define maxn 200010
int n, m;
struct Node *null;
struct Node
{
	bool rev;
	Node *ch[2], *fa;
	inline bool type()
	{
		return fa -> ch[1] == this;
	}
	inline bool check()
	{
		return this == fa -> ch[type()];
	}
	inline void set_rev()
	{
		std::swap(ch[0], ch[1]);
		rev ^= 1;
	}
	inline void pushdown()
	{
		if (rev)
		{
			ch[0] -> set_rev();
			ch[1] -> set_rev();
			rev = 0;
		}
	}
	void pushdownall()
	{
		if (check())
			fa -> pushdownall();
		pushdown();
	}
	inline void rotate()
	{
		R Node *f = fa;
		R bool d = type();
		(fa = f -> fa), f -> check() ? fa -> ch[f -> type()] = this : 0;
		(f -> ch[d] = ch[!d]) != null ? ch[!d] -> fa = f : 0;
		(ch[!d] = f) -> fa = this;
	}
	inline void splay(R bool need = 1)
	{
		if (need) pushdownall();
		for (; check(); rotate())
			if (fa -> check())
				(type() != fa -> type() ? this : fa) -> rotate();
	}
	inline Node *access()
	{
		R Node *i = this, *j = null;
		for (; i != null; i = (j = i) -> fa)
		{
			i -> splay();
			i -> ch[1] = j;
		}
		return j;
	}
	inline void make_root()
	{
		access();
		splay(0);
		set_rev();
	}
	inline void link(R Node *that)
	{
		make_root();
		fa = that;
	}
	inline void cut(R Node *that)
	{
		make_root();
		that -> access();
		splay(0);
		that -> fa = ch[1] = null;
	}
	inline bool find(R Node *that)
	{
		access();
		splay();
		while (that -> fa != null)
			that = that -> fa;
		return that == this;
	}
}mem[maxn];
int main()
{
//	setfile();
	n = FastIn(), m = FastIn();
	null = mem;
	null -> fa = null -> ch[0] = null -> ch[1] = null;
	for (R int i = 1; i <= n; ++i) mem[i] = (Node) {0, {null, null}, null};
	for (R int i = 1; i <= m; ++i)
	{
		R char opt;
		while (opt = getc(), opt < 'A' || opt > 'Z');
		R int a = FastIn(), b = FastIn();
		if (opt == 'C')
		{
			(mem + a) -> link(mem + b);
		}
		else if (opt == 'D')
		{
			(mem + a) -> cut(mem + b);
		}
		else
		{
			puts((mem + a) -> find(mem + b) ? "Yes" : "No");
		}
	}
	return 0;
}
/*
200	5
Query	123	127
Connect	123	127
Query	123	127
Destroy	127	123
Query	123	127
3 5
Connect	1 2
Connect	3 1
Query	2 3
Destroy	1 3
Query	2 3
*/
