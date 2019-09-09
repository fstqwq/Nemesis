//
//  Title : Point-divide-ans-conquer
//  Date : 01.06.2016
//  Test : BZOJ-1468
//  Complexity : O(nlogn)
//  
/*
	对于树的路径统计等问题——
	解决办法：基于点的分治
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
#define maxn 300010
#define maxm 600010
struct Edge
{
	Edge *next;
	int to, w;
}*last[maxn], e[maxm], *ecnt = e;
inline void link(R int a, R int b, R int v)
{
	*++ecnt = (Edge) {last[a], b, v}; last[a] = ecnt;
}
int n, k, size[maxn], son[maxn], root, sum, depcnt;
long long ans, deep[maxm], d[maxn];
bool vis[maxn];
void dfsroot(R int x, R int fa)
{
	size[x] = 1; son[x] = 0;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
	{
		R int pre = iter -> to;
		if (pre == fa || vis[pre]) continue;
		dfsroot(pre, x);
		size[x] += size[pre];
		cmax(son[x], size[pre]);
	}
	cmax(son[x], sum - size[x]);
	if (root == 0 || son[x] < son[root]) root = x;
}
void dfsdep(R int x, R int fa)
{
	deep[++depcnt] = d[x];
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
	{
		R int pre = iter -> to;
		if (pre == fa || vis[pre]) continue;
		d[pre] = d[x] + iter -> w;
		dfsdep(pre, x);
	}
}
inline long long cal(R int x, R int val)
{
	d[x] = val; depcnt = 0;
	dfsdep(x, 0);
	std::sort(deep + 1, deep + depcnt + 1);
	R long long t = 0;
	R int l, r;
	for (l = 1, r = depcnt; l < r; )
	{
		if (deep[l] + deep[r] <= k) {t += r - l; ++l;}
		else --r;
	}
	return t;
}
void work(R int x)
{
	ans += cal(x, 0);
	vis[x] = 1;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
	{
		R int pre = iter -> to;
		if (vis[pre]) continue;
		ans -= cal(pre, iter -> w);
		sum = size[pre];
		root = 0;
		dfsroot(pre, 0);
		work(root);
	}
}
int main()
{
	n = FastIn(); sum = n;
	for (R int i = 1; i < n; ++i)
	{
		R int a = FastIn(), b = FastIn(), v = FastIn();
		link(a, b, v); link(b, a, v);
	}
	k = FastIn();
	son[root = 0] = 1 << 30;
	dfsroot(1, 0);
	work(root);
	printf("%lld\n", ans );
	return 0;
}
