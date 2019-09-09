#include <cstdio>
#include <cstring>

#define maxn 10010
#define maxm 100010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
bool cut[maxn];
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxm << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dfn[maxn], low[maxn], timer, ans, num;
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++timer;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				tarjan(iter -> to, x);
				cmin(low[x], low[iter -> to]);
				if (dfn[x] <= low[iter -> to])
				{
					cut[x] = 1;
					if (!fa && dfn[x] < low[iter -> to]) num = 233;
					else if (!fa) ++num;
				}
			}
			else cmin(low[x], dfn[iter -> to]);
		}
}
int main()
{
	int t; scanf("%d", &t);
	for (; t; --t)
	{
		memset(last, 0, sizeof last); ecnt = e;
		memset(cut, 0, sizeof (cut));
		memset(dfn, 0, sizeof (dfn)); timer = 0;
		memset(low, 0, sizeof (low)); ans = 0;
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			link(a, b);
		}
		for (int i = 1; i <= n; ++i)
			if (!dfn[i])
			{
				num = 0;
				tarjan(i, 0);
				if (num == 1) cut[i] = 0;
			}
		for (int i = 1; i <= n; ++i) ans += cut[i];
		printf("%d\n", ans);
	}
	return 0;
}
