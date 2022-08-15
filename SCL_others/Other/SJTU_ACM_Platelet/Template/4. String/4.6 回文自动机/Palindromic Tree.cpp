#define maxn 300010
char str[maxn];
int next[maxn][26], fail[maxn], len[maxn], cnt[maxn], last, tot, n;
inline int new_node(R int l)
{
    len[++tot] = l;
    return tot;
}
inline void init()
{
    tot = -1;
    new_node(0);
    new_node(-1);
    str[0] = -1;
    fail[0] = 1;
}
inline int get_fail(R int x)
{
    while (str[n - len[x] - 1] != str[n]) x = fail[x];
    return x;
}
inline void extend(R int c)
{
    ++n;
    R int cur = get_fail(last);
    if (!next[cur][c])
    {
        R int now = new_node(len[cur] + 2);
        fail[now] = next[get_fail(fail[cur])][c];
        next[cur][c] = now;
    }
    last = next[cur][c];
    ++cnt[last];
}
long long ans;
inline void count()
{
    for (R int i = tot; i; --i)
    {
        cnt[fail[i]] += cnt[i];
        cmax(ans, 1ll * len[i] * cnt[i]);
    }
}
int main()
{
    scanf("%s", str + 1);
    init();
    for (R int i = 1; str[i]; ++i)
        extend(str[i] - 'a');
    count();
    printf("%lld\n", ans);
    return 0;
}
