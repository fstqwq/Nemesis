#include <cstdio>
#include <algorithm>

#define R register
#define maxn 400010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
inline int F()
{
	R char ch; R int cnt = 0;
	while (ch = getchar(), ch < '0' || ch > '9') ;
	cnt = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return cnt;
}
struct Edge {
	Edge *next;
	int to;
} *last[maxn << 1], e[maxn << 2], *ecnt = e;
struct edge {
	edge *next; int to, w;
} *lt[maxn], le[maxn << 2], *lecnt = le, *rt[maxn], re[maxn << 2], *recnt = re;
inline void link1(R int a, R int b, R int w)
{
	*++lecnt = (edge) {lt[a], b, w}; lt[a] = lecnt;
	*++recnt = (edge) {rt[b], a, w}; rt[b] = recnt;
}
inline void link(R int a, R int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
}
int dfn[maxn], low[maxn], timer, st[maxn], top, id[maxn], colcnt, n;
bool fail, used[maxn];
void tarjan(R int x, R int fa)
{
	dfn[x] = low[x] = ++timer; st[++top] = x;
	for (R Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				tarjan(iter -> to, x);
				cmin(low[x], low[iter -> to]);
			}
			else if (!id[iter -> to]) cmin(low[x], dfn[iter -> to]);
		}
	if (dfn[x] == low[x])
	{
		++colcnt; R bool flag = 1;
		for (; ;)
		{
			R int now = st[top--];
			id[now] = colcnt;
			if (now <= 2 * n)
			{
				flag &= !used[id[now <= n ? now + n : now - n]];
				now <= n ? fail |= (id[now + n] == id[now]) : fail |= (id[now - n] == id[now]);
			}
			if (now == x) break;
		}
		used[colcnt] = flag;
	}
}
int ans[maxn], tot;
int main()
{
	n = F(); R int m = F();
	for (R int i = 1; i <= m; ++i)
	{
		R int a = F(), b = F(), w = F();
		link1(a, b, w);
	}
//********************************* build graph
	R int ptot = 2 * n;
	for (R int i = 1; i <= n; ++i)
	{
		R int lp = ptot, rp;
		for (R edge *iter = lt[i]; iter; iter = iter -> next)
		{
			link(i + n, iter -> to + n * iter -> w);
			ptot != lp ? link(ptot + 1, ptot), 1 : 0;
			link(++ptot, iter -> to + n * iter -> w);
		}
		rp = ptot;
		for (R edge *iter = lt[i]; iter; iter = iter -> next)
		{
			if (iter != lt[i]) link(ptot, ptot + 1);
			link(++ptot, iter -> to + n * iter -> w);
		}
		for (R edge *iter = rt[i]; iter; iter = iter -> next)
			if (!iter -> w) link(i + n, iter -> to);
		R int counter = 0;
		for (R edge *iter = lt[i]; iter; iter = iter -> next)
		{
			++counter;
			if (iter != lt[i]) link(iter -> to + n * (iter -> w ^ 1), lp + counter - 1);
			if (iter -> next) link(iter -> to + n * (iter -> w ^ 1), rp + counter + 1);
		}
		for (R edge *iter = rt[i]; iter; iter = iter -> next)
			if (iter -> w) link(i, iter -> to);
	}
//****************************************************
	for (R int i = 1; !fail && i <= n; ++i) if (!dfn[i]) tarjan(i, 0);
	if (fail)
	{
		puts("Impossible");
		return 0;
	}
	for (R int i = 1; i <= n; ++i) if (used[id[i]]) ans[++tot] = i;
	printf("%d\n", tot);
	std::sort(ans + 1, ans + tot + 1);
	for (R int i = 1; i <= tot; ++i) printf("%d ", ans[i]);
	return 0;
}
