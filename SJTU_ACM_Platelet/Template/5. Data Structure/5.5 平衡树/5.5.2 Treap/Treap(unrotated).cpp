//
//  Title : Treap (unrotated)
//  Date : 13.04.2016
//  Test : BZOJ-3224
//  Complexity : O(nlogn)(期望)
//  
/*
	对于序列上的一些操作的问题——
	解决办法：平衡树Treap
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
const int Ta = 1 << 16 | 3, Tb = 33333331;
int Tc;
inline int randint() {return Tc = Ta * Tc + Tb;}
struct Treap
{
	int data, key, size;
	Treap *ls, *rs;
	Treap(int _val):data(_val), key(randint()), ls(NULL), rs(NULL), size(1){}
	inline void update()
	{
		size = (ls ? ls -> size : 0) + (rs ? rs -> size : 0) + 1;
	}
}*root;
inline int Size(Treap *x)
{
	return x ? x -> size : 0;
}
//为了防止访问到空节点，定义一个函数来访问size
struct Pair
{
	Treap *fir, *sec;
};
Treap *Merge(Treap *a, Treap *b)
{
	if (!a) return b;
	if (!b) return a;
	if (a -> key < b -> key)
	{
		a -> rs = Merge(a -> rs, b);
		a -> update();
		return a;
	}
	else
	{
		b -> ls = Merge(a, b -> ls);
		b -> update();
		return b;
	}
}
//按照a，b的顺序来合并两棵Treap
Pair Split(Treap *x, int k)
{
	if (!x) return (Pair){NULL, NULL};
	Pair y; y.fir = NULL; y.sec = NULL;
	if (Size(x -> ls) >= k)
	{
		y = Split(x -> ls, k);
		x -> ls = y.sec;
		x -> update();
		y.sec = x;
	}
	else
	{
		y = Split(x -> rs, k - Size(x -> ls) - 1);
		x -> rs = y.fir;
		x -> update();
		y.fir = x;
	}
	return y;
}
//将前k个的点分离出来
inline int Find(R int k)
{
	Pair x = Split(root, k - 1);
	Pair y = Split(x.sec, 1);
	Treap *ans = y.fir;
	root = Merge(Merge(x.fir, ans), y.sec);
	return ans -> data;
}
//找到第k小的data值
int Get(Treap *x, R int val)
{
	if (!x) return 0;
	return val < x -> data ? Get(x -> ls, val) : Get(x -> rs, val) + Size(x -> ls) + 1;
}
//找到val的排名
inline void Insert(R int val)
{
	R int k = Get(root, val);
	Pair x = Split(root, k);
	Treap *pre = new Treap(val);
	root = Merge(Merge(x.fir, pre), x.sec);
}
//插入
inline void Delete(R int val)
{
	R int k = Get(root, val);
	Pair x = Split(root, k - 1);
	Pair y = Split(x.sec, 1);
	root = Merge(x.fir, y.sec);
}
//单点删除
inline int upper(R int val)
{
	R int ans = 1e9;
	Treap *tmp = root;
	while (tmp)
	{
		if (tmp -> data > val)
		{
			cmin(ans, tmp -> data);
			tmp = tmp -> ls;
		}
		else
			tmp = tmp -> rs;
	}
	return ans;
}
inline int lower(R int val)
{
	R int ans = -1e9;
	Treap *tmp = root;
	while (tmp)
	{
		if (tmp -> data < val)
		{
			cmax(ans, tmp -> data);
			tmp = tmp -> rs;
		}
		else tmp = tmp -> ls;
	}
	return ans;
}
void print(Treap *x)
{
	if (!x) return;
	print(x -> ls);
	printf("%d ",x -> data );
	print(x -> rs);
}
int main()
{
	root = NULL;
	for (R int Q = FastIn(); Q; --Q)
	{
		R int opt = FastIn(), x = FastIn();
		if (opt == 1) Insert(x);
		else if (opt == 2) Delete(x);
		else if (opt == 3)
		{
			R int ans = Get(root, x);
			while (ans > 1 && Find(ans - 1) == x) ans--;
			printf("%d\n", ans );
		}
		else if (opt == 4) printf("%d\n", Find(x) );
		else if (opt == 5) printf("%d\n",lower(x) );
		else printf("%d\n",upper(x) );
	}
	return 0;
}
/*
input:
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598

output:
106465
84185
492737

input2:
5
1 1
1 1
1 1
1 2
3 1
output2:
1
*/
