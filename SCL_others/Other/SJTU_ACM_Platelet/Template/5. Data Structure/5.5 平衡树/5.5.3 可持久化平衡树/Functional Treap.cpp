//
//  Title: Functional Treap
//  Date: 16.04.2016
//  Test:YZOJ-1620
//  Complexity:O(nlogn)(期望)
//  
/*
    可持久化Treap:
	用来解决超级编辑器等问题。
	优势：好写好调好理解的平衡树
	缺点：写不好看的话常数大。（相较于SBT来说，甚至有可能会比splay慢），需手写rand
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
	#define setfile() freopen(filename".in", 'r', stdin); freopen(filename".out", 'w', stdout)
#endif

#define R register
//#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
#define getc() getchar()
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cabs(_x) ((_x)<0?(-_x):(_x))
char B[1<<15],*S=B,*T=B;
inline int FastIn()
{
	R char ch;R int cnt=0;R bool minus=0;
	while (ch=getc(),(ch < '0' || ch > '9') && ch != '-') ;
	ch == '-' ?minus=1:cnt=ch-'0';
	while (ch=getc(),ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return minus?-cnt:cnt;
}
#define maxn 100010
char str[maxn];
struct Treap
{
	char data;
	int size;
	Treap *ls, *rs;
	Treap(char _ch): data(_ch), size(1), ls(NULL), rs(NULL){}
	inline void update()
	{
		size = (ls ? ls -> size : 0) + (rs ? rs -> size : 0) + 1;
	}
}*root[maxn];
inline int Size(Treap *x)
{
	return x ? x -> size : 0;
}
struct Pair
{
	Treap *fir, *sec;
};
inline Treap *copy(Treap *x)
{
	if (!x) return NULL;
	Treap *nw = new Treap(x -> data);
	nw -> ls = x -> ls;
	nw -> rs = x -> rs;
	nw -> size = x -> size;
	return nw;
}
Pair Split(Treap *x, int k)
{
	if (!x) return (Pair){NULL, NULL};
	Pair y; y.fir = NULL; y.sec = NULL;
	Treap *nw = copy(x);
	if (Size(nw -> ls) >= k)
	{
		y = Split(nw -> ls, k);
		nw -> ls = y.sec;
		nw -> update();
		y.sec = nw;
	}
	else
	{
		y = Split(nw -> rs, k - Size(nw -> ls) - 1);
		nw -> rs = y.fir;
		nw -> update();
		y.fir = nw;
	}
	return y;
}
const int Ta = 1 << 16 | 3, Tb = 33333331;
unsigned int Tc;
inline unsigned int randint(){return Tc = Ta * Tc + Tb;}
Treap *Merge(Treap *a, Treap *b)
{
	Treap *nw;
	if (!a) return nw = copy(b);
	if (!b) return nw = copy(a);
	if (randint() % (Size(a) + Size(b)) < Size(a))
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
	if (l > r) return NULL;
	R int mid = l + r >> 1;
	Treap *nw = new Treap(str[mid]);
	nw -> ls = Build(l, mid - 1);
	nw -> rs = Build(mid + 1, r);
	nw -> update();
	return nw;
}
int now;
inline void Insert(R int k, R char ch)
{
	Pair x = Split(root[now], k);
	Treap *nw = new Treap(ch);
	root[++now] = Merge(Merge(x.fir, nw), x.sec);
}
inline void Del(R int l, R int r)
{
	Pair x = Split(root[now], l - 1);
	Pair y = Split(x.sec, r - l + 1);
	root[++now] = Merge(x.fir, y.sec);
}
inline void Copy(R int l, R int r, R int ll)
{
	Pair x = Split(root[now], l - 1);
	Pair y = Split(x.sec, r - l + 1);
	Pair z = Split(root[now], ll);
	Treap *ans = y.fir;
	root[++now] = Merge(Merge(z.fir, ans), z.sec);
}
inline void Print(Treap *x, R int l, R int r)
{
	if (!x) return ;
	if (l > r) return;
	R int mid = Size(x -> ls) + 1;
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
	printf("%c",x -> data );
	Print(x -> rs, 1, r - mid);
}
inline void Printtree(Treap *x)
{
	if (!x) return;
	Printtree(x -> ls);
	printf("%c",x -> data );
	Printtree(x -> rs);
}
int main()
{
//	setfile();
	R int n = FastIn();
	gets(str + 1);
	R int len = strlen(str + 1);
	root[0] = Build(1, len);
	while (1)
	{
		R char opt = getc();
		while (opt < 'A' || opt > 'Z')
		{
			if (opt == EOF) return 0;
			opt = getc();
		}
		if (opt == 'I')
		{
			R int x = FastIn();
			R char ch = getc();
			Insert(x, ch);
		}
		else if (opt == 'D')
		{
			R int l = FastIn(), r = FastIn();
			Del(l, r);
		}
		else if (opt == 'C')
		{
			R int x = FastIn(), y = FastIn(), z = FastIn();
			Copy(x, y, z);
		}
		else if (opt == 'P')
		{
			R int x = FastIn(), y = FastIn(), z = FastIn();
//			printf("%d %d %d\n",x, y, z );
			Print(root[now - x], y, z);
			puts("");
		}
//		Printtree(root[now]);
//		puts("");
	}
	return 0;
}
