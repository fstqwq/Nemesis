int size[maxn], dep[maxn], son[maxn], fa[maxn], top[maxn], dfn[maxn], pos[maxn], timer, rig[maxn];
ll dis[maxn];
bool vis[maxn];
// 树链剖分 begin
void dfs1(int x);
void dfs2(int x){cmax(rig[top[x]], dfn[x]);}
inline int getlca(int a, int b);
// 树链剖分 end
struct Seg {
    Seg *ls, *rs;
    ll min, k, b, vl, vr;
    // min 表示区间最小值
    // k 表示区间内 直线标记的斜率
    // b 表示区间内 直线标记的截距
    // vl, vr 表示区间内 x 的最小值和最大值
    inline void update()
    {
        min = dmin(ls -> min, rs -> min);
        k > 0 ? cmin(min, k * vl + b) : cmin(min, k * vr + b);
    }
} ssegg[maxn << 2], *scnt = ssegg, *rt[maxn];
void build(int l, int r)
{
    R Seg *o = scnt; o -> k = 0; o -> b = inf;
    o -> vl = dis[pos[l]]; o -> vr = dis[pos[r]]; o -> min = inf;
    if (l == r) return ;
    int mid = l + r >> 1;
    o -> ls = ++scnt; build(l, mid);
    o -> rs = ++scnt; build(mid + 1, r);
    o -> update();
}
int ql, qr, qk;
ll qb;
void modify(R Seg *o, int l, int r, int k, ll b)
{
    int mid = l + r >> 1;

    if (ql <= l && r <= qr)
    {
        if (l == r)
        {
            cmin(o -> min, k * o -> vl + b);
            return ;
        }
        ll
        val = o -> vl * k + b,
        var = o -> vr * k + b,
        vbl = o -> vl * o -> k + o -> b,
        vbr = o -> vr * o -> k + o -> b;
        if (val <= vbl && var <= vbr)
        {
            o -> k = k; o -> b = b;
            o -> update();
            return ;
        }
        if (val >= vbl && var >= vbr) return ;
        ll dam = dis[pos[mid]], vam = dam * k + b, vbm = dam * o -> k + o -> b;
        if (val >= vbl && vam <= vbm)
        {
            modify(o -> ls, l, mid, o -> k, o -> b);
            o -> k = k; o -> b = b;
        }
        else if (val <= vbl && vam >= vbm)
            modify(o -> ls, l, mid, k, b);
        else
        {
            if (vam <= vbm && var >= vbr)
            {
                modify(o -> rs, mid + 1, r, o -> k, o -> b);
                o -> k = k; o -> b = b;
            }
            else
                modify(o -> rs, mid + 1, r, k, b);
        }
        o -> update();
        return ;
    }
    if (ql <= mid) modify(o -> ls, l, mid, k, b);
    if (mid < qr) modify(o -> rs, mid + 1, r, k, b);
    o -> update();
}
ll query(R Seg *o, int l, int r)
{
    if (ql <= l && r <= qr) return o -> min;
    int mid = l + r >> 1; ll ret = inf, tmp;
    cmin(ret, dis[pos[dmax(ql, l)]] * o -> k + o -> b);
    cmin(ret, dis[pos[dmin(qr, r)]] * o -> k + o -> b);
    if (ql <= mid) tmp = query(o -> ls, l, mid), cmin(ret, tmp);
    if (mid < qr) tmp = query(o -> rs, mid + 1, r), cmin(ret, tmp);
    return ret;
}
inline void tr_modify(int x, int f)
{
    while (top[x] != top[f])
    {
        ql = dfn[top[x]]; qr = dfn[x];
        modify(rt[top[x]], ql, rig[top[x]], qk, qb);
        x = fa[top[x]];
    }
    ql = dfn[f]; qr = dfn[x];
    modify(rt[top[x]], dfn[top[x]], rig[top[x]], qk, qb);
}
inline ll tr_query(int s, int t)
{
    ll ret = inf, tmp;
    while (top[s] != top[t])
    {
        if (dep[top[s]] < dep[top[t]])
        {
            ql = dfn[top[t]]; qr = dfn[t];
            tmp = query(rt[top[t]], ql, rig[top[t]]);
            cmin(ret, tmp);
            t = fa[top[t]];
        }
        else
        {
            ql = dfn[top[s]]; qr = dfn[s];
            tmp = query(rt[top[s]], ql, rig[top[s]]);
            cmin(ret, tmp);
            s = fa[top[s]];
        }
    }
    ql = dfn[s]; qr = dfn[t]; ql > qr ? std::swap(ql, qr), 1 : 0;
    tmp = query(rt[top[s]], dfn[top[s]], rig[top[s]]);
    cmin(ret, tmp);
    return ret;
}
int main()
{
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int a, b, w; scanf("%d%d%d", &a, &b, &w); link(a, b, w);
    }
    dfs1(1); dfs2(1);
    for (int i = 1; i <= n; ++i)
        if (top[i] == i)
        {
            rt[i] = ++scnt;
            build(dfn[i], rig[i]);
        }
    for (; m; --m)
    {
        int opt, s, t, lca; scanf("%d%d%d", &opt, &s, &t);
        lca = getlca(s, t);
        if (opt == 1)
        {
            int a; ll b; scanf("%d%lld", &a, &b);
            lca = getlca(s, t);
            qk = -a; qb = a * dis[s] + b;
            tr_modify(s, lca);
            qk = a; qb = a * dis[s] - dis[lca] * 2 * a + b;
            tr_modify(t, lca);
        }
        else
        {
            printf("%lld\n", tr_query(s, t));
        }
    }
    return 0;
}
