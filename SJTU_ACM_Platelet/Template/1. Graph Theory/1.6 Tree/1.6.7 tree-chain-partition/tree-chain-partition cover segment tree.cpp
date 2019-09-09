//
//  Title : 树链剖分套线段树
//  Date : 10.05.2016
//  Test : BZOJ-1036
//  Complexity : O(n log^2 n)
//  
/*
	对于维护带修改的树上路径的点权信息的问题——
	解决办法：树链剖分套线段树
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
int M;
#define maxn 1 << 16
struct Edge
{
    int to;
    Edge *next;
}*last[maxn], e[maxn], *ecnt = e;
inline void add(R int a, R int b)
{
    *++ecnt = (Edge) {b, last[a]};
    last[a] = ecnt;
}
int dep[maxn], fa[maxn], size[maxn], son[maxn], top[maxn], pos[maxn], timer;
int v[maxn];
bool vis[maxn];
void dfs1(R int x)
{
    dep[x] = dep[fa[x]] + 1; size[x] = 1; vis[x] = 1;
    for (R Edge *iter = last[x]; iter; iter = iter -> next)
        if (!vis[iter -> to])
        {
            R int pre = iter -> to;
            fa[pre] = x;
            dfs1(pre);
            size[x] += size[pre];
            size[pre] > size[son[x]] ? son[x] = pre : 0;
        }
}
void dfs2(R int x)
{
    vis[x] = 0;
    pos[x] = timer++;
    top[x] = x == son[fa[x]] ? top[fa[x]] : x;
    for (R Edge *iter = last[x]; iter; iter = iter -> next)
        if (iter -> to == son[x])
            dfs2(iter -> to);
    for (R Edge *iter = last[x]; iter; iter = iter -> next)
        if (vis[iter -> to])
            dfs2(iter -> to);
}
inline int getlca(R int a, R int b)
{
    while (top[a] != top[b])
    {
        dep[top[a]] < dep[top[b]] ? b = fa[top[b]] : a = fa[top[a]];
    }
    return dep[a] < dep[b] ? a : b;
}
struct SegmentTree
{
    int sum, mx;
}tr[maxn];
inline void Build()
{
    for (R int i = M - 1; i; --i)
    {
        tr[i].sum = tr[i << 1].sum + tr[i << 1 | 1].sum;
        tr[i].mx = dmax(tr[i << 1].mx, tr[i << 1 | 1].mx);
    }
}
inline void Change(R int pos, R int val)
{
    R int i = pos + M;
    for (tr[i].sum = tr[i].mx = val, i >>= 1; i; i >>= 1)
    {
        tr[i].sum = tr[i << 1].sum + tr[i << 1 | 1].sum;
        tr[i].mx = dmax(tr[i << 1].mx, tr[i << 1 | 1].mx);
    }
}
#define inf 0x7fffffff
inline int Query_max(R int s, R int t)
{
    R int ans = -inf;
    for (s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1)
    {
        if (~ s & 1) cmax(ans, tr[s ^ 1].mx);
        if (t & 1) cmax(ans, tr[t ^ 1].mx);
    }
    return ans;
}
inline int Query_sum(R int s, R int t)
{
    R int ans = 0;
    for (s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1)
    {
        if (~ s & 1) ans += tr[s ^ 1].sum;
        if (t & 1) ans += tr[t ^ 1].sum;
    }
    return ans;
}
inline int getmax(R int a, R int b)
{
    R int ans = -inf;
    while (top[a] != top[b])
    {
        cmax(ans, Query_max(pos[top[a]], pos[a]));
        a = fa[top[a]];
    }
    cmax(ans, Query_max(pos[b], pos[a]));
    return ans;
}
inline int getsum(R int a, R int b)
{
    R int ans = 0;
    while (top[a] != top[b])
    {
        ans += Query_sum(pos[top[a]], pos[a]);
        a = fa[top[a]];
    }
    ans += Query_sum(pos[b], pos[a]);
    return ans;
}
int main()
{
//  setfile();
    R int n = FastIn();
    for (M = 1; M < n; M <<= 1);
    for (R int i = 1; i < n; ++i)
    {
        R int a = FastIn(), b = FastIn();
        add(a, b);
        add(b, a);
    }
    dfs1(1);
    dfs2(1);
    for (R int i = 1; i <= n; ++i)
    {
        v[i] = FastIn();
        tr[pos[i] + M] = (SegmentTree) {v[i], v[i]};
    }
    for (R int i = n; i < M; ++i) tr[i + M] = (SegmentTree) {0, -inf};
    Build();
    for (R int q = FastIn(); q; --q)
    {
        char opt = getc();
        while (opt < 'A' || opt > 'Z') opt = getc();
        if (opt == 'C')
        {
            R int x = FastIn(), y = FastIn();
            Change(pos[x], y);
            v[x] = y;
        }
        else
        {
            opt = getc();
            R int x = FastIn(), y = FastIn();
            R int lca = getlca(x, y);
            if (opt == 'M')
                printf("%d\n", dmax(getmax(x, lca), getmax(y, lca)) );
            else
                printf("%d\n", getsum(x, lca) + getsum(y, lca) - v[lca]);
        }
    }
    return 0;
}
/*
input:
4
1 2
2 3
4 1
4 2 1 3
12
QMAX 3 4
QMAX 3 3
QMAX 3 2
QMAX 2 3
QSUM 3 4
QSUM 2 1
CHANGE 1 5
QMAX 3 4
CHANGE 3 6
QMAX 3 4
QMAX 2 4
QSUM 3 4
output:
4
1
2
2
10
6
5
6
5
16
*/
