//
//  Title : tarjan缩强联通分量
//  Date : 04.04.2016
//  Test : YZOJ-1332
//  Complexity : O(n + m)
//  
/*
	对于有向图中存在缩强联通分量的问题——
	解决办法：tarjan缩强联通分量
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
#define maxn 10010
#define maxm 1000010
int last[maxn], to[maxm], next[maxm], ecnt;
int dfn[maxn], low[maxn], id[maxn], scc, num, st[maxn], stcnt, size[maxn];
#define add(_a, _b) (to[++ecnt] = (_b), next[ecnt] = last[_a] , last[_a] = ecnt )
void dfs(R int x)
{
	dfn[x] = low[x] = ++num;
	st[++stcnt] = x;
	for (R int i = last[x]; i; i = next[i])
	{
		R int pre = to[i];
		if (!dfn[pre])
		{
			dfs(pre);
			cmin(low[x], low[pre]);
		}
		else if (!id[pre]) cmin(low[x], dfn[pre]);
	}
	if (dfn[x] == low[x])
	{
		++scc;
		while (1)
		{
			R int pre = st[stcnt--];
			id[pre] = scc;
			size[scc]++;
			if (pre == x) break;
		}
	}
}
int out[maxn];
int main()
{
//	setfile();
	R int n = FastIn(), m = FastIn();
	for (R int i = 1; i <= m; ++i)
	{
		R int a = FastIn(), b = FastIn();
		add(a, b);
	}
	for (R int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i);
	for (R int i = 1; i <= n; ++i)
		for (R int j = last[i]; j; j = next[j])
			if (id[i] != id[to[j]])
				out[id[i]]++;
	R int ans = 0;
	for (R int i = 1; i <= scc; ++i)
		if (!out[i])
		{
			if (!ans) ans = size[i];
			else
			{
				ans = 0;
				break;
			}
		}
	printf("%d\n",ans );
	return 0;
}

