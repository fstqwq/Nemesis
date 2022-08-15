//
//  Title : 朴素的dijkstra算法（链表优化）
//  Date : 04.05.2016
//  Test : YZOJ-1353
//  Complexity : O(n^2)
//  
/*
	对于稠密图的单源最短路等问题——
	解决办法：朴素的dijkstra
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
#define maxn 1810
int a[maxn][maxn], last[maxn], next[maxn], d[maxn];
#define INF 0x7fffffff
int main()
{
//	setfile();
	R int n = FastIn();
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= n; ++j)
			a[i][j] = FastIn();
	for (R int i = 1; i <= n; ++i) last[i] = i - 1, next[i] = i + 1;
	for (R int i = 1; i <= n; ++i) d[i] = a[1][i];
	R int ans = 0;
	for (R int i = 1; i < n; ++i)
	{
		R int minn = INF, node;
		for (R int j = next[1]; j <= n; j = next[j])
			minn > d[j] ? minn = d[j], node = j : 0;
		next[last[node]] = next[node];
		last[next[node]] = last[node];
		ans += minn;
		for (R int j = next[1]; j <= n; j = next[j])
			cmin(d[j], minn + a[node][j]);
	}
	printf("%d\n",ans );
	return 0;
}
