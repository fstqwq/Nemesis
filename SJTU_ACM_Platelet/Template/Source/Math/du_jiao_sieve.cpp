int phi[maxn], pr[maxn / 10], prcnt;
ll sph[maxn];
bool vis[maxn];
const int moha = 3333331;
struct Hash {
    Hash *next;
    int ps; ll ans;
} *last1[moha], mem[moha], *tot = mem;
inline ll S1(int n)
{
    if (n < maxn) return sph[n];
    for (R Hash *iter = last1[n % moha]; iter; iter = iter -> next)
        if (iter -> ps == n) return iter -> ans;

    ll ret = 1ll * n * (n + 1ll) / 2;
    for (ll i = 2, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        ret -= S1(n / i) * (j - i + 1);
    }
    *++tot = (Hash) {last1[n % moha], n, ret}; last1[n % moha] = tot;
    return ret;
}
int main()
{
    int T; scanf("%d", &T);
    phi[1] = sph[1] = 1;
    for (int i = 2; i < maxn; ++i)
    {
        if (!vis[i]) pr[++prcnt] = i, phi[i] = i - 1;
        sph[i] = sph[i - 1] + phi[i];
        for (int j = 1; j <= prcnt && 1ll * i * pr[j] < maxn; ++j)
        {
            vis[i * pr[j]] = 1;
            if (i % pr[j])
                phi[i * pr[j]] = phi[i] * (pr[j] - 1);
            else
            {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            }
        }
    }
    for (; T; --T)
    {
        int N; scanf("%d", &N);
        printf("%lld\n", S1(N));
    }
    return 0;
}
