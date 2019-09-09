//
//  Title : Bridge
//  Date : 27.05.2016
//  Test : YZOJ-1292
//  Complexity : O(n)
//  
/*
	对于求桥等问题——
	解决办法：dfs
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
#define maxn 160
#define maxm 5010
struct Edge
{
	Edge *next;
	int to;
}*last[maxn], e[maxm], *ecnt = e;
bool ans[maxn][maxn];
inline void link(R int a, R int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
}
int dfn[maxn], low[maxn], timer;
void dfs(R int x, R int fa)
{
	dfn[x] = low[x] = ++timer;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				dfs(iter -> to, x);
				cmin(low[x], low[iter -> to]);
				if (dfn[x] < low[iter -> to]) ans[x][iter -> to] = ans[iter -> to][x] = 1;
			}
			else cmin(low[x], dfn[iter -> to]);
		}
}
int main()
{
//	setfile();
	R int n = FastIn(), m = FastIn();
	for (R int i = 1; i <= m; ++i)
	{
		R int a = FastIn(), b = FastIn();
		link(a, b), link(b, a);
	}
	dfs(1, 0);
	for (R int i = 1; i <= n; ++i)
		for (R int j = i + 1; j <= n; ++j)
			if (ans[i][j]) printf("%d %d\n", i, j );
	return 0;
}
